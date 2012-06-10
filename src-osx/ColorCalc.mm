// ColorCalc.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005-2006 Mark Lentczner - markl@glyphic.com
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
//

#import "ColorCalc.h"
#include "HSBColor.h"

namespace {
    NSString* buildText(float hue, float saturation, float brightness)
    {
        return [NSString stringWithFormat: @"hue %.1f sat %.4f b %.4f",
            hue, saturation, brightness];
    }
    
};

@implementation ColorCalc

+ (void)initialize {
    NSArray* a;
    
    a = [NSArray arrayWithObject: @"startColor"];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"startHue"];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"startSaturation"];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"startBrightness"];
    
    a = [NSArray arrayWithObjects:
        @"startHue", @"startSaturation", @"startBrightness", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"startColor"];

    a = [NSArray arrayWithObjects:
        @"startHue", @"startSaturation", @"startBrightness",
        @"startColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"startText"];



    a = [NSArray arrayWithObjects:
        @"startHue", @"finishHue", @"deltaSteps", 
        @"startColor", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"deltaHue"];

    a = [NSArray arrayWithObjects:
        @"startSaturation", @"finishSaturation", @"deltaSteps", 
        @"startColor", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"deltaSaturation"];

    a = [NSArray arrayWithObjects:
        @"startBrightness", @"finishBrightness", @"deltaSteps", 
        @"startColor", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"deltaBrightness"];

    a = [NSArray arrayWithObjects:
        @"startHue", @"startSaturation", @"startBrightness",
        @"deltaHue", @"deltaSaturation", @"deltaBrightness",
        @"finishHue", @"finishSaturation", @"finishBrightness",
        @"startColor", @"finishColor", @"deltaSteps", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"deltaText"];



    a = [NSArray arrayWithObjects: @"deltaHue", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"finishHue"];

    a = [NSArray arrayWithObjects: @"deltaSaturation", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"finishSaturation"];

    a = [NSArray arrayWithObjects: @"deltaBrightness", @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"finishBrightness"];

    a = [NSArray arrayWithObjects:
        @"deltaHue", @"deltaSaturation", @"deltaBrightness",
        @"finishHue", @"finishSaturation", @"finishBrightness",
        nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"finishColor"];

    a = [NSArray arrayWithObjects:
        @"deltaHue", @"deltaSaturation", @"deltaBrightness",
        @"finishHue", @"finishSaturation", @"finishBrightness",
        @"finishColor", nil];
    [self setKeys: a triggerChangeNotificationsForDependentKey: @"finishText"];
}

- init
{
    if ((self = [super init])) {
        deltaSteps = 1;
        finishBrightness = 1.0;
    }
    return self;
}

- (NSColor*) startColor
{
    return [NSColor colorWithCalibratedHue: startHue / 360.0
                saturation: startSaturation
                brightness: startBrightness
                alpha: 1.0];
}

- (NSColor*) finishColor;
{
    return [NSColor colorWithCalibratedHue: finishHue / 360.0
                saturation: finishSaturation
                brightness: finishBrightness
                alpha: 1.0];
}

- (void)  setStartColor: (NSColor*) c
{
    startHue = [c hueComponent] * 360.0;
    startSaturation = [c saturationComponent];
    startBrightness = [c brightnessComponent];
}

- (void)  setFinishColor: (NSColor*) c;
{
    finishHue = [c hueComponent] * 360.0;
    finishSaturation = [c saturationComponent];
    finishBrightness = [c brightnessComponent];
}

- (NSString*)   startText
    { return buildText(startHue, startSaturation, startBrightness); }

- (NSString*)   finishText;
    { return buildText(finishHue, finishSaturation, finishBrightness); }

- (float) deltaHue
    { return HSBColor::deltaHue(finishHue, startHue, deltaSteps); }
    
- (void) setDeltaHue: (float) h
{ 
    finishHue = startHue;
    for (int i = 0; i < deltaSteps; ++i)
        finishHue = HSBColor::adjustHue(finishHue, h); 
}

- (float) deltaSaturation
    { return HSBColor::delta(finishSaturation, startSaturation, deltaSteps); }

- (void) setDeltaSaturation: (float) s
{ 
    finishSaturation = startSaturation;
    for (int i = 0; i < deltaSteps; ++i)
        finishSaturation = HSBColor::adjust(finishSaturation, s); 
}

- (float) deltaBrightness
    { return HSBColor::delta(finishBrightness, startBrightness, deltaSteps); }
    
- (void) setDeltaBrightness: (float) b
{ 
    finishBrightness = startBrightness;
    for (int i = 0; i < deltaSteps; ++i)
        finishBrightness = HSBColor::adjust(finishBrightness, b); 
}
    
- (NSString*) deltaText
{
    return buildText(
        [self deltaHue], [self deltaSaturation], [self deltaBrightness]);
}
        


@end
