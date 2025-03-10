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
#include <memory>

class WinSystem;
class WinCanvas;

using wincanvas_ptr = std::unique_ptr<WinCanvas>;

class WinCanvas : public aggCanvas
{
public:
    WinCanvas(WinSystem* sys, aggCanvas::PixelFormat pixfmt, 
        int width, int height, agg::rgba bkgrnd);
    WinCanvas(const WinCanvas&) = delete;
    WinCanvas& operator=(const WinCanvas&) = delete;

    int mStride;
    aggCanvas::PixelFormat mPixelFormat;
    std::unique_ptr<uint32_t[]> mBM;
    agg::rgba mBackground;
    bool mNoUpdate;
    
    void start(bool clear, const agg::rgba& bk, int, int);
    void end();
    void Make8bitCopy(wincanvas_ptr& canvas8);
    char* bitmap();
    
protected:
    WinSystem* mSystem;
};

#endif // INCLUDE_WINCANVAS_H