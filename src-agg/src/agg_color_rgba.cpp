//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.4
// Copyright (C) 2009 John Horigan (http://www.antigrain.com)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
//
// Contact: john@glyphic.com.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------

#include "agg_color_rgba.h"
#include "agg_color_gray.h"

agg::rgba8::rgba8(const gray8& c) :
r(c.v), g(c.v), b(c.v), a(c.a) {}

agg::rgba16::rgba16(const gray16& c) :
r(c.v), g(c.v), b(c.v), a(c.a) {}

