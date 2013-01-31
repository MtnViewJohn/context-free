// WinCanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2011 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_WINCANVAS_H
#define INCLUDE_WINCANVAS_H

#include "cfdg.h"
#include "aggCanvas.h"

class WinSystem;

class WinCanvas : public aggCanvas
{
public:
    WinCanvas(WinSystem* sys, aggCanvas::PixelFormat pixfmt, 
        int width, int height, agg::rgba bkgrnd);
    WinCanvas(const WinCanvas&);                // declare but do not implement
    WinCanvas& operator=(const WinCanvas&);     // declare but do not implement
    ~WinCanvas();

    int mStride;
    aggCanvas::PixelFormat mPixelFormat;
    char* mBM;
    agg::rgba mBackground;
    bool mNoUpdate;
    
    void start(bool clear, const agg::rgba& bk, int, int);
    void end();
    WinCanvas* Make8bitCopy();
    
protected:
    WinSystem* mSystem;
};

#endif // INCLUDE_WINCANVAS_H