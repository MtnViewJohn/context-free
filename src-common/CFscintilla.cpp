// CFscintilla.cpp
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

#include "CFscintilla.h"

namespace ContextFree {
    const char major_keywords[] =
    "a alpha "
    "b background brightness "
    "case clone "
    "else "
    "f finally flip "
    "h hue "
    "if import include "
    "let loop "
    "path "
    "r rotate rule "
    "s saturation sat size skew startshape shape "
    "tile time timescale trans transform "
    "x x1 x2 "
    "y y1 y2 "
    "z";
    
    const char functions[] =
    "cos sin tan cot acos asin atan acot cosh sinh tanh acosh asinh atanh log log10 "
    "sqrt exp abs floor ceiling infinity factorial sg isNatural bitnot bitor bitand bitxor "
    "bitleft bitright atan2 mod divides div dot cross hsb2rgb rgb2hsb vec min max ftime "
    "frame rand_static rand rand::exponential rand::gamma rand::weibull rand::extremeV "
    "rand::normal rand::lognormal rand::chisquared rand::cauchy rand::fisherF "
    "rand::studentT randint randint::bernoulli randint::binomial randint::negbinomial "
    "randint::poisson randint::discrete randint::geometric "
    "CIRCLE SQUARE TRIANGLE FILL STROKE "
    "MOVETO LINETO ARCTO CURVETO MOVEREL LINEREL ARCREL CURVEREL CLOSEPOLY";
    
    const char built_ins[] =
    "CF::None CF::MiterJoin CF::RoundJoin CF::BevelJoin CF::ButtCap CF::RoundCap "
    "CF::SquareCap CF::ArcCW CF::ArcLarge CF::Continuous CF::Align CF::EvenOdd "
    "CF::IsoWidth CF::Cyclic CF::Dihedral CF::p11g CF::p11m CF::p1m1 CF::p2 "
    "CF::p2mg CF::p2mm CF::pm CF::pg CF::cm CF::pmm CF::pmg CF::pgg CF::cmm "
    "CF::p4 CF::p4m CF::p4g CF::p3 CF::p3m1 CF::p31m CF::p6 CF::p6m "
    "CF::AllowOverlap CF::Alpha CF::Background CF::BorderDynamic CF::BorderFixed "
    "CF::Color CF::ColorDepth CF::Frame CF::FrameTime CF::Impure CF::MaxNatural "
    "CF::MaxShapes CF::MinimumSize CF::Size CF::StartShape CF::Symmetry "
    "CF::Tile CF::Time";
    
    std::vector<const char*> autoComplete = {
        "ARCREL", "ARCTO", "background", "bitand", "bitleft", "bitnot", "bitor", "bitright", "bitxor",
        "CF::Align", "CF::AllowOverlap", "CF::Alpha", "CF::ArcCW", "CF::ArcLarge", "CF::Background",
        "CF::BevelJoin", "CF::BorderDynamic", "CF::BorderFixed", "CF::ButtCap", "CF::cm", "CF::cmm", "CF::Color",
        "CF::ColorDepth", "CF::Continuous", "CF::Cyclic", "CF::Dihedral", "CF::EvenOdd", "CF::Frame",
        "CF::FrameTime", "CF::Impure", "CF::IsoWidth", "CF::MaxNatural", "CF::MaxShapes",
        "CF::MinimumSize", "CF::MiterJoin",
        "CF::p11g", "CF::p11m", "CF::p1m1", "CF::p2", "CF::p2mg", "CF::p2mm", "CF::p3", "CF::p3m1", "CF::p31m",
        "CF::p4", "CF::p4g", "CF::p4m", "CF::p6", "CF::p6m", "CF::pg", "CF::pgg", "CF::pm", "CF::pmg", "CF::pmm",
        "CF::RoundCap", "CF::RoundJoin", "CF::Size", "CF::SquareCap", "CF::StartShape", "CF::Symmetry", "CF::Tile", "CF::Time",
        "CIRCLE", "CLOSEPOLY", "CURVEREL", "CURVETO", "FILL", "import", "include", "LINEREL", "LINETO", "MOVEREL", "MOVETO", "SQUARE", "STROKE", "TRIANGLE",
        "rand", "rand::cauchy", "rand::chisquared", "rand::exponential", "rand::extremeV",
        "rand::fisherF", "rand::gamma", "rand::lognormal", "rand::normal", "rand::studentT", "rand::weibull",
        "randint", "randint::bernoulli", "randint::binomial", "randint::discrete",
        "randint::geometric", "randint::negbinomial", "randint::poisson", "rand_static", "startshape",
        "floor", "ceiling", "infinity", "factorial", "isNatural", "divides", "div",
        "dot", "cross", "hsb2rgb", "rgb2hsb"
    };
}
