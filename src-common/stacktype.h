// stacktype.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2011 John Horigan - john@glyphic.com
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

#ifndef INCLUDE_STACKTYPE_H
#define INCLUDE_STACKTYPE_H

#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS
#endif
#include <stdint.h>               // Use the C99 official header
#include <vector>
#include <iosfwd>

namespace AST { class ASTparameter; class ASTexpression; }

union StackType;
class Renderer;

struct StackRule {
    enum { MaxRefCount = UINT32_MAX };
    int16_t     mRuleName;
    uint16_t    mParamCount;
    mutable uint32_t    mRefCount;
    
    bool operator==(const StackRule& o) const;
    static bool Equal(const StackRule* a, const StackType* b);
};

union StackType {
    double      number;
    const StackType*  rule;
    StackRule   ruleHeader;
    const std::vector<AST::ASTparameter>* typeInfo;

    static StackType*  alloc(int name, int size, const std::vector<AST::ASTparameter>* ti);
    void        release() const;
    void        release(const std::vector<AST::ASTparameter>* p) const;
    void        retain(Renderer* r) const;

    void        read(std::istream& is);
    void        write(std::ostream& os) const;
    static StackType*  readHeader(std::istream& is);
    static void        writeHeader(std::ostream& os, const StackType* s);
    
    void        evalArgs(Renderer* rti, const AST::ASTexpression* arguments, 
                         const StackType* parent);
    void        evalArgs(Renderer* rti, const AST::ASTexpression* arguments,
                         const std::vector<AST::ASTparameter>* p, bool sequential);
};

#endif // INCLUDE_STACKTYPE_H
