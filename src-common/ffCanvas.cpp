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
#include <libswscale/swscale.h>
}

#ifdef _WIN32
bool av_load_dlls(void);
bool ffCanvas::Available()
{
    return av_load_dlls(); 
}
void log_callback_debug(void *ptr, int level, const char *fmt, va_list vl);
void my_av_log_set_callback(void(*callback)(void*, int, const char*, va_list));
void my_avcodec_register_all(void);
void my_av_register_all(void);
int my_avformat_alloc_output_context2(AVFormatContext **ctx, AVOutputFormat *oformat,
    const char *format_name, const char *filename);
AVCodec *my_avcodec_find_encoder_by_name(const char*);
AVStream *my_avformat_new_stream(AVFormatContext *s, const AVCodec *c);
AVPacket *my_av_packet_alloc(void);
int my_avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
AVFrame *my_av_frame_alloc(void);
int my_av_frame_get_buffer(AVFrame *frame, int align);
int my_avio_open(AVIOContext **s, const char *url, int flags);
av_warn_unused_result
int my_avformat_write_header(AVFormatContext *s, AVDictionary **options);
int my_av_write_trailer(AVFormatContext *s);
int my_avio_close(AVIOContext *s);
void my_avformat_free_context(AVFormatContext *s);
void my_av_free(void *ptr);
void my_av_packet_free(AVPacket **pkt);
int my_av_frame_make_writable(AVFrame *frame);
int64_t my_av_rescale_q(int64_t a, AVRational bq, AVRational cq) av_const;
int my_avcodec_send_frame(AVCodecContext *avctx, const AVFrame *frame);
int my_avcodec_receive_packet(AVCodecContext *avctx, AVPacket *avpkt);
int my_av_write_frame(AVFormatContext *s, AVPacket *pkt);
void my_av_packet_unref(AVPacket *pkt);
struct SwsContext *my_sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat,
    int dstW, int dstH, enum AVPixelFormat dstFormat,
    int flags, SwsFilter *srcFilter,
    SwsFilter *dstFilter, const double *param);
void my_sws_freeContext(struct SwsContext *swsContext);
int my_sws_scale(struct SwsContext *c, const uint8_t *const srcSlice[],
    const int srcStride[], int srcSliceY, int srcSliceH,
    uint8_t *const dst[], const int dstStride[]);
int my_av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags);
#else
void log_callback_debug(void *ptr, int level, const char *fmt, va_list vl)
{ av_log_default_callback(ptr, level, fmt, vl); }
bool ffCanvas::Available()
{
    return true;
}
#define my_av_log_set_callback av_log_set_callback
#define my_avcodec_register_all avcodec_register_all
#define my_av_register_all av_register_all
#define my_avformat_alloc_output_context2 avformat_alloc_output_context2
#define my_avcodec_find_encoder_by_name avcodec_find_encoder_by_name
#define my_avformat_new_stream avformat_new_stream
#define my_av_packet_alloc av_packet_alloc
#define my_avcodec_open2 avcodec_open2
#define my_av_frame_alloc av_frame_alloc
#define my_av_frame_get_buffer av_frame_get_buffer
#define my_avio_open avio_open
#define my_avformat_write_header avformat_write_header
#define my_av_write_trailer av_write_trailer
#define my_avio_close avio_close
#define my_avformat_free_context avformat_free_context
#define my_av_free av_free
#define my_av_packet_free av_packet_free
#define my_av_frame_make_writable av_frame_make_writable
#define my_av_rescale_q av_rescale_q
#define my_avcodec_send_frame avcodec_send_frame
#define my_av_write_frame av_write_frame
#define my_av_packet_unref av_packet_unref
#define my_sws_getContext sws_getContext
#define my_sws_freeContext sws_freeContext
#define my_sws_scale sws_scale
#define my_av_dict_set av_dict_set
#define my_avcodec_receive_packet avcodec_receive_packet
#endif

class ffCanvas::Impl
{
public:
    Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
        std::unique_ptr<char[]> bits, int fps, QTcodec codec);
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
    SwsContext      *mSwsCtx;
    
    static const uint32_t
                    dummyPalette[256];
    
    friend class ffCanvas;
};

const uint32_t ffCanvas::Impl::dummyPalette[256] = { 0 };

ffCanvas::Impl::Impl(const char* name, PixelFormat fmt, int width, int height, int stride,
                     std::unique_ptr<char[]> bits, int fps, QTcodec _codec)
