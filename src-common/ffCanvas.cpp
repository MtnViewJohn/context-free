// ffCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2017 John Horigan - john@glyphic.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
// 
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#define __STDC_CONSTANT_MACROS 1

#include "ffCanvas.h"
#include <cassert>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

extern void log_callback_debug(void *ptr, int level, const char *fmt, va_list vl);

class ffCanvas::Impl
{
public:
    Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
        std::unique_ptr<char[]> bits, int fps);
    ~Impl();
    
    void addFrame(bool end);
    
    int             mWidth;
    int             mHeight;
    int             mStride;
    std::unique_ptr<char[]> mBuffer;
    int             mFrameRate;
    int				mLineSize;
    const char*     mError;
    
    AVFormatContext *mOutputCtx;
    AVFrame         *mFrame;
    AVPacket		*mPacket;
    
    static const uint32_t
                    dummyPalette[256];
    
    friend class ffCanvas;
};

const uint32_t ffCanvas::Impl::dummyPalette[256] = { 0 };

ffCanvas::Impl::Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
                     std::unique_ptr<char[]> bits, int fps)
: mWidth(width), mHeight(height), mStride(stride), mBuffer(std::move(bits)), mFrameRate(fps),
  mError(nullptr), mOutputCtx(nullptr), mFrame(nullptr), mPacket(nullptr)
{
#ifdef DEBUG
    av_log_set_callback(log_callback_debug);
#endif

    avcodec_register_all();
    av_register_all();

    int res = avformat_alloc_output_context2(&mOutputCtx, NULL, "mov", name);
    if (res < 0) {
        mError = "out of memory";
        return;
    }
    
    AVCodec *codec = avcodec_find_encoder(AV_CODEC_ID_QTRLE);
    if (!codec) {
        mError = "codec not found";
        return;
    }
    
    AVStream* stream = avformat_new_stream(mOutputCtx, codec);
    if (stream == NULL) {
        mError = "out of memory";
        return;
    }

    AVCodecContext* codecCtx = stream->codec;

    mPacket = av_packet_alloc();
    if (!mPacket) {
        mError = "Out of memory";
        return;
    }

    /* put sample parameters */
    codecCtx->bit_rate = height * stride * fps * 8;
    /* resolution must be a multiple of two */
    assert(((width & 3) | (height & 3)) == 0);
    codecCtx->width = width;
    codecCtx->height = height;
    /* frames per second */
    codecCtx->time_base.num = 1;
    codecCtx->time_base.den = fps;
    codecCtx->gop_size = 10; /* emit one intra frame every ten frames */
    codecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
    
    switch (fmt) {
        case aggCanvas::Gray8_Blend:
            codecCtx->pix_fmt = AV_PIX_FMT_GRAY8;
            mLineSize = mWidth;
            break;
        case aggCanvas::FF24_Blend:
            codecCtx->pix_fmt = AV_PIX_FMT_RGB24;
            mLineSize = mWidth * 3;
            break;
        case aggCanvas::FF_Blend:
            codecCtx->pix_fmt = AV_PIX_FMT_ARGB;
            mLineSize = mWidth * 4;
            break;
        default:
            mError = "unknown pixel format";
            return;
    }
    
    if (avcodec_open2(codecCtx, codec, NULL) < 0) {
        mError = "could not open codec";
        return;
    }

    mFrame = av_frame_alloc();
    if (mFrame == NULL) {
        mError = "out of memory";
        return;
    }
    mFrame->format = codecCtx->pix_fmt;
    mFrame->width = width;
    mFrame->height = height;

    if (av_frame_get_buffer(mFrame, 32) < 0) {
        mError = "Out of memory";
        return;
    }
    
    if (avio_open(&(mOutputCtx->pb), name, AVIO_FLAG_WRITE) < 0) {
        mError = "failed to write video file header";
        return;
    }
    
    res = avformat_write_header(mOutputCtx, NULL);
    if (res < 0) {
        avio_close(mOutputCtx->pb);
        mError = "failed to write video file header";
        return;
    }
}

ffCanvas::Impl::~Impl()
{
    if (!mError) {
        addFrame(true);         // flush out any packets
        int ret = av_write_trailer(mOutputCtx);
        if (ret >= 0)
            ret = avio_close(mOutputCtx->pb);
        if (ret < 0)
            mError = "error closing movie file";
    }
    
    if (mOutputCtx) {
        avformat_free_context(mOutputCtx); mOutputCtx = NULL;
    }
    
    if (mFrame) {
        av_free(mFrame); mFrame = NULL;
    }

    av_packet_free(&mPacket);   // OK if NULL, sets to NULL
}

void
ffCanvas::Impl::addFrame(bool end)
{
    AVFrame* frame = end ? nullptr : mFrame;
    AVStream* stream = mOutputCtx->streams[0];
    AVCodecContext* codecCtx = stream->codec;
    int ret;
    bool tryAgain = false;

    if (!end) {
        if (av_frame_make_writable(frame)) {
            mError = "Error encoding frame";
            return;
        }

        const uint8_t* src = (uint8_t*)(mBuffer.get());
        uint8_t* dest = frame->data[0];
        for (int h = 0; h < mHeight; ++h, src += mStride, dest += frame->linesize[0])
            memcpy(dest, src, mLineSize);
        frame->pts = av_rescale_q(codecCtx->frame_number, codecCtx->time_base, stream->time_base);
    }

    do {
        /* send the frame to the encoder */
        ret = avcodec_send_frame(codecCtx, frame);
        tryAgain = false;
        if (ret == AVERROR(EAGAIN)) {
            tryAgain = true;
        } else if (ret < 0) {
            mError = "Error sending a frame for encoding";
            return;
        }

        for (;;) {
            ret = avcodec_receive_packet(codecCtx, mPacket);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            } else if (ret < 0) {
                mError = "Error during encoding";
                return;
            }

            mPacket->stream_index = stream->index;
            av_write_frame(mOutputCtx, mPacket);
            av_packet_unref(mPacket);
        }
    } while (tryAgain);
}

static aggCanvas::PixelFormat
mapPixFmt(aggCanvas::PixelFormat in)
{
    switch (in) {
        case aggCanvas::Gray8_Blend:
        case aggCanvas::Gray16_Blend:
            return aggCanvas::Gray8_Blend;
        case aggCanvas::RGB8_Blend:
        case aggCanvas::RGB16_Blend:
            return aggCanvas::FF24_Blend;
        default:
            return aggCanvas::FF_Blend;
    }
}

ffCanvas::ffCanvas(const char* name, PixelFormat fmt, int width, int height, int fps)
: aggCanvas(mapPixFmt(fmt)), mErrorMsg(nullptr)
{
    if (width & 7 || height & 7) {
        mErrorMsg = "Dimensions must be multiples of 8 pixels";
        mError = true;
        return;
    }
    
    int stride = width * aggCanvas::BytesPerPixel.at(mapPixFmt(fmt));
    
    std::unique_ptr<char[]> bits = std::make_unique<char[]>(stride * height);
    aggCanvas::attach((void*)bits.get(), width, height, stride);
    
    impl = std::make_unique<Impl>(name, mapPixFmt(fmt), width, height, stride, std::move(bits), fps);
    if (impl->mError) {
        mErrorMsg = impl->mError;
        impl.reset();
        mError = true;
    }
}

ffCanvas::~ffCanvas() = default;

void
ffCanvas::end()
{
    aggCanvas::end();

    if (impl) {
        impl->addFrame(false);
        if (impl->mError) {
            mErrorMsg = impl->mError;
            mError = true;
            impl.reset();
        }
    }
}

