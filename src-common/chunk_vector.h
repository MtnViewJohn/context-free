// chunk_vector.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2012-2013 John Horigan - john@glyphic.com
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


#ifndef INCLUDE_CHUNK_VECTOR_H
#define INCLUDE_CHUNK_VECTOR_H

#include <vector>
#include <iterator>
#include <memory>
#include <cassert>
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <type_traits>
#include "mynoexcept.h"

template <typename _valType, unsigned _power2>
struct chunk_vector_iterator
{
    typedef std::random_access_iterator_tag iterator_category;
    typedef _valType                        value_type;
    typedef _valType*                       pointer;
    typedef _valType&                       reference;
    typedef size_t                          size_type;
    typedef ptrdiff_t                       difference_type;
    
private:
    enum consts_e {
        _chunk_size = 1 << _power2,
        _chunk_mask = _chunk_size - 1
    };
    
    pointer*    _chunksPtr;
    size_type   _index;
    
    chunk_vector_iterator(_valType** vals, size_t index)
        : _chunksPtr(vals), _index(index)
    {
    }
    
    template <typename _vT, unsigned _p2, typename _Alloc>
    friend class chunk_vector;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator==(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator!=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator<(const chunk_vector_iterator<_valType1, _p2>& __x,
                          const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator>(const chunk_vector_iterator<_valType1, _p2>& __x,
                          const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator<=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator>=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) NOEXCEPT;
    
public:
    chunk_vector_iterator(const chunk_vector_iterator& cvi)
        : _chunksPtr(cvi._chunksPtr), _index(cvi._index)
    { }
    chunk_vector_iterator()
        : _chunksPtr(nullptr), _index(0)
    { }
    
    chunk_vector_iterator& operator=(const chunk_vector_iterator& rhs)
    {
        _chunksPtr = rhs._chunksPtr;
        _index = rhs._index;
        return *this;
    }

    reference operator*() const
    { return *_get_current(); }

    pointer operator->() const
    { return _get_current(); }

    chunk_vector_iterator& operator++()
    {
        ++_index;
        return *this;
    }

    chunk_vector_iterator operator++(int)
    {
        chunk_vector_iterator tmp = *this;
        ++*this;
        return tmp;
    }

    chunk_vector_iterator& operator--()
    {
        --_index;
        return *this;
    }

    chunk_vector_iterator operator--(int)
    {
        chunk_vector_iterator tmp = *this;
        --*this;
        return tmp;
    }

    chunk_vector_iterator& operator+=(difference_type n)
    {
        _index += n;
        return *this;
    }

    chunk_vector_iterator operator+(difference_type n) const
    {
        chunk_vector_iterator tmp = *this;
        tmp += n;
        return tmp;
    }

    chunk_vector_iterator& operator-=(difference_type n)
    {
        _index -= n;
        return *this;
    }

    chunk_vector_iterator operator-(difference_type n) const
    {
        chunk_vector_iterator tmp = *this;
        tmp -= n;
        return tmp;
    }

    difference_type operator-(const chunk_vector_iterator& cvi) const
    { return _index - cvi._index; }

    reference operator[](difference_type n) const
    {
        chunk_vector_iterator tmp = *this;
        tmp += n;
        return *tmp;
    }
    
    bool operator<(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index < rhs._index;
    }
    
    bool operator>(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index > rhs._index;
    }
    
    bool operator<=(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index <= rhs._index;
    }
    
    bool operator>=(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index >= rhs._index;
    }
    
    bool operator==(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index == rhs._index;
    }
    
    bool operator!=(const chunk_vector_iterator& rhs) const NOEXCEPT
    {
        return _index != rhs._index;
    }
    
private:
    pointer _get_current() const
    {
        return _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
    }
};

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator==(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index == __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator!=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index != __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<(const chunk_vector_iterator<_valType1, _power2>& __x,
                      const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index < __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>(const chunk_vector_iterator<_valType1, _power2>& __x,
                      const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index > __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index <= __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) NOEXCEPT
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index >= __y._index;
}

template<typename _valType, unsigned _power2>
inline chunk_vector_iterator<_valType, _power2> operator+(ptrdiff_t __n,
                       const chunk_vector_iterator<_valType, _power2>& __x) NOEXCEPT
{ return __x + __n; }

template <typename _valType, unsigned _power2, typename _Alloc = std::allocator<_valType>>
class chunk_vector {
private:
    size_t _start;
    size_t _end;
    std::vector<_valType*> _chunks;
    _Alloc _valAlloc;
    enum consts_e : size_t {
        _chunk_size = 1 << _power2,
        _chunk_mask = _chunk_size - 1
    };

public:
    typedef _valType                                        value_type;
    typedef typename _Alloc::pointer                        pointer;
    typedef typename _Alloc::const_pointer                  const_pointer;
    typedef typename _Alloc::reference                      reference;
    typedef typename _Alloc::const_reference                const_reference;
    typedef chunk_vector_iterator<_valType, _power2>        iterator;
    typedef chunk_vector_iterator<const _valType, _power2>  const_iterator;
    typedef std::reverse_iterator<const_iterator>           const_reverse_iterator;
    typedef std::reverse_iterator<iterator>                 reverse_iterator;
    typedef size_t                                          size_type;
    typedef ptrdiff_t                                       difference_type;
    typedef _Alloc                                          allocator_type;

    chunk_vector()
        : _start(0), _end(0)
    {
        assert(_valAlloc.max_size() >= _chunk_size);
    }
    ~chunk_vector() { clear(); _shrink_to_fit(true); }

    void push_back(const value_type& x)
    {
        _valType* endVal = _alloc_back();
        _valAlloc.construct(endVal, x);
        ++_end;
    }
    
    void push_back(value_type&& x)
    {
        _valType* endVal = _alloc_back();
        _valAlloc.construct(endVal, std::move(x));
        ++_end;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        _valType* endVal = _alloc_back();
        _valAlloc.construct(endVal, std::forward<Args>(args)...);
        ++_end;
        
    }
    
    void pop_back()
    {
        if (_start == _end) return;
        --_end;
        _valType* endVal = _chunks[_end >> _power2] + (_end & _chunk_mask);
        _valAlloc.destroy(endVal);
    }
    
    void push_front(const value_type& x)
    {
        _valType* frontVal = _alloc_front();
        _valAlloc.construct(frontVal, x);
        --_start;
    }
    
    void push_front(value_type&& x)
    {
        _valType* frontVal = _alloc_front();
        _valAlloc.construct(frontVal, std::move(x));
        --_start;
    }
    
    template<typename... Args>
    void emplace_front(Args&&... args)
    {
        _valType* frontVal = _alloc_front();
        _valAlloc.construct(frontVal, std::forward<Args>(args)...);
        --_start;
        
    }
    
    void pop_front()
    {
        if (_start == _end) return;
        _valType* frontVal = _chunks[_start >> _power2] + (_start & _chunk_mask);
        ++_start;
        _valAlloc.destroy(frontVal);
    }
    
    size_type size() const NOEXCEPT { return _end - _start; }
    
    bool empty() const NOEXCEPT { return _start == _end; }
    
    void clear() NOEXCEPT
    {
        for (size_t i = _start; i < _end; ++i)
            _valAlloc.destroy(_chunks[i >> _power2] + (i & _chunk_mask));
        _end = _start;
    }
    
    void shrink_to_fit()
    {
        _shrink_to_fit(true);
        _chunks.shrink_to_fit();
    }
    
    void resize(difference_type _newSize, const_reference x)
    // Set to |size|, adding to/removing from the end if positive and the front
    // if negative.
    {
        reserve(_newSize);
        if (_newSize >= 0) {
            size_type newSize = static_cast<size_type>(_newSize);
            while (newSize > size())
                push_back(x);
            while (newSize < size())
                pop_back();
        } else {
            size_type newSize = static_cast<size_type>(-_newSize);
            while (newSize > size())
                push_front(x);
            while (newSize < size())
                pop_front();
        }
    }
    
    void resize(difference_type _newSize)
    // Set to |size|, adding to/removing from the end if positive and the front
    // if negative.
    {
        reserve(_newSize);
        if (_newSize >= 0) {
            size_type newSize = static_cast<size_type>(_newSize);
            while (newSize > size())
                push_back();
            while (newSize < size())
                pop_back();
        } else {
            size_type newSize = static_cast<size_type>(-_newSize);
            while (newSize > size())
                push_front();
            while (newSize < size())
                pop_front();
        }
    }
    
    void swap(chunk_vector<_valType, _power2, _Alloc>& with)
    {
        size_t tempstart = _start;
        size_t tempend = _end;
        _Alloc tempalloc = _valAlloc;
        _start = with._start;
        _end = with._size;
        _valAlloc = with._valAlloc;
        with._start = tempstart;
        with._end = tempend;
        with._valAlloc = tempalloc;
        _chunks.swap(with._chunks);
        _shrink_to_fit(false);   // no reallocation of _chunks, iterators stay valid
        with._shrink_to_fit(false);
    }
    
    void reserve(difference_type _newSize)
    // Reserve allocation for |size|. Adding allocation to the end if positive
    // and to the front if negative. 
    {
        if (_newSize >= 0) {
            size_type newSize = static_cast<size_type>(_newSize);
            if (capacity() - _start >= newSize) return;
            size_type chunksNeeded = ((newSize - (capacity() - _start)) + _chunk_mask) >> _power2;
            // Borrow from front before allocating
            while (chunksNeeded && _start >= _chunk_size) {
                pointer newChunk = _chunks.front();
                _chunks.erase(_chunks.begin());
                _start -= _chunk_size;
                _end -= _chunk_size;
                --chunksNeeded;
                _chunks.push_back(newChunk);
            }
            _chunks.reserve(_chunks.size() + chunksNeeded);
            for (size_type i = 0; i < chunksNeeded; ++i)
                _chunks.push_back(_valAlloc.allocate(_chunk_size));
        } else {
            size_type newSize = static_cast<size_type>(-_newSize);
            if (_end >= newSize) return;
            size_type chunksNeeded = (newSize - _end + _chunk_mask) >> _power2;
            while (chunksNeeded && capacity() - _end >= _chunk_size) {
                pointer newChunk = _chunks.back();
                _chunks.pop_back();
                _chunks.insert(_chunks.begin(), newChunk);
                _start += _chunk_size;
                _end += _chunk_size;
                --chunksNeeded;
            }
            // Less efficient but leaves that container state valid if the
            // alloc throws an exception.
            _chunks.reserve(_chunks.size() + chunksNeeded);
            for (size_type i = 0; i < chunksNeeded; ++i) {
                _chunks.insert(_chunks.begin(), _valAlloc.allocate(_chunk_size));
                _start += _chunk_size;
            }
        }
    }
    
    size_type capacity() const NOEXCEPT
    {
        return _chunks.size() << _power2;
    }

    reference operator[](size_t i)
    {
        i += _start;
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    const_reference operator[](size_t i) const
    {
        i += _start;
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    
    reference at(size_t i)
    {
        if (i >= size())
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    const_reference at(size_t i) const
    {
        if (i >= size())
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    
    reference front() { return (*this)[_start]; }
    const_reference front() const { return (*this)[_start]; }
    
    reference back() { return (*this)[_end - 1]; }
    const_reference back() const { return (*this)[_end - 1]; }

    iterator begin() NOEXCEPT             { return iterator(_chunks.data(), _start); }
    iterator end() NOEXCEPT               { return iterator(_chunks.data(), _end); }
    const_iterator begin() const NOEXCEPT { return const_iterator(_chunks.data(), _start); }
    const_iterator end() const NOEXCEPT   { return const_iterator(_chunks.data(), _end); }
    const_iterator cbegin() NOEXCEPT      { return const_iterator(_chunks.data(), _start); }
    const_iterator cend() NOEXCEPT        { return const_iterator(_chunks.data(), _end); }
    
    reverse_iterator rbegin() NOEXCEPT             { return reverse_iterator(end()); }
    reverse_iterator rend() NOEXCEPT               { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const NOEXCEPT { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const NOEXCEPT   { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() NOEXCEPT      { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() NOEXCEPT        { return const_reverse_iterator(cbegin()); }
    
private:
    void push_back()
    {
        _valType* endVal = _alloc_back();
        ::new((void*)endVal) value_type();
        ++_end;
    }
    
    void push_front()
    {
        _valType* frontVal = _alloc_front();
        ::new((void*)frontVal) value_type();
        --_start;
    }
    
    pointer _alloc_back()
    // return a pointer to an allocated, uninitialized block of memory at the back
    {
        size_t _chunkNum = _end >> _power2;
        if (_chunks.size() <= _chunkNum) {
            pointer newChunk = nullptr;
            if (_start >= _chunk_size) {
                // Borrow from the front if we can
                newChunk = _chunks.front();
                _chunks.erase(_chunks.begin());
                _start -= _chunk_size;
                _end -= _chunk_size;
                --_chunkNum;
            } else {
                newChunk = _valAlloc.allocate(_chunk_size);
            }
            _chunks.push_back(newChunk);
        }
        return _chunks[_chunkNum] + (_end & _chunk_mask);
    }
    
    pointer _alloc_front()
    // return a pointer to an allocated, uninitialized block of memory at the front
    {
        if (_start == 0) {
            pointer newChunk = nullptr;
            if (capacity() - _end >= _chunk_size) {
                // Borrow from the back if we can
                newChunk = _chunks.back();
                _chunks.pop_back();
            } else {
                newChunk =  _valAlloc.allocate(_chunk_size);
            }
            _chunks.insert(_chunks.begin(), newChunk);
            _start += _chunk_size;
            _end += _chunk_size;
        }
        size_t _front = _start - 1;
        size_t _chunkNum = _front >> _power2;
        return _chunks[_chunkNum] + (_front & _chunk_mask);
    }
    
    void _shrink_to_fit(bool shrinkFront)
    {
        while (shrinkFront && _start >= _chunk_size) {
            _valAlloc.deallocate(_chunks.front(), _chunk_size);
            _chunks.erase(_chunks.begin());
            _start -= _chunk_size;
            _end -= _chunk_size;
        }
        while (capacity() - _end >= _chunk_size) {
            _valAlloc.deallocate(_chunks.back(), _chunk_size);
            _chunks.pop_back();
        }
    }
};

#endif  // INCLUDE_CHUNK_VECTOR_H
