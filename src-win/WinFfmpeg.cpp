// WinFfmpeg.cpp.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2017 John Horigan - john@glyphic.com
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

#include <Windows.h>
#include <cerrno>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


static HMODULE avcodecMod = NULL;
static HMODULE avformatMod = NULL;
static HMODULE avutilMod = NULL;
static HMODULE swresampleMod = NULL;
static HMODULE swscaleMod = NULL;

void log_callback_debug(void *ptr, int level, const char *fmt, va_list vl)
{
    using av_log_default_callback_ptr = void (__cdecl *)(void *avcl, int level, const char *fmt, va_list vl);
    using av_log_format_line_ptr = void(__cdecl *)(void *ptr, int level, const char *fmt, va_list vl,
        char *line, int line_size, int *print_prefix);
    static av_log_default_callback_ptr av_log_default_callback = nullptr;
    static av_log_format_line_ptr av_log_format_line = nullptr;

    if (avutilMod && !av_log_default_callback)
        av_log_default_callback = (av_log_default_callback_ptr)GetProcAddress(avutilMod, "av_log_default_callback");
    if (avutilMod && !av_log_format_line)
        av_log_format_line = (av_log_format_line_ptr)GetProcAddress(avutilMod, "av_log_format_line");

    va_list vl2;
    char line[1024];
    static int print_prefix = 1;

    va_copy(vl2, vl);
    if (av_log_default_callback)
        (av_log_default_callback)(ptr, level, fmt, vl);
    if (av_log_format_line)
        (av_log_format_line)(ptr, level, fmt, vl2, line, sizeof(line), &print_prefix);
    va_end(vl2);
    if (av_log_format_line && AV_LOG_DEBUG >= level) {
        OutputDebugStringA(line);
    }
}

bool av_load_dlls(void)
{
    static bool firstTime = true;

    if (firstTime) {
        firstTime = false;
        avcodecMod = LoadLibraryW(L"avcodec-57.dll");
        avformatMod = LoadLibraryW(L"avformat-57.dll");
        avutilMod = LoadLibraryW(L"avutil-55.dll");
        swresampleMod = LoadLibraryW(L"swresample-2.dll");
        swscaleMod = LoadLibraryW(L"swscale-4.dll");
    }

    return avcodecMod && avformatMod && avutilMod && swresampleMod && swscaleMod;
}

using av_log_set_callback_ptr = void (__cdecl *)(void(*callback)(void*, int, const char*, va_list));
using avcodec_register_all_ptr = void (__cdecl *)(void);
using av_register_all_ptr = void (__cdecl *)(void);
using avformat_alloc_output_context2_ptr = int (__cdecl *)(AVFormatContext **ctx, AVOutputFormat *oformat,
    const char *format_name, const char *filename);
using avcodec_find_encoder_by_name_ptr = AVCodec* (__cdecl *)(const char* name);
using avformat_new_stream_ptr = AVStream* (__cdecl *)(AVFormatContext *s, const AVCodec *c);
using av_packet_alloc_ptr = AVPacket* (__cdecl *)(void);
using avcodec_open2_ptr = int (__cdecl *)(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options);
using av_frame_alloc_ptr = AVFrame* (__cdecl *)(void);
using av_frame_get_buffer_ptr = int (__cdecl *)(AVFrame *frame, int align);
using avio_open_ptr = int (__cdecl *)(AVIOContext **s, const char *url, int flags);
using avformat_write_header_ptr = int (__cdecl *)(AVFormatContext *s, AVDictionary **options);
using av_write_trailer_ptr = int (__cdecl *)(AVFormatContext *s);
using avio_close_ptr = int (__cdecl *)(AVIOContext *s);
using avformat_free_context_ptr = void (__cdecl *)(AVFormatContext *s);
using av_free_ptr = void (__cdecl *)(void *ptr);
using av_packet_free_ptr = void (__cdecl *)(AVPacket **pkt);
using av_frame_make_writable_ptr = int (__cdecl *)(AVFrame *frame);
using av_rescale_q_ptr = int64_t (__cdecl *)(int64_t a, AVRational bq, AVRational cq) av_const;
using avcodec_send_frame_ptr = int (__cdecl *)(AVCodecContext *avctx, const AVFrame *frame);
using avcodec_receive_packet_ptr = int (__cdecl *)(AVCodecContext *avctx, AVPacket *avpkt);
using av_write_frame_ptr = int (__cdecl *)(AVFormatContext *s, AVPacket *pkt);
using av_packet_unref_ptr = void (__cdecl *)(AVPacket *pkt);
using sws_getContext_ptr = struct SwsContext* (__cdecl *)(int srcW, int srcH, enum AVPixelFormat srcFormat,
    int dstW, int dstH, enum AVPixelFormat dstFormat,
    int flags, SwsFilter *srcFilter,
    SwsFilter *dstFilter, const double *param);
