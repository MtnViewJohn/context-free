// WinPngCanvas.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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

#include "WinPngCanvas.h"
#include <stdlib.h>
#define ULONG_PTR ULONG
#include <windows.h>
#include <gdiplus.h>
#include "makeCFfilename.h"

using namespace std;
using namespace Gdiplus;

static ColorPalette* GrayPalette = 0;
static ULONG_PTR GdiPToken;
static GdiplusStartupInput GdiPStartInput;
static GdiplusStartupOutput GdiPStartOutput;
int pngCanvas::CanvasCount = 0;

pngCanvas::pngCanvas(const char* outfilename, bool quiet, int width, int height, 
                     aggCanvas::PixelFormat pixfmt, bool crop, int frameCount,
                     int variation)
    : aggCanvas(pixfmt), mTiledCanvas(0), mData(0), 
	  mOutputFileName(outfilename), mFrameCount(frameCount), 
	  mCurrentFrame(0), mPixelFormat(pixfmt), mCrop(crop), mQuiet(quiet),
      mVariation(variation)
{
    if (CanvasCount++ == 0)
        GdiplusStartup(&GdiPToken, &GdiPStartInput, &GdiPStartOutput);

	mWidth = width;
	mHeight = height;
	if (quiet) return;
    cout << width << "w x " << height << "h pixel image." << endl;
    cout << "Generating..." << endl;
}

pngCanvas::~pngCanvas()
{
    if (--CanvasCount == 0) {
        GdiplusShutdown(GdiPToken);
        if (GrayPalette)
            free((void*)GrayPalette);
    }
    delete[] mData;
}

void pngCanvas::start(bool clear, const agg::rgba& bk, int width, int height)
{
	if (!mFrameCount && !mQuiet)
        cout << endl << "Rendering..." << endl;

    if (mCrop) {
        mWidth = width;
        mHeight = height;
    }

    mStride = mWidth * aggCanvas::BytesPerPixel[mPixelFormat];
    mStride += ((-mStride) & 3);
    mData = new unsigned char[mStride * mHeight];
    mBackground = bk;
    attach(mData, mWidth, mHeight, mStride);

    aggCanvas::start(clear, bk, width, height);
}

void pngCanvas::end()
{
	aggCanvas::end();
	
	string name = makeCFfilename(mOutputFileName, mCurrentFrame, mFrameCount,
	                             mVariation);
	
	if (mFrameCount) {
		output(name.c_str(), mCurrentFrame++);
	} else {
		output(name.c_str());
	}
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
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
    // If the canvas is 16-bit then copy it to an 8-bit version
    // and output that. GDI+ doesn't really support 16-bit modes.
    if (mPixelFormat & aggCanvas::Has_16bit_Color) {
        pngCanvas* eight = new pngCanvas(outfilename, mQuiet, mWidth, mHeight,
            (aggCanvas::PixelFormat)(mPixelFormat & (~ aggCanvas::Has_16bit_Color)),
            mCrop, mFrameCount, mVariation);
        if (mFrameCount) 
            eight->mCurrentFrame = mCurrentFrame - 1;
        eight->start(true, mBackground, mWidth, mHeight);
        eight->copy(mData, mWidth, mHeight, mStride, mPixelFormat);
        eight->end();
        delete eight;
        return;
    }

    WCHAR wpath[MAX_PATH];
	size_t cvt;
    ::mbstowcs_s(&cvt, wpath, MAX_PATH, outfilename, MAX_PATH);

    if (encClsid == CLSID_NULL && GetEncoderClsid(L"image/png", &encClsid) == -1) {
        cerr << endl << "Image encoder missing from GDI+!" << endl;
        return;
    } 

	if (mPixelFormat == aggCanvas::Gray8_Blend && !GrayPalette) {
        GrayPalette = (ColorPalette*)malloc(sizeof(ColorPalette) + 256*sizeof(ARGB));
        GrayPalette->Count = 256;
        GrayPalette->Flags = PaletteFlagsGrayScale;
        for (int i = 0; i < 256; i++)
            GrayPalette->Entries[i] = Color::MakeARGB(255, (BYTE)i, (BYTE)i, (BYTE)i);
	}

    Bitmap* bm;
    BYTE* data = (BYTE*)mData;
    int width = mWidth;
    int height = mHeight;
    if (mCrop) {
        width = cropWidth();
        height = cropHeight();
        data += mStride * cropY() + 
                aggCanvas::BytesPerPixel[mPixelFormat] * cropX();
    }

    switch (mPixelFormat) {
        case aggCanvas::Gray8_Blend:
            bm = new Bitmap(width, height, mStride, PixelFormat8bppIndexed, data);
            bm->SetPalette(GrayPalette);
            break;
        case aggCanvas::RGB8_Blend:
            bm = new Bitmap(width, height, mStride, PixelFormat24bppRGB, data);
            break;
        case aggCanvas::RGBA8_Blend:
            bm = new Bitmap(width, height, mStride, PixelFormat32bppPARGB, data);
            break;
        default:
            bm = 0;
            break;
    }

	Bitmap* saveBM = bm;

	if (frame == -1 && !mQuiet) {
        cout << endl << "Writing "
             << width << "w x " << height << "h pixel image..." << endl;
	}

	if (mTiledCanvas) {
	    agg::point_i factor;
		if (mTiledCanvas->isRectangular(&factor.x, &factor.y)) {
			int srcWidth = bm->GetWidth();
			int srcHeight = bm->GetHeight();
	#ifdef _DEBUG
	#undef new
	#endif
			Gdiplus::PixelFormat fmt = (bm->GetPixelFormat() & PixelFormatAlpha) ? 
				PixelFormat32bppPARGB : PixelFormat24bppRGB;

			saveBM = new Bitmap(srcWidth * factor.x, srcHeight * factor.y, fmt);
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#endif
			Graphics g(saveBM);

			tileList points = 
				mTiledCanvas->getTesselation(saveBM->GetWidth(), saveBM->GetHeight(),
											 0, 0, true);
	        
			for (tileList::iterator pt = points.begin(); 
				 pt != points.end(); pt++) {
				Gdiplus::Rect destRect(pt->x, pt->y, srcWidth, srcHeight);

				g.DrawImage(bm, destRect, 0, 0, srcWidth, srcHeight,
					UnitPixel, NULL, NULL, NULL);
			}

			delete bm;
		} else {
			cerr << endl << "Cannot generate a rectangular tiled output." << endl;
		}
    }

    PropertyItem pi;
    pi.id = PropertyTagImageDescription;
    pi.type = PropertyTagTypeASCII;
    pi.length = strlen("Context Free generated image") + 1;
    pi.value = (VOID*)"Context Free generated image";
    saveBM->SetPropertyItem(&pi);

    Status s = saveBM->Save(wpath, &encClsid, NULL);

	if (s != Ok){
		cerr << endl << "A GDI+ error occured during PNG write: " << 
			errorMsg[s];
        if (s == Gdiplus::Win32Error) {
            LPVOID lpMsgBuf;
            DWORD dw = ::GetLastError(); 

            ::FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                dw,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPSTR) &lpMsgBuf,
                0, NULL );

            cerr<< ": " << (char*)lpMsgBuf;

            LocalFree(lpMsgBuf);
        }
        cerr << endl;
    }

    delete saveBM;
}


