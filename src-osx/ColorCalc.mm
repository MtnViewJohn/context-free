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
    NSString* buildText(CGFloat hue, CGFloat saturation, CGFloat brightness)
    {
        return [NSString stringWithFormat: @"hue %.1f sat %.4f b %.4f",
            hue, saturation, brightness];
    }
    
};

@implementation ColorCalc

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

+ (NSSet *)keyPathsForValuesAffectingStartHue
{
    return [NSSet setWithObject: @"startColor"];
}
+ (NSSet *)keyPathsForValuesAffectingStartSaturation
{
    return [NSSet setWithObject:@"startColor"];
}
+ (NSSet *)keyPathsForValuesAffectingStartBrightness
{
    return [NSSet setWithObject:@"startColor"];
}
+ (NSSet *)keyPathsForValuesAffectingStartColor
{
    return [NSSet setWithObjects:@"startHue", @"startSaturation", @"startBrightness", nil];
}

- (NSColor*) finishColor;
{
    return [NSColor colorWithCalibratedHue: finishHue / 360.0
                saturation: finishSaturation
                brightness: finishBrightness
                alpha: 1.0];
}

+ (NSSet *)keyPathsForValuesAffectingFinishColor
{
    return [NSSet setWithObjects:@"finishHue", @"finishSaturation", @"finishBrightness", nil];
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

+ (NSSet *)keyPathsForValuesAffectingStartText
    { return [NSSet setWithObjects:@"startHue", @"startSaturation", @"startBrightness", nil]; }

- (NSString*)   finishText;
    { return buildText(finishHue, finishSaturation, finishBrightness); }

+ (NSSet *)keyPathsForValuesAffectingFinishText
    { return [NSSet setWithObjects:@"finishHue", @"finishSaturation", @"finishBrightness", nil]; }

- (CGFloat) deltaHue
    { return HSBColor::deltaHue(finishHue, startHue, deltaSteps); }

+ (NSSet *)keyPathsForValuesAffectingDeltaHue
    { return [NSSet setWithObjects:@"startHue", @"finishHue", @"deltaSteps", nil]; }

- (void) setDeltaHue: (CGFloat) h
{ 
    finishHue = startHue;
    for (int i = 0; i < deltaSteps; ++i)
        finishHue = HSBColor::adjustHue(finishHue, h); 
}

+ (NSSet *)keyPathsForValuesAffectingFinishHue
{
    return [NSSet setWithObjects:@"startHue", @"deltaHue", @"finishColor", nil];                // but not deltaSteps
}

- (CGFloat) deltaSaturation
    { return HSBColor::delta(finishSaturation, startSaturation, deltaSteps); }

+ (NSSet *)keyPathsForValuesAffectingDeltaSaturation
    { return [NSSet setWithObjects:@"startSaturation", @"finishSaturation", @"deltaSteps", nil]; }

- (void) setDeltaSaturation: (CGFloat) s
{ 
    finishSaturation = startSaturation;
    for (int i = 0; i < deltaSteps; ++i)
        finishSaturation = HSBColor::adjust(finishSaturation, s); 
}

+ (NSSet *)keyPathsForValuesAffectingFinishSaturation
{
    return [NSSet setWithObjects:@"startSaturation", @"deltaSaturation", @"finishColor", nil];  // but not deltaSteps
}

- (CGFloat) deltaBrightness
    { return HSBColor::delta(finishBrightness, startBrightness, deltaSteps); }

+ (NSSet *)keyPathsForValuesAffectingDeltaBrightness
    { return [NSSet setWithObjects:@"startBrightness", @"finishBrightness", @"deltaSteps", nil]; }

- (void) setDeltaBrightness: (CGFloat) b
{ 
    finishBrightness = startBrightness;
    for (int i = 0; i < deltaSteps; ++i)
        finishBrightness = HSBColor::adjust(finishBrightness, b); 
}

+ (NSSet *)keyPathsForValuesAffectingFinishBrightness
{
    return [NSSet setWithObjects:@"startBrightness", @"deltaBrightness", @"finishColor", nil];  // but not deltaSteps
}

- (NSString*) deltaText
{
    return buildText(
        [self deltaHue], [self deltaSaturation], [self deltaBrightness]);
}

+ (NSSet *)keyPathsForValuesAffectingDeltaText
{
    return [NSSet setWithObjects:@"deltaHue", @"deltaSaturation", @"deltaBrightness", nil];
}



@end