using sws_freeContext_ptr = void (__cdecl *)(struct SwsContext *swsContext);
using sws_scale_ptr = int (__cdecl *)(struct SwsContext *c, const uint8_t *const srcSlice[],
    const int srcStride[], int srcSliceY, int srcSliceH,
    uint8_t *const dst[], const int dstStride[]);
using av_dict_set_ptr = int (__cdecl *)(AVDictionary **pm, const char *key, const char *value, int flags);


void my_av_log_set_callback(void(*callback)(void*, int, const char*, va_list))
{
    static av_log_set_callback_ptr av_log_set_callback = nullptr;

    if (avutilMod && !av_log_set_callback)
        av_log_set_callback = (av_log_set_callback_ptr)GetProcAddress(avutilMod, "av_log_set_callback");

    if (av_log_set_callback)
        (av_log_set_callback)(callback);
}

void my_avcodec_register_all(void)
{
    static avcodec_register_all_ptr avcodec_register_all = nullptr;

    if (avcodecMod && !avcodec_register_all)
        avcodec_register_all = (avcodec_register_all_ptr)GetProcAddress(avcodecMod, "avcodec_register_all");

    if (avcodec_register_all) (avcodec_register_all)();
}

void my_av_register_all(void)
{
    static av_register_all_ptr av_register_all = nullptr;

    if (avformatMod && !av_register_all)
        av_register_all = (av_register_all_ptr)GetProcAddress(avformatMod, "av_register_all");

    if (av_register_all) (av_register_all)();
}

int my_avformat_alloc_output_context2(AVFormatContext **ctx, AVOutputFormat *oformat,
    const char *format_name, const char *filename)
{
    static avformat_alloc_output_context2_ptr avformat_alloc_output_context2 = nullptr;

    if (avformatMod && !avformat_alloc_output_context2)
        avformat_alloc_output_context2 = (avformat_alloc_output_context2_ptr)GetProcAddress(avformatMod, "avformat_alloc_output_context2");

    return avformat_alloc_output_context2 ? (avformat_alloc_output_context2)(ctx, oformat, format_name, filename) : -EACCES;
}

AVCodec* my_avcodec_find_encoder_by_name(const char* name)
{
    static avcodec_find_encoder_by_name_ptr avcodec_find_encoder_by_name = nullptr;

    if (avcodecMod && !avcodec_find_encoder_by_name)
        avcodec_find_encoder_by_name = (avcodec_find_encoder_by_name_ptr)GetProcAddress(avcodecMod, "avcodec_find_encoder_by_name");

    return avcodec_find_encoder_by_name ? (avcodec_find_encoder_by_name)(name) : nullptr;
}

AVStream *my_avformat_new_stream(AVFormatContext *s, const AVCodec *c)
{
    static avformat_new_stream_ptr avformat_new_stream = nullptr;

    if (avformatMod && !avformat_new_stream)
        avformat_new_stream = (avformat_new_stream_ptr)GetProcAddress(avformatMod, "avformat_new_stream");

    return avformat_new_stream ? (avformat_new_stream)(s, c) : nullptr;
}

AVPacket *my_av_packet_alloc(void)
{
    static av_packet_alloc_ptr av_packet_alloc = nullptr;

    if (avcodecMod && !av_packet_alloc)
        av_packet_alloc = (av_packet_alloc_ptr)GetProcAddress(avcodecMod, "av_packet_alloc");

    return av_packet_alloc ? (av_packet_alloc)() : nullptr;
}

