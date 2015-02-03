// tiledAggCanvas.h
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

#ifndef INCLUDE_ABSTRACTPNGCANVAS_H
#define INCLUDE_ABSTRACTPNGCANVAS_H

#include "aggCanvas.h"

class abstractPngCanvas : public aggCanvas {
public:
    abstractPngCanvas(const char* outfilename, bool quiet, int width, int height, 
                      PixelFormat pixfmt, bool crop, int frameCount,
                      int variation, bool wallpaper, Renderer *r, int mx, int my);
    ~abstractPngCanvas() override;
    void start(bool , const agg::rgba& , int , int ) override;
    void end() override;
    
protected:
    const char* mOutputFileName;
    int mFrameCount;
    int mCurrentFrame;
    int  mVariation;

    std::unique_ptr<unsigned char[]> mData;
    int mStride;
    PixelFormat mPixelFormat;
    bool mCrop;
    bool mQuiet;
    bool mWallpaper;
    
    Renderer* mRenderer;
    int mFullWidth;
    int mFullHeight;
    int mOriginX;
    int mOriginY;
    
    void copyImageUnscaled(int x, int y);
    virtual void output(const char * outfilename, int frame = -1) = 0;
};


#endif  // INCLUDE_ABSTRACTPNGCANVAS_H
