// WinPngCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2013 John Horigan - john@glyphic.com
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

#define NOMINMAX
#include <windows.h>
#include "WinPngCanvas.h"
#include <stdlib.h>
#include "makeCFfilename.h"

#ifndef ULONG_PTR
#define ULONG_PTR ULONG
#endif
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#include <gdiplus.h>

using namespace std;
using namespace Gdiplus;

static ColorPalette* GrayPalette = nullptr;
static ULONG_PTR GdiPToken;
static GdiplusStartupInput GdiPStartInput;
static GdiplusStartupOutput GdiPStartOutput;
int pngCanvas::CanvasCount = 0;

pngCanvas::pngCanvas(const char* outfilename, bool quiet, int width, int height, 
                     PixelFormat pixfmt, bool crop, int frameCount,
                     int variation, bool wallpaper, Renderer *r, int mx, int my)
    : abstractPngCanvas(outfilename, quiet, 
                        wallpaper ? ::GetSystemMetrics(SM_CXFULLSCREEN) : width, 
                        wallpaper ? ::GetSystemMetrics(SM_CYFULLSCREEN) : height, 
                        pixfmt, crop, frameCount, variation, wallpaper, r, mx, my)
{
    if (CanvasCount++ == 0)
        GdiplusStartup(&GdiPToken, &GdiPStartInput, &GdiPStartOutput);
}

pngCanvas::~pngCanvas()
{
    if (--CanvasCount == 0) {
        GdiplusShutdown(GdiPToken);
        if (GrayPalette)
            free((void*)GrayPalette);
    }
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = nullptr;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == nullptr)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

static LPCSTR errorMsg[] = {
    "Ok",
    "Generic Error",
    "Invalid Parameter",
    "Out Of Memory",
    "Object Busy",
    "Insufficient Buffer",
    "Not Implemented",
    "Win32 Error",
    "Wrong State",
    "Aborted",
    "File Not Found",
    "Value Overflow",
    "Access Denied",
    "Unknown Image Format",
    "Font Family Not Found",
    "Font Style Not Found",
    "Not TrueType Font",
    "Unsupported Gdiplus Version",
    "Gdiplus Not Initialized",
    "Property Not Found",
    "Property Not Supported",
    "Profile Not Found"
};

static CLSID encClsid = CLSID_NULL;

void pngCanvas::output(const char* outfilename, int frame)
{
    int width = mFullWidth;
    int height = mFullHeight;
    // If the canvas is 16-bit then copy it to an 8-bit version
    // and output that. GDI+ doesn't really support 16-bit modes.
    unsigned char* data = mData.get();
    int stride = mStride;
    int bpp = BytesPerPixel.at(mPixelFormat);
    std::unique_ptr<unsigned char[]> data8;
    PixelFormat pf = mPixelFormat;
    if (pf & Has_16bit_Color) {
        stride = stride >> 1;
        stride += ((-stride) & 3);
        data8.reset(new unsigned char[stride * height]);
        bpp = bpp >> 1;
        unsigned char* row8 = data8.get();
        unsigned char* srcrow = mData.get();
        for (int y = 0; y < height; ++y) {
            unsigned __int16* row16 = (unsigned __int16*)srcrow;
            for (int x = 0; x < width; ++x)
                row8[x] = row16[x] >> 8;
            row8 += stride;
            srcrow += mStride;
        }
        data = data8.get();
        pf = (PixelFormat)(pf & (~Has_16bit_Color));
    }

    if (mCrop) {
        width = cropWidth();
        height = cropHeight();
        data += cropY() * stride + cropX() * BytesPerPixel.at(pf);
    }

    WCHAR wpath[MAX_PATH];
    TCHAR fullpath[MAX_PATH];
    size_t cvt;
    ::mbstowcs_s(&cvt, wpath, MAX_PATH, outfilename, MAX_PATH);
    ::GetFullPathName(wpath, MAX_PATH, fullpath, nullptr);
    const WCHAR* mimetype = mWallpaper ? L"image/bmp" : L"image/png";

    if (encClsid == CLSID_NULL && GetEncoderClsid(mimetype, &encClsid) == -1) {
        cerr << endl << "Image encoder missing from GDI+!" << endl;
        return;
    } 

    if (pf == aggCanvas::Gray8_Blend && !GrayPalette) {
        GrayPalette = (ColorPalette*)malloc(sizeof(ColorPalette) + 256*sizeof(ARGB));
        GrayPalette->Count = 256;
        GrayPalette->Flags = PaletteFlagsGrayScale;
        for (int i = 0; i < 256; i++)
            GrayPalette->Entries[i] = Color::MakeARGB(255, (BYTE)i, (BYTE)i, (BYTE)i);
    }

    std::unique_ptr<Bitmap> saveBM;

    switch (pf) {
        case aggCanvas::Gray8_Blend:
            saveBM.reset(new Bitmap(width, height, stride, PixelFormat8bppIndexed, data));
            saveBM->SetPalette(GrayPalette);
            break;
        case aggCanvas::RGB8_Blend:
            saveBM.reset(new Bitmap(width, height, stride, PixelFormat24bppRGB, data));
            break;
        case aggCanvas::RGBA8_Blend:
            saveBM.reset(new Bitmap(width, height, stride, PixelFormat32bppPARGB, data));
            break;
        default:
            break;
    }

    if (frame == -1 && !mQuiet) {
        cerr << endl << "Writing "
             << width << "w x " << height << "h pixel image..." << endl;
    }

    PropertyItem pi;
    pi.id = PropertyTagImageDescription;
    pi.type = PropertyTagTypeASCII;
    pi.length = (ULONG)strlen("Context Free generated image") + 1;
    pi.value = (VOID*)"Context Free generated image";
    if (saveBM) saveBM->SetPropertyItem(&pi);

    Status s = saveBM ? saveBM->Save(wpath, &encClsid, NULL) : Gdiplus::UnknownImageFormat;

    if (s != Ok){
        cerr << endl << "A GDI+ error occured during PNG write: " << 
            errorMsg[s];
        if (s == Gdiplus::Win32Error) {
            LPVOID lpMsgBuf;
            DWORD dw = ::GetLastError(); 

            ::FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM,
                nullptr,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPSTR) &lpMsgBuf,
                0, nullptr );

            cerr << ": " << (char*)lpMsgBuf;

            LocalFree(lpMsgBuf);
        }
        cerr << endl;
    } else if (mWallpaper && frame == -1) {
        SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (LPVOID)fullpath, 
                             SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
    }

    return;
}


