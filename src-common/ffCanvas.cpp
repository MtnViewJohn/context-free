// ffCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011-2012 John Horigan - john@glyphic.com
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
#undef PixelFormat
}

class ffCanvas::Impl
{
public:
    Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
         char* bits, int fps);
    ~Impl();
    
    void addFrame();
    
    int             mWidth;
    int             mHeight;
    int             mStride;
    std::unique_ptr<char[]> mBuffer;
    int             mFrameRate;
    const char*     mError;
    
    AVFormatContext *mOutputCtx;
    AVFrame         *mFrame;
    
    static const uint32_t
                    dummyPalette[256];
    
    friend class ffCanvas;
};

const uint32_t ffCanvas::Impl::dummyPalette[256] = { 0 };

ffCanvas::Impl::Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
                     char* bits, int fps)
: mWidth(width), mHeight(height), mStride(stride), mBuffer(bits), mFrameRate(fps),
  mError(NULL), mOutputCtx(NULL), mFrame(NULL)
{
    avcodec_register_all();
    av_register_all();

    int res = avformat_alloc_output_context2(&mOutputCtx, NULL, "mov", name);
    if (res < 0) {
        mError = "out of memory";
        return;
    }
    
    AVCodec *codec = avcodec_find_encoder(CODEC_ID_QTRLE);
    if (codec == NULL) {
        mError = "codec not found";
        return;
    }
    
    AVStream* stream = avformat_new_stream(mOutputCtx, codec);
    if (stream == NULL) {
        mError = "out of memory";
        return;
    }
    
    AVCodecContext *codecCtx = stream->codec;

    avcodec_get_context_defaults3(codecCtx, codec);
    
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
            codecCtx->pix_fmt = PIX_FMT_GRAY8;
            break;
        case aggCanvas::FF24_Blend:
            codecCtx->pix_fmt = PIX_FMT_RGB24;
            break;
        case aggCanvas::FF_Blend:
            codecCtx->pix_fmt = PIX_FMT_ARGB;
            break;
        default:
            mError = "unknown pixel format";
            return;
    }
    
    if (avcodec_open2(codecCtx, codec, NULL) < 0) {
        mError = "could not open codec";
        return;
    }
    
    mFrame = avcodec_alloc_frame();
    if (mFrame == NULL) {
        mError = "out of memory";
        return;
    }
    mFrame->data[0] = (uint8_t*)bits;
    mFrame->data[1] = codecCtx->pix_fmt == PIX_FMT_GRAY8 ? (uint8_t*)dummyPalette : NULL;
    mFrame->data[2] = mFrame->data[3] = NULL;
    mFrame->linesize[0] = stride;
    mFrame->linesize[1] = codecCtx->pix_fmt == PIX_FMT_GRAY8 ? 1024 : 0;
    mFrame->linesize[2] = mFrame->linesize[3] = 0;
    
    if (avio_open(&(mOutputCtx->pb), name, AVIO_FLAG_WRITE) < 0) {
        mError = "failed to write video file header";
        return;
    }
    
    if (avformat_write_header(mOutputCtx, NULL) < 0) {
        avio_close(mOutputCtx->pb);
        mError = "failed to write video file header";
        return;
    }
}

ffCanvas::Impl::~Impl()
{
    if (!mError) {
        AVStream* stream = mOutputCtx->streams[0];
        AVPacket pkt;
        
        av_init_packet(&pkt);
        pkt.data = NULL;    // packet data will be allocated by the encoder
        pkt.size = 0;
        int ret = 0;
        for (int got_output = 1; got_output; ) {
            ret = avcodec_encode_video2(stream->codec, &pkt, NULL, &got_output);
            if (ret < 0)
                break;
            if (got_output) {
                pkt.stream_index = stream->index;
                
                if (stream->codec->coded_frame->key_frame)
                    pkt.flags |= AV_PKT_FLAG_KEY;
                ret = av_write_frame(mOutputCtx, &pkt);
                if (ret < 0)
                    av_free_packet(&pkt);
                //av_free_packet(&pkt);
            }
        }
        ret = av_write_trailer(mOutputCtx);
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
}

void
ffCanvas::Impl::addFrame()
{
    AVStream* stream = mOutputCtx->streams[0];
    AVPacket pkt;
    int got_output;
    
    av_init_packet(&pkt);
    pkt.data = NULL;    // packet data will be allocated by the encoder
    pkt.size = 0;
    
    int ret = avcodec_encode_video2(stream->codec, &pkt, mFrame, &got_output);
    
    if (ret < 0) {
        mError = "video encoding failed";
        return;
    }
    
    if (got_output) {
        pkt.stream_index = stream->index;
        
        if (stream->codec->coded_frame->key_frame)
            pkt.flags |= AV_PKT_FLAG_KEY;
        if (av_write_frame(mOutputCtx, &pkt) < 0) {
            mError = "video frame write error";
            av_free_packet(&pkt);
            return;
        }
        //av_free_packet(&pkt);
    }
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
: aggCanvas(mapPixFmt(fmt)), mErrorMsg(NULL)
{
    width &= ~3;
    height &= ~3;
    
    int stride = width * aggCanvas::BytesPerPixel.at(mapPixFmt(fmt));
    
    char* bits = new char[stride * height];
    aggCanvas::attach((void*)bits, width, height, stride);
    
    impl.reset(new Impl(name, mapPixFmt(fmt), width, height, stride, bits, fps));
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
        impl->addFrame();
        if (impl->mError) {
            mErrorMsg = impl->mError;
            mError = true;
            impl.reset();
        }
    }
}

