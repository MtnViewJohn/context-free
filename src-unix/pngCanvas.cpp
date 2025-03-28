// pngCanvas.cpp
// Context Free
// ---------------------
// Copyright (C) 2005-2007 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2007-2013 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
// John Horigan can be contacted at john@glyphic.com or at
// John Horigan, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "pngCanvas.h"
#include "png.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "prettyint.h"

#ifndef _WIN32
#include <arpa/inet.h>
#include <unistd.h>
#else
#include <io.h>
#include <fcntl.h>

namespace {
    unsigned short htons(unsigned short s)
    {
        return ((s & 0xff) << 8) | ((s & 0xff00) >> 8);
    }
}
#endif

using std::cerr;
using std::endl;

namespace {
    void
    pngWriteError(png_structp, png_const_charp message)
    {
        cerr << message << endl;
        throw false;
    }

    void
    pngWriteWarning(png_structp, png_const_charp message)
    {
        cerr << message << endl;
    }
}

namespace {
    struct FileCloser
    {
        void operator()(std::FILE* ptr) const {
            if (ptr != stdout)
                std::fclose(ptr);        // Not called if nullptr
        }
    };
}

void pngCanvas::output(const char* outfilename, int frame)
{
    std::unique_ptr<std::FILE, FileCloser> out;
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;

    std::unique_ptr<png_byte[]> row;
    std::unique_ptr<png_uint_16[]> row16;
    if (mPixelFormat & Has_16bit_Color)
        row16 = std::make_unique<png_uint_16[]>(mStride);
    else
        row = std::make_unique<png_byte[]>(mStride);
    
    try {
        png_ptr = png_create_write_struct(
            PNG_LIBPNG_VER_STRING,
            0, pngWriteError, pngWriteWarning);
        if (!png_ptr) throw "couldn't create png write struct";

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr) throw "couldn't create png info struct";

        if (*outfilename || usetmpfile) {
            if (usetmpfile) {
#ifdef _WIN32
                FILE* fp = nullptr;
                mFileName = "cfdg_temp_image_XXXXXX.png";
                if (_mktemp_s(mFileName.data(), mFileName.length() + 1) == 0 &&
                    fopen_s(&fp, mFileName.c_str(), "wb"))
                {
                    out.reset(fp);
                }
#else
                mFileName = "/tmp/cfdg_temp_image_XXXXXX.png";
                int fd = mkstemps(mFileName.data(), 4);
                if (fd != -1)
                    out.reset(fdopen(fd, "w"));
#endif
            } else {
                FILE* fp = nullptr;
#ifdef _WIN32
                fopen_s(&fp, outfilename, "wb");
#else
                fp = std::fopen(outfilename, "wb");
#endif
                if (fp)
                    out.reset(fp);
            }
        } else {
            out.reset(stdout);
#ifdef _WIN32
            _setmode(_fileno(stdout), _O_BINARY);
#endif
        }
        if (!out) {
            cerr << "Couldn't open " << outfilename << "\n";
            throw false;
        }
        
        if (setjmp(png_jmpbuf(png_ptr)))
            throw "Unspecified PNG output failure.";

        png_init_io(png_ptr, out.get());
        
        int pngFormat;
        switch (mPixelFormat) {
            case aggCanvas::RGBA8_Blend:
            case aggCanvas::RGBA16_Blend:
            case aggCanvas::RGBA8_Custom_Blend:
            case aggCanvas::RGBA16_Custom_Blend:
                pngFormat = PNG_COLOR_TYPE_RGB_ALPHA;
                break;
            case aggCanvas::RGB8_Blend:
            case aggCanvas::RGB16_Blend:
                pngFormat = PNG_COLOR_TYPE_RGB;
                break;
            case aggCanvas::Gray8_Blend:
            case aggCanvas::Gray16_Blend:
                pngFormat = PNG_COLOR_TYPE_GRAY;
                break;
            default:
                throw "Unknown pixel format";
        }
        
        int width = mFullWidth;
        int height = mFullHeight;
        int srcx = 0;
        int srcy = 0;
        if (mCrop && (!mRenderer || !mRenderer->m_tiledCanvas)) {
            width = cropWidth();
            height = cropHeight();
            srcx = cropX();
            srcy = cropY();
        }

        if (frame == -1 && !mQuiet) {
            cerr << endl << "Writing "
                 << prettyInt(static_cast<unsigned long>(width)) << "w x "
                 << prettyInt(static_cast<unsigned long>(height)) << "h pixel image..." << endl;
        } 
        
        png_set_IHDR(png_ptr, info_ptr,
            width, height, (mPixelFormat & Has_16bit_Color) + 8, pngFormat,
            PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);

        char myKey[] = "Software", myValue[] = "Context Free";
        
        png_text comments[1];
        std::memset(comments, 0, sizeof(comments));
        comments[0].compression = PNG_TEXT_COMPRESSION_NONE;
        comments[0].key = myKey;
        comments[0].text = myValue;
        comments[0].text_length = strlen(comments[0].text);
        png_set_text(png_ptr, info_ptr,
            comments, sizeof(comments)/sizeof(comments[0]));

        png_write_info(png_ptr, info_ptr);

        png_bytep rowPtr = mData.data() + srcy * mStride + srcx * aggCanvas::BytesPerPixel.at(mPixelFormat);
        for (int r = 0; r < height; ++r) {
            if (mPixelFormat == aggCanvas::RGBA8_Blend || mPixelFormat == aggCanvas::RGBA8_Custom_Blend) {
                // Convert each row to non-premultiplied alpha as per PNG spec
                // This is done in a separate array instead of in-situ because
                // for animations the main buffer might be drawn into again
                for (int c = 0; c < width * 4; c += 4) {
                    agg::rgba8 pix(rowPtr[c + 0], rowPtr[c + 1], rowPtr[c + 2], rowPtr[c + 3]);
                    pix.demultiply();
                    row[c + 0] = pix.r; 
                    row[c + 1] = pix.g;
                    row[c + 2] = pix.b; 
                    row[c + 3] = pix.a;
                }
                png_write_row(png_ptr, row.get());
            } else if (mPixelFormat == aggCanvas::RGBA16_Blend || mPixelFormat == aggCanvas::RGBA16_Custom_Blend) {
                // Ditto for rgba16
                png_uint_16p rowPtr16 = reinterpret_cast<png_uint_16p>(rowPtr);
                for (int c = 0; c < width * 4; c += 4) {
                    agg::rgba16 pix(rowPtr16[c + 0], rowPtr16[c + 1], rowPtr16[c + 2], rowPtr16[c + 3]);
                    pix.demultiply();
                    row16[c + 0] = htons(pix.r);    // Also convert to network byte order
                    row16[c + 1] = htons(pix.g);
                    row16[c + 2] = htons(pix.b); 
                    row16[c + 3] = htons(pix.a);
                }
                png_write_row(png_ptr, reinterpret_cast<png_bytep>(row16.get()));
            } else if (mPixelFormat & Has_16bit_Color) {
                // Convert rgb16/gray16 to network byte order
                png_uint_16p rowPtr16 = reinterpret_cast<png_uint_16p>(rowPtr);
                for (int c = 0; c < width * (BytesPerPixel.at(mPixelFormat) >> 1); ++c) 
                    row16[c] = htons(rowPtr16[c]);
                png_write_row(png_ptr, reinterpret_cast<png_bytep>(row16.get()));
            } else {
                png_write_row(png_ptr, rowPtr);
            }
            rowPtr += mStride;
        }

        png_write_end(png_ptr, 0);
    }
    catch (const char* msg) {
        cerr << "***" << msg << endl;
    }
    catch (bool) { }
    
    if (png_ptr)    png_destroy_write_struct(&png_ptr, &info_ptr);
}