int my_avcodec_open2(AVCodecContext *avctx, const AVCodec *codec, AVDictionary **options)
{
    static avcodec_open2_ptr avcodec_open2 = nullptr;

    if (avcodecMod && !avcodec_open2)
        avcodec_open2 = (avcodec_open2_ptr)GetProcAddress(avcodecMod, "avcodec_open2");

    return avcodec_open2 ? (avcodec_open2)(avctx, codec, options) : -EACCES;
}

AVFrame* my_av_frame_alloc(void)
{
    static av_frame_alloc_ptr av_frame_alloc = nullptr;

    if (avutilMod && !av_frame_alloc)
        av_frame_alloc = (av_frame_alloc_ptr)GetProcAddress(avutilMod, "av_frame_alloc");

    return av_frame_alloc ? (av_frame_alloc)() : nullptr;
}

int my_av_frame_get_buffer(AVFrame *frame, int align)
{
    static av_frame_get_buffer_ptr av_frame_get_buffer = nullptr;

    if (avutilMod && !av_frame_get_buffer)
        av_frame_get_buffer = (av_frame_get_buffer_ptr)GetProcAddress(avutilMod, "av_frame_get_buffer");

    return av_frame_get_buffer ? (av_frame_get_buffer)(frame, align) : -EACCES;
}

int my_avio_open(AVIOContext **s, const char *url, int flags)
{
    static avio_open_ptr avio_open = nullptr;

    if (avformatMod && !avio_open)
        avio_open = (avio_open_ptr)GetProcAddress(avformatMod, "avio_open");

    return avio_open ? (avio_open)(s, url, flags) : -EACCES;
}

int my_avformat_write_header(AVFormatContext *s, AVDictionary **options)
{
    static avformat_write_header_ptr avformat_write_header = nullptr;

    if (avformatMod && !avformat_write_header)
        avformat_write_header = (avformat_write_header_ptr)GetProcAddress(avformatMod, "avformat_write_header");

    return avformat_write_header ? (avformat_write_header)(s, options) : -EACCES;
}

int my_av_write_trailer(AVFormatContext *s)
{
    static av_write_trailer_ptr av_write_trailer = nullptr;

    if (avformatMod && !av_write_trailer)
        av_write_trailer = (av_write_trailer_ptr)GetProcAddress(avformatMod, "av_write_trailer");

    return av_write_trailer ? (av_write_trailer)(s) : -EACCES;
}

int my_avio_close(AVIOContext *s)
{
    static avio_close_ptr avio_close = nullptr;

    if (avformatMod && !avio_close)
        avio_close = (avio_close_ptr)GetProcAddress(avformatMod, "avio_close");

    return avio_close ? (avio_close)(s) : -EACCES;
}

void my_avformat_free_context(AVFormatContext *s)
{
    static avformat_free_context_ptr avformat_free_context = nullptr;

    if (avformatMod && !avformat_free_context)
        avformat_free_context = (avformat_free_context_ptr)GetProcAddress(avformatMod, "avformat_free_context");

    if (avformat_free_context)
        (avformat_free_context)(s);
}

void my_av_free(void *ptr)
{
    static av_free_ptr av_free = nullptr;

    if (avutilMod && !av_free)
        av_free = (av_free_ptr)GetProcAddress(avutilMod, "av_free");

    if (av_free)
        (av_free)(ptr);
}

void my_av_packet_free(AVPacket **pkt)
{
    static av_packet_free_ptr av_packet_free = nullptr;

    if (avcodecMod && !av_packet_free)
        av_packet_free = (av_packet_free_ptr)GetProcAddress(avcodecMod, "av_packet_free");

    if (av_packet_free)
        (av_packet_free)(pkt);
}

int my_av_frame_make_writable(AVFrame *frame)
{
    static av_frame_make_writable_ptr av_frame_make_writable = nullptr;

    if (avutilMod && !av_frame_make_writable)
        av_frame_make_writable = (av_frame_make_writable_ptr)GetProcAddress(avutilMod, "av_frame_make_writable");

    return av_frame_make_writable ? (av_frame_make_writable)(frame) : -EACCES;
}

