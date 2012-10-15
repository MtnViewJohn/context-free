// hsbColor.cpp
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

#include "StdAfx.h"
#include "hsbColor.h"
#include "math.h"

using namespace CFControls;
using namespace System;
using namespace System::Drawing;

hsbColor::hsbColor(System::Drawing::Color c)
{
    int iMin = Math::Min(c.R, Math::Min(c.G, c.B));
    int iMax = Math::Max(c.R, Math::Max(c.G, c.B));
	double min = ((double)(iMin)) / 255.0;
	double max = ((double)(iMax)) / 255.0;
	double delta = max - min;

    Bright = max;

    if (iMin == iMax) {
        Hue = Sat = 0.0;
        return;
    }

    Sat = delta / max;  // max can't be zero here

    double temp;
    if (c.R == iMax) {
        temp = (c.G - c.B) / (255.0 * delta);
    } else if (c.G == iMax) {
        temp = 2.0 + ((c.B - c.R) / (255.0 * delta));
    } else /* if (c.B == iMax) */ {
        temp = 4.0 + ((c.R - c.G) / (255.0 * delta));
    }

    // compute hue in the interval [0,360)
    temp *= 60.0;
    Hue = temp < 0.0 ? fmod(temp + 360.0, 360.0) : fmod(temp, 360.0);
}

System::Drawing::Color hsbColor::GetColor()
{
    // Determine which facet of the HSB hexcone we are in and how 
	// far we are into this hextant.
    double hue = Hue / 60.0;
    double remainder, hex; 

	for(;;) {
        // try splitting the hue into an integer hextant in [0,6) and
        // a real remainder in [0,1)
		remainder = modf(hue, &hex);
		if (hex > -0.1 && hex < 5.1 && remainder >= 0)
			break;

        // We didn't get the ranges that we wanted. Adjust hue and try again.
		if (hex < 0 || remainder < 0)
			hue += 6.0;
		if (hex > 5.5)
			hue -= 6.0;
	}

	int hextant = (int)(hex + 0.5); // guaranteed to be in 0..5
    
    int p = (int)(255.0 * Bright * (1 - Sat) + 0.5);
    int q = (int)(255.0 * Bright * (1 - (Sat * remainder)) + 0.5);
    int t = (int)(255.0 * Bright * (1 - (Sat * (1 - remainder))) + 0.5);

    int b = (int)(255.0 * Bright + 0.5);

    switch (hextant) {
        case 0:  
            return Color::FromArgb(b, t, p);
        case 1:  
            return Color::FromArgb(q, b, p);
        case 2:  
            return Color::FromArgb(p, b, t);
        case 3:  
            return Color::FromArgb(p, q, b);
        case 4:  
            return Color::FromArgb(t, p, b);
        case 5:  
            return Color::FromArgb(b, p, q);
    }

    return Color::Black;
}

hsbColor hsbColor::getAdjustmentFrom(const hsbColor& old, unsigned int steps)
{
    double hue =   adjustHueFrom(Hue, old.Hue, steps);
    double sat =   adjustFrom(Sat, old.Sat, steps);
    double bri =   adjustFrom(Bright, old.Bright, steps);
    
    return hsbColor(hue, sat, bri);
}

void hsbColor::adjustWith(const hsbColor& adj)
{
    // Adjust parent color w/shape color
    Hue = adjustHue(Hue, adj.Hue);
    Sat = adjust(Sat, adj.Sat);
    Bright = adjust(Bright, adj.Bright);
}

double hsbColor::adjustFrom(double to, double from, unsigned int steps)
{
    if (fabs(to - from) < EQUALITY_THRESHOLD) 
        return 0.0;

    if (to > from)
        return -adjustFrom(1.0 - to, 1.0 - from, steps);

    // from >= EQUALITY_THRESHOLD
    if (steps == 1)
        return to / from - 1.0;

    return pow(to / from, 1.0 / ((double)steps)) - 1.0;
}

double hsbColor::adjustHueFrom(double to, double from, unsigned int steps)
{ 
    double diff = fmod(to - from, 360.0) / steps;
    // Normalize result to the interval (-180,180]
    if (diff <= -180.0) return diff + 360.0;
    if (diff >   180.0) return diff - 360.0;
    return diff;
}

double hsbColor::adjust(double from, double adj)
{
    if (adj < 0)
        return from + from * adj;
    else 
        return from + (1.0 - from) * adj;
}

double hsbColor::adjustHue(double from, double adj)
{
    double h = from + adj;

    // Normalize result to the interval [0,360)
    return h < 0.0 ? fmod(h + 360.0, 360.0) : fmod(h, 360.0);
}



