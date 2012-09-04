// HSBColor.cpp
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
// Copyright (C) 2005-2008 John Horigan - john@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#include "HSBColor.h"

#include <math.h>
#include <agg_color_rgba.h>



void HSBColor::getRGBA(agg::rgba& c) const
{
    // Determine which facet of the HSB hexcone we are in and how 
	// far we are into this hextant.
    double hue = h / 60.0;; 
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
    
    double p = b * (1 - s);
    double q = b * (1 - (s * remainder));
    double t = b * (1 - (s * (1 - remainder)));
    
    c.a = a;
    switch (hextant) {
        case 0:  
            c.r = b; c.g = t; c.b = p;
            return;
        case 1:  
            c.r = q; c.g = b; c.b = p;
            return;
        case 2:  
            c.r = p; c.g = b; c.b = t;
            return;
        case 3:  
            c.r = p; c.g = q; c.b = b;
            return;
        case 4:  
            c.r = t; c.g = p; c.b = b;
            return;
        case 5:  
            c.r = b; c.g = p; c.b = q;
            return;
        default: 	// this should never happen
            c.r = 0; c.g = 0; c.b = 0; c.a = 1;
            return;
    }
}

static inline double myfmin(double x, double y) { return x < y ? x : y; }
static inline double myfmax(double x, double y) { return x > y ? x : y; }

HSBColor::HSBColor(const agg::rgba& c)
{
	double min = myfmin(c.r, myfmin(c.g, c.b));	
	double max = myfmax(c.r, myfmax(c.g, c.b));
	double delta = max - min;
	
	b = max;
	if (delta < EQUALITY_THRESHOLD) {
		h = s = 0.0;
    } else {
		s = delta / b;  // hsb.b can't be zero here

		// The == operator is normally useless for floats and doubles. But
		// since max is always assigned from either c.r/g/b we will take
		// a chance.
		double temp;
		if (c.r == max) {
			temp = (c.g - c.b) / (delta);
        } else if (c.g == max) {
			temp = 2 + ((c.b - c.r) / (delta));
        } else /* if (c.b == max) */ {
			temp = 4 + ((c.r - c.g) / (delta));
        }

        // compute hue in the interval [0,360)
		temp *= 60;
        h = temp < 0.0 ? fmod(temp + 360.0, 360.0) : fmod(temp, 360.0);
	}
    a = c.a;
}

void HSBColor::adjustWith(const HSBColor& adj, const HSBColor& target)
{
    // Adjust parent color w/shape color
    h = adjustHue(h, adj.h, adj.mUseTarget, target.h);
    s = adjust(s, adj.s, adj.mUseTarget & SaturationTarget, target.s);
    b = adjust(b, adj.b, adj.mUseTarget & BrightnessTarget, target.b);
    a = adjust(a, adj.a, adj.mUseTarget & AlphaTarget, target.a);
}

double HSBColor::delta(double to, double from, unsigned int steps)
{
    if (fabs(to - from) < EQUALITY_THRESHOLD) 
        return 0.0;

    if (to > from)
        return -delta(1.0 - to, 1.0 - from, steps);

    // from >= EQUALITY_THRESHOLD
    if (steps == 1)
        return to / from - 1.0;

    return pow(to / from, 1.0 / ((double)steps)) - 1.0;
}

double HSBColor::deltaHue(double to, double from, unsigned int steps)
{ 
    double diff = fmod(to - from, 360.0) / steps;
    // Normalize result to the interval (-180,180]
    if (diff <= -180.0) return diff + 360.0;
    if (diff >   180.0) return diff - 360.0;
    return diff;
}


