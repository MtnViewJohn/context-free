// countable.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2006-2007 Mark Lentczner - markl@glyphic.com
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


#ifndef INCULDE_COUNTABLE_H
#define INCULDE_COUNTABLE_H

template <class C> class ref_ptr;

class Countable {
protected:
    Countable() : mUseCount(0) { }
    virtual ~Countable();

    template <class C>
    static ref_ptr<C> build(C* p) { return ref_ptr<C>(p); }

public:
    class RefPtr {
    protected:
        static void adjust(Countable* pointer, Countable* value);
    };
    
private:
    int mUseCount;
    friend class RefPtr;
};


inline void
Countable::RefPtr::adjust(Countable* pointer, Countable* value)
{
    if (value)      ++value->mUseCount;
    if (pointer)    if (--pointer->mUseCount == 0) delete pointer;
}


template <class C>
class ref_ptr : private Countable::RefPtr {
private:
    C* ptr;
    void assign(C* p) { RefPtr::adjust(ptr, p); ptr = p; }
    
public:
    ref_ptr()                   : ptr(0)    { }
    ref_ptr(const ref_ptr& r)   : ptr(0)    { assign(r.ptr); }
    ~ref_ptr()                              { assign(0); }
    ref_ptr& operator=(const ref_ptr& r)
        { assign(r.ptr); return *this; }

    C& operator*()  const { return *ptr; }
    C* operator->() const { return ptr; }
    C* get()        const { return ptr; }

#ifndef WIN32
    template <class D>
    ref_ptr(const ref_ptr<D>& r)
        : ptr(0) { assign(r.get()); }

    template <class D>
    ref_ptr& operator=(const ref_ptr<D>& r)
        { assign(r.get()); return *this; }
#endif // !WIN32

private:
    friend class Countable;
    explicit ref_ptr(C* p) : ptr(0) { assign(p); }
};


#endif // INCULDE_COUNTABLE_H
