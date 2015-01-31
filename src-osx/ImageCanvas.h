// ImageCanvas.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2009-2011 John Horigan - john@glyphic.com
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

@class GView;
@class BitmapImageHolder;

#include "aggCanvas.h"

class ImageCanvas : public aggCanvas
{
public:
    ImageCanvas(GView* view, BitmapImageHolder* bitmap, PixelFormat format);
    ~ImageCanvas() override;
    
    void start(bool clear, const agg::rgba& background,
                int width, int height) override;
    void end() override;
                
private:
    GView*   mView;
};

