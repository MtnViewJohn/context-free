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
#include <vector>
#include <array>
#ifdef _WIN32
#include <Windows.h>
#else
#include <cstdio>
#endif

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

bool
ffCanvas::Available()
{
    return true;
}

class ffCanvas::Impl
{
public:
    Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
        int fps, QTcodec codec);
    ~Impl();
    
    void addFrame(bool end);
    
    int             mWidth;
    int             mHeight;
    int             mStride;
    std::vector<char> mBuffer;
    int             mFrameRate;
    int				mLineSize = 0;
    const char*     mError = nullptr;
    
    AVStream        *mStream = nullptr;
    AVCodecContext  *mEncCtx = nullptr;

    AVFormatContext *mOutputCtx = nullptr;
    AVFrame         *mFrame = nullptr;
    AVPacket		*mPacket = nullptr;
    SwsContext      *mSwsCtx = nullptr;
    
    friend class ffCanvas;
};

#if defined(_WIN32) && defined(_DEBUG)
void log_callback_debug(void* ptr, int level, const char* fmt, va_list vl)
{
    using av_log_default_callback_ptr = void(__cdecl*)(void* avcl, int level, const char* fmt, va_list vl);
    using av_log_format_line_ptr = void(__cdecl*)(void* ptr, int level, const char* fmt, va_list vl,
        char* line, int line_size, int* print_prefix);

    va_list vl2;
    std::array<char, 1024> line;
    static int print_prefix = 1;

    va_copy(vl2, vl);
    av_log_default_callback(ptr, level, fmt, vl);
    av_log_format_line(ptr, level, fmt, vl2, line.data(), (int)line.size(), &print_prefix);
    va_end(vl2);
    if (AV_LOG_DEBUG >= level) {
        ::OutputDebugStringA(line.data());
    }
}
#endif


ffCanvas::Impl::Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
                     int fps, QTcodec _codec)
