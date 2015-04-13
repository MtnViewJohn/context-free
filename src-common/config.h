// config.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2013 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <array>
#include <initializer_list>

enum class CFG {
    AllowOverlap,
    Alpha,
    Background,
    BorderDynamic,
    BorderFixed,
    Color,
    ColorDepth,
    Frame,
    FrameTime,
    Impure,
    MaxNatural,
    MaxShapes,
    MinimumSize,
    Size,
    StartShape,
    Symmetry,
    Tile,
    Time,
    _NumberOf
};

template <typename _T>
struct CfgArray : public std::array<_T, static_cast<size_t>(CFG::_NumberOf)>
{
    typedef std::array<_T, static_cast<size_t>(CFG::_NumberOf)> base_t;
    CfgArray() : base_t() {}
   
    CfgArray(std::initializer_list<_T> l) : base_t()
    {
        if (l.size() >= base_t::size()) {
            std::copy(l.begin(), l.begin() + base_t::size(), base_t::begin());
        } else if (l.size()) {
            std::copy(l.begin(), l.end(), base_t::begin());
            std::fill(base_t::begin() + l.size(), base_t::end(), *(l.begin() + l.size() - 1));
        }
    }

    CfgArray(const _T* l) : base_t()
    {
        std::copy(l, l + base_t::size(), base_t::begin());
    }

    using base_t::operator[];
    _T& operator[](CFG c) { return operator[](static_cast<size_t>(c)); }
    const _T& operator[](CFG c) const { return operator[](static_cast<size_t>(c)); }
};

#endif      // INCLUDE_CONFIG_H