: mWidth(width), mHeight(height), mStride(stride), mBuffer(std::move(bits)), mFrameRate(fps),
  mError(nullptr), mOutputCtx(nullptr), mFrame(nullptr), mPacket(nullptr), mSwsCtx(nullptr)
{
#ifdef DEBUG
    my_av_log_set_callback(log_callback_debug);
#endif

    my_avcodec_register_all();
    my_av_register_all();

    int res = my_avformat_alloc_output_context2(&mOutputCtx, NULL, "mov", name);
    if (res < 0) {
        mError = "out of memory";
        return;
    }
    
    AVCodec *codec = my_avcodec_find_encoder_by_name(_codec ? "prores_ks" : "libx264");
    if (!codec) {
        mError = "codec not found";
        return;
    }
    
    AVStream* stream = my_avformat_new_stream(mOutputCtx, codec);
    if (stream == nullptr) {
        mError = "out of memory";
        return;
    }

    AVCodecContext* codecCtx = stream->codec;

    mPacket = my_av_packet_alloc();
    if (!mPacket) {
        mError = "Out of memory";
        return;
    }

    /* put sample parameters */
    codecCtx->bit_rate = height * stride * fps * 8;
    /* resolution must be a multiple of 8 */
    assert(((width & 7) | (height & 7)) == 0);
    codecCtx->width = width;
    codecCtx->height = height;
    /* frames per second */
    codecCtx->time_base.num = 1;
    codecCtx->time_base.den = fps;
    codecCtx->gop_size = 10; /* emit one intra frame every ten frames */
    codecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
    codecCtx->profile = _codec ? 2 : FF_PROFILE_H264_MAIN;  // ProRes422 main profile is 2
    
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
            srcFormat = AV_PIX_FMT_ARGB;
            mLineSize = mWidth * 4;
            if (_codec) {   // switch from ProRes422 to ProRes4444
                dstFormat = AV_PIX_FMT_YUVA444P10LE;
                codecCtx->profile = 4;
            }
            break;
        default:
            mError = "unknown pixel format";
            return;
    }

    codecCtx->pix_fmt = dstFormat;

    AVDictionary* opt = nullptr;
    my_av_dict_set(&opt, "preset", "slow", 0);
    my_av_dict_set(&opt, "crf", "20.0", 0);
    my_av_dict_set(&opt, "maxrate", "400k", 0);
    
    if (my_avcodec_open2(codecCtx, codec, &opt) < 0) {
        mError = "could not open codec";
        return;
    }

    mSwsCtx = my_sws_getContext(mWidth, mHeight, srcFormat, 
                                mWidth, mHeight, dstFormat, 
                                0, nullptr, nullptr, nullptr);
    if (mSwsCtx == nullptr) {
        mError = "pixel conversion error";
        return;
    }

    mFrame = my_av_frame_alloc();
    if (mFrame == nullptr) {
        mError = "out of memory";
        return;
    }
    mFrame->format = codecCtx->pix_fmt;
    mFrame->width = width;
    mFrame->height = height;

    if (my_av_frame_get_buffer(mFrame, 32) < 0) {
        mError = "Out of memory";
        return;
    }
    
    if (my_avio_open(&(mOutputCtx->pb), name, AVIO_FLAG_WRITE) < 0) {
        mError = "failed to write video file header";
        return;
    }
    
    res = my_avformat_write_header(mOutputCtx, NULL);
    if (res < 0) {
        my_avio_close(mOutputCtx->pb);
        mError = "failed to write video file header";
        return;
    }
}

ffCanvas::Impl::~Impl()
{
    if (!mError) {
        addFrame(true);         // flush out any packets
        int ret = my_av_write_trailer(mOutputCtx);
        if (ret >= 0)
            ret = my_avio_close(mOutputCtx->pb);
        if (ret < 0)
            mError = "error closing movie file";
    }
    
    if (mOutputCtx) {
        my_avformat_free_context(mOutputCtx); mOutputCtx = nullptr;
    }
    
    if (mFrame) {
        my_av_free(mFrame); mFrame = nullptr;
    }

    if (mSwsCtx) {
        my_sws_freeContext(mSwsCtx); mSwsCtx = nullptr;
    }

    my_av_packet_free(&mPacket);   // OK if NULL, sets to NULL
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
        if (my_av_frame_make_writable(frame)) {
            mError = "Error encoding frame";
            return;
        }

        const uint8_t* src = (uint8_t*)(mBuffer.get());
        if (my_sws_scale(mSwsCtx, &src, &mLineSize, 0, mHeight, frame->data, frame->linesize) < mHeight)
            mError = "Error recoding frame";
        frame->pts = my_av_rescale_q(codecCtx->frame_number, codecCtx->time_base, stream->time_base);
    }

    do {
        /* send the frame to the encoder */
        ret = my_avcodec_send_frame(codecCtx, frame);
        tryAgain = false;
        if (ret == AVERROR(EAGAIN)) {
            tryAgain = true;
        } else if (ret < 0) {
            mError = "Error sending a frame for encoding";
            return;
        }

        for (;;) {
            ret = my_avcodec_receive_packet(codecCtx, mPacket);
            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                break;
            } else if (ret < 0) {
                mError = "Error during encoding";
                return;
            }

            mPacket->stream_index = stream->index;
            my_av_write_frame(mOutputCtx, mPacket);
            my_av_packet_unref(mPacket);
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

ffCanvas::ffCanvas(const char* name, PixelFormat fmt, int width, int height, int fps, QTcodec codec)
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
    
    impl = std::make_unique<Impl>(name, mapPixFmt(fmt), width, height, stride, std::move(bits), fps, codec);
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

