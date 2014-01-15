// HSBColor.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2008 Mark Lentczner - markl@glyphic.com
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
// Mark Lentczner can be contacted at markl@glyphic.com or at
// Mark Lentczner, 1209 Villa St., Mountain View, CA 94041-1123, USA
//
//

#ifndef __HSBCOLOR_H_
#define __HSBCOLOR_H_

namespace agg {
    struct rgba;
};

#define EQUALITY_THRESHOLD  0.00001

#include <math.h>

struct HSBColor
{
    enum AssignmentTypes {
        ColorTarget = 1,
        Color2Value = 3,
        ColorMask = 3,
        HueTarget = ColorTarget,
        Hue2Value = Color2Value,
        HueMask = 3,
        SaturationTarget = ColorTarget << 2,
        Saturation2Value = Color2Value << 2,
        SaturationMask = 3 << 2,
        BrightnessTarget = ColorTarget << 4,
        Brightness2Value = Color2Value << 4,
        BrightnessMask = 3 << 4,
        AlphaTarget = ColorTarget << 6,
        Alpha2Value = Color2Value << 6,
        AlphaMask = 3 << 6,
        HSBA2Value = Hue2Value | Saturation2Value | Brightness2Value | Alpha2Value,
        HSBATarget = HueTarget | SaturationTarget | BrightnessTarget | AlphaTarget
    };
                             
    HSBColor() : h(0), s(0), b(0), a(0) {};
    HSBColor(double hue, double sat, double bri, double alpha) 
        : h(hue), s(sat), b(bri), a(alpha) {};
    HSBColor(const agg::rgba&);

    static void Adjust(HSBColor& dest, HSBColor& destTarget,
                       const HSBColor& adj, const HSBColor& adjTarg, int assign);

    void getRGBA(agg::rgba& c) const;
    
    bool operator!=(const HSBColor& hsb) const {
        return h != hsb.h || s != hsb.s || b != hsb.b || a != hsb.s;
    }

    double h, s, b, a;
    
    static inline double adjust(const double& base, const double& adjustment, 
                                int useTarget = 0, const double& target = 0.0);
    static inline double adjustHue(const double& base, const double& adjustment, 
                                   int useTarget = 0, const double& target = 0.0);
    static double delta(double to, double from, unsigned int steps = 1);
    static double deltaHue(double to, double from, unsigned int steps = 1);
};

inline double
HSBColor::adjust(const double& base, const double& adjustment, 
                 int useTarget, const double& target)
{
    if (adjustment == 0.0)
        return base;
    
    if (useTarget) {
            // If we are really close to the target then don't change, even if
            // the adjustment is negative (which way would we go?)
        if (adjustment > 0 && fabs(base - target) < EQUALITY_THRESHOLD)
            return base;
        
            // Otherwise move away from or toward the target
        double edge = base < target ? 0 : 1;
        if (adjustment < 0)
            return base + (  base - edge) * adjustment;
        else 
            return base + (target - base) * adjustment;
    } else {
            // Move toward 0 or toward 1
        if (adjustment < 0)
            return base + base * adjustment;
        else 
            return base + (1 - base) * adjustment;
    }
}

inline double
HSBColor::adjustHue(const double& base, const double& adjustment, 
                    int useTarget, const double& target)
{
    if (adjustment == 0.0)
        return base;
    
    double h;
    if (useTarget) {
        // decrease or increase toward target. If the target hue does not 
        // cooperate by being smaller (or larger) than the current hue then 
        // add/subtract 360 to make it so. This only works if all hues are
        // within the interval [0,360).
        double t = target;
        if (adjustment < 0) {
            if (t > base) t -= 360;
            h = base + (base - t) * adjustment;
        } else {
            if (t < base) t += 360;
            h = base + (t - base) * adjustment;
        }
    } else {
        h = base + adjustment;
    }
    
    // Normalize result to the interval [0,360)
    return h < 0.0 ? fmod(h + 360.0, 360.0) : fmod(h, 360.0);
}


#endif
