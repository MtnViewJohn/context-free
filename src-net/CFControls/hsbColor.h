// hsbColor.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2008 John Horigan - john@glyphic.com
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

#define EQUALITY_THRESHOLD  0.00001


namespace CFControls {
    public value class hsbColor {
    public: hsbColor(System::Drawing::Color c);
    public: hsbColor(double hue, double sat, double bright)
                : Hue(hue), Sat(sat), Bright(bright)
            { }


    public:
        double Hue;
        double Sat;
        double Bright;

        System::Drawing::Color GetColor();
        void adjustWith(const hsbColor& adj);
        hsbColor getAdjustmentFrom(const hsbColor& from, unsigned int steps);
    private:
        static double adjust(double from, double adj);
        static double adjustHue(double from, double adj);
        static double adjustFrom(double to, double from, unsigned int steps);
        static double adjustHueFrom(double to, double from, unsigned int steps);
    };
}