: mWidth(width), mHeight(height), mStride(stride), mBuffer(stride * height), mFrameRate(fps)
{
#if defined(_WIN32) && defined(_DEBUG)
    av_log_set_callback(log_callback_debug);
#endif

    if (int alloc_outctx_stat = avformat_alloc_output_context2(&mOutputCtx, nullptr, "mov", name);
        alloc_outctx_stat < 0)
    {
        mError = "out of memory";
        return;
    }
    
    const AVCodec *codec = avcodec_find_encoder_by_name(_codec ? "prores_ks" : "libx264");
    if (!codec) {
        mError = "codec not found";
        return;
    }
    
    mStream = avformat_new_stream(mOutputCtx, codec);
    if (mStream == nullptr) {
        mError = "out of memory";
        return;
    }
    mStream->id = mOutputCtx->nb_streams - 1;


    mPacket = av_packet_alloc();
    if (!mPacket) {
        mError = "Out of memory";
        return;
    }

    mEncCtx = avcodec_alloc_context3(codec);
    if (!mEncCtx) {
        mError = "Out of memory";
        return;
    }

    /* resolution must be a multiple of 8,2 */
    assert(((width & 7) | (height & 1)) == 0);
    mEncCtx->width = width;
    mEncCtx->height = height;
    /* frames per second */
    mEncCtx->time_base.num = 1;
    mEncCtx->time_base.den = fps;
    mEncCtx->gop_size = 10; /* emit one intra frame every ten frames */
    if (mOutputCtx->flags & AVFMT_GLOBALHEADER)
        mEncCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    if (mEncCtx->codec_id == AV_CODEC_ID_H264)
        mEncCtx->mb_decision = 2;
    if (_codec)
        mEncCtx->profile = 2;  // ProRes422 main profile is 2
    
    AVPixelFormat srcFormat;
    AVPixelFormat dstFormat = _codec ? AV_PIX_FMT_YUV422P10LE : AV_PIX_FMT_YUV420P;

    switch (fmt) {
        case aggCanvas::Gray8_Blend:
            srcFormat = AV_PIX_FMT_GRAY8;
            mLineSize = mWidth;
            break;
        case aggCanvas::FF24_Blend:
            srcFormat = AV_PIX_FMT_RGB24;
            mLineSize = mWidth * 3;
            break;
        case aggCanvas::FF_Blend:
        case aggCanvas::FF_Custom_Blend:
            srcFormat = AV_PIX_FMT_ARGB;
            mLineSize = mWidth * 4;
            if (_codec) {   // switch from ProRes422 to ProRes4444
                dstFormat = AV_PIX_FMT_YUVA444P10LE;
                mEncCtx->profile = 4;
            }
            break;
        default:
            mError = "unknown pixel format";
            return;
    }

    mEncCtx->pix_fmt = dstFormat;

    AVDictionary* opt = nullptr;
    av_dict_set(&opt, "preset", "slow", 0);
    av_dict_set(&opt, "crf", "20.0", 0);
    
    if (int open_codec_stat = avcodec_open2(mEncCtx, codec, &opt)) {
        mError = "could not open codec";
        return;
    }
    
    avcodec_parameters_from_context(mStream->codecpar, mEncCtx);

    mSwsCtx = sws_getContext(mWidth, mHeight, srcFormat, 
                             mWidth, mHeight, dstFormat, 
                             0, nullptr, nullptr, nullptr);
    if (mSwsCtx == nullptr) {
        mError = "pixel conversion error";
        return;
    }

    mFrame = av_frame_alloc();
    if (mFrame == nullptr) {
        mError = "out of memory";
        return;
    }
    mFrame->format = mEncCtx->pix_fmt;
    mFrame->width = width;
    mFrame->height = height;

    if (int fb_alloc_stat = av_frame_get_buffer(mFrame, 32)) {
        mError = "Out of memory";
        return;
    }
    
    if (int open_stat = avio_open(&(mOutputCtx->pb), name, AVIO_FLAG_WRITE)) {
        mError = "failed to open movie file";
        return;
    }

    if (int write_stat = avformat_write_header(mOutputCtx, nullptr);
        write_stat < 0)
    {
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

    avcodec_free_context(&mEncCtx); // OK if NULL, sets to NULL
    
    if (mOutputCtx) {
        avformat_free_context(mOutputCtx); mOutputCtx = nullptr;
    }
    
    if (mFrame) {
        av_free(mFrame); mFrame = nullptr;
    }

    if (mSwsCtx) {
        sws_freeContext(mSwsCtx); mSwsCtx = nullptr;
    }

    av_packet_free(&mPacket);   // OK if NULL, sets to NULL
}

void
ffCanvas::Impl::addFrame(bool end)
{
    AVFrame* frame = end ? nullptr : mFrame;
    int ret;
    bool tryAgain = false;

    if (!end) {
        if (av_frame_make_writable(frame)) {
            mError = "Error encoding frame";
            return;
        }

        const uint8_t* src = (uint8_t*)(mBuffer.data());
        if (sws_scale(mSwsCtx, &src, &mLineSize, 0, mHeight, frame->data, frame->linesize) < mHeight)
            mError = "Error recoding frame";
#if LIBAVCODEC_VERSION_MAJOR < 60
        frame->pts = av_rescale_q(mEncCtx->frame_number, mEncCtx->time_base, mStream->time_base);
#else
        frame->pts = av_rescale_q(mEncCtx->frame_num, mEncCtx->time_base, mStream->time_base);
#endif
    }

    do {
        /* send the frame to the encoder */
        ret = avcodec_send_frame(mEncCtx, frame);
        tryAgain = false;
        if (ret == AVERROR(EAGAIN)) {
            tryAgain = true;
        } else if (ret < 0) {
            mError = "Error sending a frame for encoding";
            return;
        }

        for (;;) {
            ret = avcodec_receive_packet(mEncCtx, mPacket);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            } else if (ret < 0) {
                mError = "Error during encoding";
                return;
            }

            mPacket->stream_index = mStream->index;
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
        case aggCanvas::RGBA8_Custom_Blend:
        case aggCanvas::RGBA16_Custom_Blend:
            return aggCanvas::FF_Custom_Blend;
        default:
            return aggCanvas::FF_Blend;
    }
}

ffCanvas::ffCanvas(const char* name, PixelFormat fmt, int width, int height, 
                   int fps, QTcodec codec, bool temp)
: aggCanvas(mapPixFmt(fmt)), mErrorMsg(nullptr)
{
    if (width <= 0 || height <= 0 || width & 7 || height & 1) {
        mErrorMsg = "Dimensions must be multiples of (8,2) pixels";
        mError = true;
        return;
    }

    if (temp) {
#ifdef _WIN32
        std::array<char, L_tmpnam_s> buf;
        if (tmpnam_s(buf.data(), buf.size()) == 0)
            mFileName = buf.data();
#else
        std::array<char, L_tmpnam> buf;
        char* tempname = tmpnam(buf.data());
        if (tempname)
            mFileName = tempname;
#endif
        if (!mFileName.empty())
            mFileName += ".mov";
        name = mFileName.c_str();
    } else {
        mFileName = name;
    }
    
    int stride = width * aggCanvas::BytesPerPixel.at(mapPixFmt(fmt));
    
    impl = std::make_unique<Impl>(name, mapPixFmt(fmt), width, height, stride, fps, codec);
    if (impl->mError) {
        mErrorMsg = impl->mError;
        impl.reset();
        mError = true;
    } else {
        aggCanvas::attach((void*)impl->mBuffer.data(), width, height, stride);
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

