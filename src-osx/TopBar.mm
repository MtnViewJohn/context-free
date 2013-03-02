// TopBar.mm
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

#import "TopBar.h"
#include <math.h>

namespace {
    void
    moveView(NSView* superView, NSView* subView,
        const NSRect& oldSubFrame, const NSRect& newSubFrame)
    {
        if (NSEqualRects(oldSubFrame, newSubFrame)) return;
        
        [superView setNeedsDisplayInRect: oldSubFrame];
        [subView setFrame: newSubFrame];
        [subView setNeedsDisplay: YES];
    }
};

@implementation TopBar

- (void)awakeFromNib
{
    [self relayout];
}

- (void)relayout
{
    [self resizeSubviewsWithOldSize: [self frame].size];
}

- (void)resizeSubviewsWithOldSize:(NSSize)oldBoundsSize
{
    NSSize size = [self frame].size;
    
    NSRect midOld = [mCenterControls frame];
    NSRect midNew = midOld;
    midNew.origin.x = floor((size.width - midNew.size.width) / 2.0);
    moveView(self, mCenterControls, midOld, midNew);
    
    NSRect leftOld = [mLeftStatus frame];
    NSRect leftNew = leftOld;
    CGFloat xSpace = leftOld.origin.x;
    leftNew.size.width = midNew.origin.x - xSpace - leftNew.origin.x;
    moveView(self, mLeftStatus, leftOld, leftNew);
    
    CGFloat rightEdge = size.width;
    
    if (![mProgressOne isHidden]) {
        NSRect progOld = [mProgressOne frame];
        NSRect progNew = progOld;
        progNew.origin.x = rightEdge - xSpace - progNew.size.width;
        moveView(self, mProgressOne, progOld, progNew);
        rightEdge = progNew.origin.x;
    }
    if (![mProgressTwo isHidden]) {
        NSRect progOld = [mProgressTwo frame];
        NSRect progNew = progOld;
        progNew.origin.x = rightEdge - xSpace - progNew.size.width;
        moveView(self, mProgressTwo, progOld, progNew);
        rightEdge = progNew.origin.x;
    }
    
    NSRect rightOld = [mRightStatus frame];
    NSRect rightNew = rightOld;
    rightNew.origin.x = midNew.origin.x + midNew.size.width + xSpace;
    rightNew.size.width = rightEdge - xSpace - rightNew.origin.x;
    moveView(self, mRightStatus, rightOld, rightNew);
}

@end
