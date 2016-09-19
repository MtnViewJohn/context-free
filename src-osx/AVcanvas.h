// AVcanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2016 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_AVcanvas_h
#define INCLUDE_AVcanvas_h

@class NSString;
@class NSError;
@class AVimpl;
@class BitmapImageHolder;

#include "aggCanvas.h"

class AVcanvas : public aggCanvas {
public:
    enum VideoFormat {
        H264, ProRes422, ProRes4444
    };
    AVcanvas(NSString* name, BitmapImageHolder* bits, int fps, VideoFormat format);
    ~AVcanvas() override;
    AVcanvas& operator=(const AVcanvas& c) = delete;
    
    void end() override;
    
private:
    AVimpl* impl;
};


#endif /* INCLUDE_AVcanvas_h */
