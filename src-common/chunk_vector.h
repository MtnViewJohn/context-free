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

#if defined(_MSC_VER) && !defined(noexcept)
#define noexcept throw()
#endif

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
    pointer     _current;
    size_type   _size;
    size_type   _index;
    
    chunk_vector_iterator(_valType** vals, size_t size, bool begin)
        : _chunksPtr(vals), _size(size), _index(begin ? 0 : size)
    {
        _set_current();
    }
    
    template <typename _vT, unsigned _p2, typename _Alloc>
    friend class chunk_vector;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator==(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator!=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator<(const chunk_vector_iterator<_valType1, _p2>& __x,
                          const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator>(const chunk_vector_iterator<_valType1, _p2>& __x,
                          const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator<=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
    template<typename _valType1, typename _valType2, unsigned _p2>
    friend bool operator>=(const chunk_vector_iterator<_valType1, _p2>& __x,
                           const chunk_vector_iterator<_valType2, _p2>& __y) noexcept;
    
public:
    chunk_vector_iterator(const chunk_vector_iterator& cvi)
        : _chunksPtr(cvi._chunksPtr), _current(cvi._current), _size(cvi._size), _index(cvi._index)
    { }
    chunk_vector_iterator()
        : _chunksPtr(nullptr), _current(nullptr), _size(0), _index(0)
    { }
    
    chunk_vector_iterator& operator=(const chunk_vector_iterator& rhs)
    {
        _chunksPtr = rhs._chunksPtr;
        _current = rhs._current;
        _size = rhs._size;
        _index = rhs._index;
        return *this;
    }

    reference operator*() const
    { return *_current; }

    pointer operator->() const
    { return _current; }

    chunk_vector_iterator& operator++()
    {
        ++_index;
        _set_current();
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
        _set_current();
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
        _set_current();
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
        _set_current();
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
        size_t i = _index + n;
        if (i < _size) {
            _valType* val = _chunksPtr[i >> _power2] + (i & _chunk_mask);
            return *val;
        }
        return *_current;
    }
    
    bool operator<(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index < rhs._index;
    }
    
    bool operator>(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index > rhs._index;
    }
    
    bool operator<=(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index <= rhs._index;
    }
    
    bool operator>=(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index >= rhs._index;
    }
    
    bool operator==(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index == rhs._index;
    }
    
    bool operator!=(const chunk_vector_iterator& rhs) const noexcept
    {
        return _index != rhs._index;
    }
    
private:
    void _set_current()
    {
        if (_index < _size)
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
    }
};

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator==(const chunk_vector_iterator<_valType1, _power2>& __x,
	                   const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index == __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator!=(const chunk_vector_iterator<_valType1, _power2>& __x,
	                   const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index != __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<(const chunk_vector_iterator<_valType1, _power2>& __x,
	                  const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index < __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>(const chunk_vector_iterator<_valType1, _power2>& __x,
	                  const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index > __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<=(const chunk_vector_iterator<_valType1, _power2>& __x,
	                   const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index <= __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>=(const chunk_vector_iterator<_valType1, _power2>& __x,
	                   const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    assert(__x._chunksPtr == __y.chunksPtr && __x._size == __y._size);
    return __x._index >= __y._index;
}

template<typename _valType, unsigned _power2>
inline chunk_vector_iterator<_valType, _power2> operator+(ptrdiff_t __n,
	                   const chunk_vector_iterator<_valType, _power2>& __x) noexcept
{ return __x + __n; }

template <typename _valType, unsigned _power2, typename _Alloc = std::allocator<_valType>>
class chunk_vector {
private:
    size_t _size;
    std::vector<_valType*> _chunks;
    _Alloc _valAlloc;
    enum consts_e {
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
        : _size(0)
    {
        assert(_valAlloc.max_size() >= _chunk_size);
    }
    ~chunk_vector() { clear(); _shrink_to_fit(); }

    void push_back(const_reference x)
    {
        size_t chunkNum = _size >> _power2;
        if (_chunks.size() <= chunkNum)
            _chunks.push_back(_valAlloc.allocate(_chunk_size));
        _valType* endVal = _chunks[chunkNum] + (_size & _chunk_mask);
        _valAlloc.construct(endVal, x);
        ++_size;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        size_t chunkNum = _size >> _power2;
        if (_chunks.size() <= chunkNum)
            _chunks.push_back(_valAlloc.allocate(_chunk_size));
        _valType* endVal = _chunks[chunkNum] + (_size & _chunk_mask);
        _valAlloc.construct(endVal, std::forward<Args>(args)...);
        ++_size;
        
    }
    
    void pop_back()
    {
        if (_size == 0) return;
        --_size;
        _valType* endVal = _chunks[_size >> _power2] + (_size & _chunk_mask);
        _valAlloc.destroy(endVal);
    }
    
    size_type size() const noexcept { return _size; }
    
    bool empty() const noexcept { return _size == 0; }
    
    void clear() noexcept
    {
        for (size_t chunkNum = 0, num2delete = _size; num2delete; ++chunkNum) {
            size_t valCount = num2delete > _chunk_size ? _chunk_size : num2delete;
            _valType* chunk = _chunks[chunkNum];
            for (size_t valNum = 0; valNum < valCount; ++valNum)
                _valAlloc.destroy(chunk + valNum);
            num2delete -= valCount;
        }
        _size = 0;
    }
    
    void shrink_to_fit()
    {
        _shrink_to_fit();
        _chunks.shrink_to_fit();
    }
    
    void resize(size_type newSize, const_reference x)
    {
        reserve(newSize);
        while (newSize > _size)
            push_back(x);
        while (newSize < _size)
            pop_back();
    }
    
    void resize(size_type newSize)
    {
        reserve(newSize);
        while (newSize > _size)
            push_back();
        while (newSize < _size)
            pop_back();
    }
    
    void swap(chunk_vector<_valType, _power2, _Alloc>& with)
    {
        size_t tempsize = _size;
        _Alloc tempalloc = _valAlloc;
        _size = with._size;
        _valAlloc = with._valAlloc;
        with._size = tempsize;
        with._valAlloc = tempalloc;
        _chunks.swap(with._chunks);
        _shrink_to_fit();   // no reallocation of _chunks, iterators stay valid
    }
    
    void reserve(size_type n)
    {
        size_t chunksNeeded = _size ? (_size >> _power2) + 1 : 0;
        if (_chunks.size() >= chunksNeeded)
            return;
        _chunks.reserve(chunksNeeded);
        for (size_type num = chunksNeeded - _chunks.size(); num; --num)
             _chunks.push_back(_valAlloc.allocate(_chunk_size));
    }
    
    size_type capacity() const noexcept
    {
        return _chunks.size() << _power2;
    }

    reference operator[](size_t i)
    {
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    const_reference operator[](size_t i) const
    {
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    
    reference at(size_t i)
    {
        if (i >= _size)
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    const_reference at(size_t i) const
    {
        if (i >= _size)
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    
    reference front() { return (*this)[0]; }
    const_reference front() const { return (*this)[0]; }
    
    reference back() { return (*this)[_size - 1]; }
    const_reference back() const { return (*this)[_size - 1]; }

    iterator begin() noexcept             { return iterator(_chunks.data(), _size, true); }
    iterator end() noexcept               { return iterator(_chunks.data(), _size, false); }
    const_iterator begin() const noexcept { return const_iterator(_chunks.data(), _size, true); }
    const_iterator end() const noexcept   { return const_iterator(_chunks.data(), _size, false); }
    const_iterator cbegin() noexcept      { return const_iterator(_chunks.data(), _size, true); }
    const_iterator cend() noexcept        { return const_iterator(_chunks.data(), _size, false); }
    
    reverse_iterator rbegin() noexcept             { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept               { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept   { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() noexcept      { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() noexcept        { return const_reverse_iterator(cbegin()); }
    
private:
    void push_back()
    {
        size_t chunkNum = _size >> _power2;
        if (_chunks.size() <= chunkNum)
            _chunks.push_back(_valAlloc.allocate(_chunk_size));
        _valType* endVal = _chunks[chunkNum] + (_size & _chunk_mask);
        ::new(reinterpret_cast<void*>(endVal)) value_type();
        ++_size;
    }
    
    void _shrink_to_fit()
    {
        size_t chunksNeeded = _size ? (_size >> _power2) + 1 : 0;
        for (size_t chunkNum = chunksNeeded; chunkNum < _chunks.size(); ++chunkNum)
            _valAlloc.deallocate(_chunks[chunkNum], _chunk_size);
        _chunks.resize(chunksNeeded);
    }
};

#endif  // INCLUDE_CHUNK_VECTOR_H
