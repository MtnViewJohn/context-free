// ffCanvasDummy.cpp
// this file is part of Context Free
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

#define __STDC_CONSTANT_MACROS 1

#include "ffCanvas.h"

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

class ffCanvas::Impl
// We need to declare this to make std::unique_ptr<ffCanvas::Impl> happy, even though
// it is never constructed or destroyed.
{
public:
    Impl() = default;
    ~Impl() = default;
};


ffCanvas::ffCanvas(const char* name, PixelFormat fmt, int width, int height, int fps)
: aggCanvas(mapPixFmt(fmt)), mErrorMsg("Quicktime support not compiled in")
{
    width &= ~3;
    height &= ~3;
    mError = true;
}

ffCanvas::~ffCanvas() = default;

void
ffCanvas::end()
{
    aggCanvas::end();
}