int64_t my_av_rescale_q(int64_t a, AVRational bq, AVRational cq) av_const
{
    static av_rescale_q_ptr av_rescale_q = nullptr;

    if (avutilMod && !av_rescale_q)
        av_rescale_q = (av_rescale_q_ptr)GetProcAddress(avutilMod, "av_rescale_q");

    return av_rescale_q ? (av_rescale_q)(a, bq, cq) : 0;
}

int my_avcodec_send_frame(AVCodecContext *avctx, const AVFrame *frame)
{
    static avcodec_send_frame_ptr avcodec_send_frame = nullptr;

    if (avcodecMod && !avcodec_send_frame)
        avcodec_send_frame = (avcodec_send_frame_ptr)GetProcAddress(avcodecMod, "avcodec_send_frame");

    return avcodec_send_frame ? (avcodec_send_frame)(avctx, frame) : -EACCES;
}

int my_avcodec_receive_packet(AVCodecContext *avctx, AVPacket *avpkt)
{
    static avcodec_receive_packet_ptr avcodec_receive_packet = nullptr;

    if (avcodecMod && !avcodec_receive_packet)
        avcodec_receive_packet = (avcodec_receive_packet_ptr)GetProcAddress(avcodecMod, "avcodec_receive_packet");

    return avcodec_receive_packet ? (avcodec_receive_packet)(avctx, avpkt) : -EACCES;
}

int my_av_write_frame(AVFormatContext *s, AVPacket *pkt)
{
    static av_write_frame_ptr av_write_frame = nullptr;

    if (avformatMod && !av_write_frame)
        av_write_frame = (av_write_frame_ptr)GetProcAddress(avformatMod, "av_write_frame");

    return av_write_frame ? (av_write_frame)(s, pkt) : -EACCES;
}

void my_av_packet_unref(AVPacket *pkt)
{
    static av_packet_unref_ptr av_packet_unref = nullptr;

    if (avcodecMod && !av_packet_unref)
        av_packet_unref = (av_packet_unref_ptr)GetProcAddress(avcodecMod, "av_packet_unref");

    if (av_packet_unref)
        (av_packet_unref)(pkt);
}

struct SwsContext* my_sws_getContext(int srcW, int srcH, enum AVPixelFormat srcFormat,
    int dstW, int dstH, enum AVPixelFormat dstFormat,
    int flags, SwsFilter *srcFilter,
    SwsFilter *dstFilter, const double *param)
{
    static sws_getContext_ptr sws_getContext = nullptr;

    if (swscaleMod && !sws_getContext)
        sws_getContext = (sws_getContext_ptr)GetProcAddress(swscaleMod, "sws_getContext");

    return sws_getContext ? (sws_getContext)(srcW, srcH, srcFormat,
        dstW, dstH, dstFormat, flags, srcFilter, dstFilter, param)
                          : nullptr;
}

void my_sws_freeContext(struct SwsContext *swsContext)
{
    static sws_freeContext_ptr sws_freeContext = nullptr;

    if (swscaleMod && !sws_freeContext)
        sws_freeContext = (sws_freeContext_ptr)GetProcAddress(swscaleMod, "sws_freeContext");

    if (sws_freeContext)
        (sws_freeContext)(swsContext);
}

int my_sws_scale(struct SwsContext *c, const uint8_t *const srcSlice[],
    const int srcStride[], int srcSliceY, int srcSliceH,
    uint8_t *const dst[], const int dstStride[])
{
    static sws_scale_ptr sws_scale = nullptr;

    if (swscaleMod && !sws_scale)
        sws_scale = (sws_scale_ptr)GetProcAddress(swscaleMod, "sws_scale");

    return sws_scale ? (sws_scale)(c, srcSlice, srcStride, srcSliceY, srcSliceH, dst, dstStride)
                     : 0;
}

int my_av_dict_set(AVDictionary **pm, const char *key, const char *value, int flags)
{
    static av_dict_set_ptr av_dict_set = nullptr;

    if (avutilMod && !av_dict_set)
        av_dict_set = (av_dict_set_ptr)GetProcAddress(avutilMod, "av_dict_set");

    return av_dict_set ? (av_dict_set)(pm, key, value, flags) : -EACCES;
}
