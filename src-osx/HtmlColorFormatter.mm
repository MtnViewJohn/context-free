// HtmlColorFormatter.mm
// this file is part of Context Free
// ---------------------
// Copyright (C) 2018 John Horigan - john@glyphic.com
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

#import "HtmlColorFormatter.h"
#include <cctype>

@implementation HtmlColorFormatter
- (BOOL)isPartialStringValid:(NSString *)partialString
            newEditingString:(NSString *__autoreleasing *)newString
            errorDescription:(NSString *__autoreleasing *)error {
    NSUInteger len = [partialString length];
    unichar buffer[len+1];
    [partialString getCharacters:buffer range:NSMakeRange(0, len)];
    if (len == 0) return YES;
    if (buffer[0] == (unichar)'#') {
        if (len > 7) return NO;
        for (NSUInteger i = 1; i < len; i++) {
            unichar c = buffer[i];
            if (c >= 0x80 || !std::isxdigit(c)) return NO;
        }
    } else {
        for (NSUInteger i = 0; i < len; ++i) {
            unichar c = buffer[i];
            if (c >= 0x80 || !std::isalpha(c)) return NO;
        }
    }
    return YES;
}

- (NSString *)stringForObjectValue:(id)obj {
    return obj;
}

- (BOOL)getObjectValue:(__autoreleasing id *)obj
             forString:(NSString *)string
      errorDescription:(NSString *__autoreleasing *)error {
    *obj = string;
    return YES;
}

@end
