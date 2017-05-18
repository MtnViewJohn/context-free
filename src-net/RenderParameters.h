// RenderParameters.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2017 John Horigan - john@glyphic.com
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

#pragma once

#include "Form1.h"

namespace ContextFreeNet {

    public value class RenderParameters
    {
    public:
        enum class RenderActions { Render, Animate, SaveSVG };
        RenderActions action;
        bool    periodicUpdate;
        bool	animateZoom;
        bool    suppressDisplay;
        int		animateFrameCount;
        int     width;
        int     height;
        double  minimumSize;
        double  borderSize;
        int     animateWidth;
        int     animateHeight;
        int     length;
        int     frameRate;
        int     frame;
        bool    animateFrame;
        int     codec;
        bool    preview;

        void initFromPrefs()
        {
            periodicUpdate = Form1::prefs->ProgressiveRender;
            suppressDisplay = Form1::prefs->DontDisplay;
            animateZoom = Form1::prefs->AnimateZoom;
            width = Form1::prefs->RenderWidth;
            height = Form1::prefs->RenderHeight;
            borderSize = Form1::prefs->BorderWidth;
            minimumSize = Form1::prefs->MinimumSize;
            animateWidth = Form1::prefs->AnimateWidth;
            animateHeight = Form1::prefs->AnimateHeight;
            length = Form1::prefs->AnimateLength;
            frameRate = Form1::prefs->AnimateFrameRate;
            codec = Form1::prefs->AnimateCodec;
            preview = Form1::prefs->AnimatePreview;
        }

        void saveToPrefs()
        {
            Form1::prefs->ProgressiveRender = periodicUpdate;
            Form1::prefs->DontDisplay = suppressDisplay;
            Form1::prefs->AnimateZoom = animateZoom;
            Form1::prefs->RenderWidth = width;
            Form1::prefs->RenderHeight = height;
            Form1::prefs->BorderWidth = borderSize;
            Form1::prefs->MinimumSize = minimumSize;
            Form1::prefs->AnimateWidth = animateWidth;
            Form1::prefs->AnimateHeight = animateHeight;
            Form1::prefs->AnimateLength = length;
            Form1::prefs->AnimateFrameRate = frameRate;
            Form1::prefs->AnimateCodec = codec;
            Form1::prefs->AnimatePreview = preview;
        }
    };

};