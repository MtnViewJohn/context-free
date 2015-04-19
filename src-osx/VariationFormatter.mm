// VariationFormatter.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2005 Mark Lentczner - markl@glyphic.com
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

#import "VariationFormatter.h"
#include "variation.h"

@implementation VariationFormatter

+ (int)minVariation     { return Variation::recommendedMin(); }
+ (int)maxVariation     { return Variation::recommendedMax(6); }
+ (int)randomVariation  { return Variation::random(3); }

+ (NSString *)stringForVariation:(int)v lowerCase:(BOOL)lowerCase
{
    std::string code = Variation::toString(v, lowerCase);
    return [NSString stringWithUTF8String: code.c_str()];
}

- (NSString *)stringForObjectValue:(id)obj
{
    int v = 0;
    if ([obj respondsToSelector: @selector(intValue)]) {
        v = [obj intValue];
    }
    return [VariationFormatter stringForVariation: v lowerCase: NO];
}

- (BOOL)getObjectValue:(id *)obj forString:(NSString *)string
    errorDescription:(NSString **)error
{
    NSUInteger l = [string length];
    if (l > 6) {
        if (error)
            *error = NSLocalizedString(@"No more than six letters", @"");
        return NO;
    }
    
    for (unsigned int i = 0; i < l; ++i) {
        unichar c = [string characterAtIndex: i];

        if (('A' <= c && c <= 'Z') ||  ('a' <= c && c <= 'z'))
            continue;
            
        if (error)
            *error = NSLocalizedString(@"Only accepts letters", @"");
        return NO;
    }
    
    int v = Variation::fromString([string UTF8String]);
    if (v == -1) {
        if (error)
            *error = NSLocalizedString(@"Error parsing variation", @"");
        return NO;
    }
    
    if (obj)
        *obj = [NSNumber numberWithInt: v];
    return YES;
}


- (BOOL)isPartialStringValid:(NSString **)partialStringPtr
    proposedSelectedRange:(NSRangePointer)proposedSelRangePtr
    originalString:(NSString *)origString
    originalSelectedRange:(NSRange)origSelRange
    errorDescription:(NSString **)error
{
    return [self getObjectValue: nil forString: *partialStringPtr
                errorDescription: error];
}

@end
