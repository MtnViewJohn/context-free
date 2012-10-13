// tiledAggCanvas.cpp
// Context Free
// ---------------------
// Copyright (C) 2012 John Horigan - john@glyphic.com
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

#include "abstractPngCanvas.h"
#include "tiledCanvas.h"
#include "makeCFfilename.h"
#include <string>
#include <iostream>

using namespace std;

abstractPngCanvas::abstractPngCanvas(const char* outfilename, bool quiet, int width, int height, 
                                     aggCanvas::PixelFormat pixfmt, bool crop, int frameCount,
                                     int variation, bool wallpaper, Renderer *r, int mx, int my)
: aggCanvas(pixfmt), mOutputFileName(outfilename), mFrameCount(frameCount), 
  mCurrentFrame(0), mVariation(variation), mData(0), mPixelFormat(pixfmt), 
  mCrop(crop), mQuiet(quiet), mWallpaper(wallpaper), mRenderer(r), mFullWidth(width), 
  mFullHeight(height), mOriginX(0), mOriginY(0)
{
    if (wallpaper) {
        mWidth = r->m_width;
        mHeight = r->m_height;
        mFullWidth = width;
        mFullHeight = height;

        double scalex = (double)width /  ( mWidth * mx);
        double scaley = (double)height / (mHeight * my);
        double scale = scalex < scaley ? scalex : scaley;
        mWidth *= scale;
        mHeight *= scale;
    } else {
        mWidth = width;
        mHeight = height;
        mFullWidth = mWidth * mx;
        mFullHeight = mHeight * my;
    }
    
    mOriginX = (mFullWidth - mWidth) / 2;
    mOriginY = (mFullHeight - mHeight) / 2;
    
    mStride = mFullWidth * aggCanvas::BytesPerPixel[mPixelFormat];
#ifdef _WIN32
    mStride += ((-mStride) & 3);
#endif
    mData = new unsigned char[mStride * height];
    attach(mData + mOriginY * mStride + mOriginX * BytesPerPixel[mPixelFormat], 
           mWidth, mHeight, mStride);

    if (quiet) return;
    cout << mFullWidth << "w x " << mFullHeight << "h pixel image." << endl;
    cout << "Generating..." << endl;
}

abstractPngCanvas::~abstractPngCanvas()
{
    delete[] mData;
}

void
abstractPngCanvas::start(bool clear, const agg::rgba &bk, int width, int height)
{
    if (!mFrameCount && !mQuiet)
        cout << endl << "Rendering..." << endl;
    
    aggCanvas::start(clear, bk, width, height);
}

void
abstractPngCanvas::end()
{
    aggCanvas::end();
    
    if (mRenderer && mRenderer->m_tiledCanvas) {
        tileList points;
        mRenderer->m_tiledCanvas->getTesselation(points, mFullWidth, mFullHeight,
                                                 mOriginX, mOriginY, true);
        
        for (tileList::reverse_iterator pt = points.rbegin(), ept = points.rend();
             pt != ept; ++pt)
        {
            if (pt->x != mOriginX || pt->y != mOriginY)
                copyImageUnscaled(pt->x, pt->y);
        }
        
    }
    
    string name = makeCFfilename(mOutputFileName, mCurrentFrame, mFrameCount,
                                 mVariation);
    
    if (mFrameCount) {
        output(name.c_str(), mCurrentFrame++);
    } else {
        output(name.c_str());
    }
}

void
abstractPngCanvas::copyImageUnscaled(int destx, int desty)
{
    destx *= BytesPerPixel[mPixelFormat];
    int srcx = mOriginX * BytesPerPixel[mPixelFormat];
    int srcy = mOriginY;
    for (int y = 0; y < mHeight; ++y) {
        if (y + desty < 0 || y + desty >= mFullHeight) continue;
        for (int x = 0; x < mWidth * BytesPerPixel[mPixelFormat]; ++x) {
            if (destx + x >= 0 && destx + x < mStride)
                mData[(y + desty) * mStride + destx + x] = mData[(y + srcy) * mStride + srcx + x];
        }
    }
}
