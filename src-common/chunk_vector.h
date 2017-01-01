// chunk_vector.h
// this file is part of Context Free
// ---------------------
// Copyright (C) 2012-2016 John Horigan - john@glyphic.com
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
#include <initializer_list>

template <typename _valType, unsigned _power2>
struct chunk_vector_iterator
{
    using iterator_category = std::random_access_iterator_tag;
    using value_type        = _valType;
    using pointer           = _valType*;
    using reference         = _valType&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    
private:
    enum consts_e : unsigned {
        _chunk_size = 1 << _power2,
        _chunk_mask = _chunk_size - 1
    };
    
    pointer const * _chunksPtr;
    size_type       _index;
    
    chunk_vector_iterator(pointer const * vals, std::size_t index)
        : _chunksPtr(vals), _index(index)
    {
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
    
    void swap(chunk_vector_iterator& o)
    {
        auto _ti  = _index;     _index     = o._index;     o._index     = _ti;
        auto _tcp = _chunksPtr; _chunksPtr = o._chunksPtr; o._chunksPtr = _tcp;
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
        return *_get_current(n);
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
    pointer _get_current(difference_type n = 0) const
    {
        return _chunksPtr[(_index + n) >> _power2] + ((_index + n) & _chunk_mask);
    }
};

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator==(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index == __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator!=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index != __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<(const chunk_vector_iterator<_valType1, _power2>& __x,
                      const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index < __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>(const chunk_vector_iterator<_valType1, _power2>& __x,
                      const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index > __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator<=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index <= __y._index;
}

template<typename _valType1, typename _valType2, unsigned _power2>
inline bool operator>=(const chunk_vector_iterator<_valType1, _power2>& __x,
                       const chunk_vector_iterator<_valType2, _power2>& __y) noexcept
{
    static_assert(std::is_same<typename std::remove_const<_valType1>::type,
                               typename std::remove_const<_valType2>::type>::value,
                  "Types must match, modulo const");
    return __x._index >= __y._index;
}

template<typename _valType, unsigned _power2>
inline chunk_vector_iterator<_valType, _power2> operator+(std::ptrdiff_t __n,
                       const chunk_vector_iterator<_valType, _power2>& __x) noexcept
{ return __x + __n; }

template<typename _valType, unsigned _power2>
void swap(chunk_vector_iterator<_valType, _power2>& s, chunk_vector_iterator<_valType, _power2>& t)
{ s.swap(t); }
    
template <typename _valType, unsigned _power2, typename _Alloc = std::allocator<_valType>>
class chunk_vector {
private:
    std::size_t _start = 0;
    std::size_t _end = 0;
    std::vector<_valType*> _chunks;
    _Alloc _valAlloc;
    enum consts_e : size_t {
        _chunk_size = 1 << _power2,
        _chunk_mask = _chunk_size - 1
    };

public:
    using value_type             = _valType;
    using pointer                = typename _Alloc::pointer;
    using const_pointer          = typename _Alloc::const_pointer;
    using reference              = typename _Alloc::reference;
    using const_reference        = typename _Alloc::const_reference;
    using iterator               = chunk_vector_iterator<_valType, _power2>;
    using const_iterator         = chunk_vector_iterator<const _valType, _power2>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using allocator_type         = _Alloc;

    chunk_vector()
    {
        assert(_valAlloc.max_size() >= _chunk_size);
    }
    chunk_vector(std::initializer_list<value_type> l)
    {
        assert(_valAlloc.max_size() >= _chunk_size);
        reserve(l.size());
        for (auto&& v: l)
            push_back(v);
    }
    chunk_vector(const chunk_vector& o)
    {
        assert(_valAlloc.max_size() >= _chunk_size);
        reserve(o.size());
        for (auto&& v: o)
            push_back(v);
    }
    chunk_vector(chunk_vector&& o) noexcept(noexcept(_chunks.swap(o._chunks)))
    {
        assert(_valAlloc.max_size() >= _chunk_size);
        _start = o._start;  o._start = 0;
        _end = o._end;      o._end = 0;
        _chunks.swap(o._chunks);
    }
    
    chunk_vector& operator=(const chunk_vector& o)
    {
        clear();
        reserve(o.size());
        for (auto&& v: o)
            push_back(v);
        return *this;
    }
    
    chunk_vector& operator=(chunk_vector&& o) noexcept(noexcept(_chunks.swap(o._chunks)))
    {
        clear();
        shrink_to_fit();
        _start = o._start;  o._start = 0;
        _end = o._end;      o._end = 0;
        _chunks.swap(o._chunks);
        return *this;
    }
    
    chunk_vector& operator=(std::initializer_list<value_type> l)
    {
        clear();
        reserve(l.size());
        for (auto&& v: l)
            push_back(v);
        return *this;
    }
    
    ~chunk_vector() { clear(); _shrink_to_fit(true); }

    void push_back(const value_type& x)
    {
        auto endVal = _alloc_back();
        _valAlloc.construct(endVal, x);
        ++_end;
    }
    
    void push_back(value_type&& x)
    {
        auto endVal = _alloc_back();
        _valAlloc.construct(endVal, std::move(x));
        ++_end;
    }
    
    template<typename... Args>
    void emplace_back(Args&&... args)
    {
        auto endVal = _alloc_back();
        _valAlloc.construct(endVal, std::forward<Args>(args)...);
        ++_end;
    }
    
    void pop_back()
    {
        if (_start == _end) return;
        --_end;
        auto endVal = _chunks[_end >> _power2] + (_end & _chunk_mask);
        _valAlloc.destroy(endVal);
    }
    
    void push_front(const value_type& x)
    {
        auto frontVal = _alloc_front();
        _valAlloc.construct(frontVal, x);
        --_start;
    }
    
    void push_front(value_type&& x)
    {
        auto frontVal = _alloc_front();
        _valAlloc.construct(frontVal, std::move(x));
        --_start;
    }
    
    template<typename... Args>
    void emplace_front(Args&&... args)
    {
        auto frontVal = _alloc_front();
        _valAlloc.construct(frontVal, std::forward<Args>(args)...);
        --_start;
        
    }
    
    void pop_front()
    {
        if (_start == _end) return;
        auto frontVal = _chunks[_start >> _power2] + (_start & _chunk_mask);
        ++_start;
        _valAlloc.destroy(frontVal);
    }
    
    size_type size() const noexcept { return _end - _start; }
    
    bool empty() const noexcept { return _start == _end; }
    
    void clear() noexcept
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
        using std::swap;
        swap(_start, with._start);
        swap(_end, with._end);
        swap(_valAlloc, with._valAlloc);
        swap(_chunks, with._chunks);
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
    
    size_type capacity() const noexcept
    {
        return _chunks.size() << _power2;
    }

    reference operator[](std::size_t i)
    {
        i += _start;
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    const_reference operator[](std::size_t i) const
    {
        i += _start;
        _valType* chunk = _chunks[i >> _power2];
        return chunk[i & _chunk_mask];
    }
    
    reference at(std::size_t i)
    {
        if (i >= size())
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    const_reference at(std::size_t i) const
    {
        if (i >= size())
            throw std::out_of_range("chunk_vector::at() range exceeded");
        return (*this)[i];
    }
    
    reference front() { return (*this)[_start]; }
    const_reference front() const { return (*this)[_start]; }
    
    reference back() { return (*this)[_end - 1]; }
    const_reference back() const { return (*this)[_end - 1]; }

    iterator begin() noexcept             { return iterator(_chunks.data(), _start); }
    iterator end() noexcept               { return iterator(_chunks.data(), _end); }
    const_iterator begin() const noexcept { return const_iterator(_chunks.data(), _start); }
    const_iterator end() const noexcept   { return const_iterator(_chunks.data(), _end); }
    const_iterator cbegin() noexcept      { return const_iterator(_chunks.data(), _start); }
    const_iterator cend() noexcept        { return const_iterator(_chunks.data(), _end); }
    
    reverse_iterator rbegin() noexcept             { return reverse_iterator(end()); }
    reverse_iterator rend() noexcept               { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const noexcept   { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() noexcept      { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() noexcept        { return const_reverse_iterator(cbegin()); }
    
private:
    void push_back()
    {
        auto endVal = _alloc_back();
        ::new((void*)endVal) value_type();
        ++_end;
    }
    
    void push_front()
    {
        auto frontVal = _alloc_front();
        ::new((void*)frontVal) value_type();
        --_start;
    }
    
    pointer _alloc_back()
    // return a pointer to an allocated, uninitialized block of memory at the back
    {
        std::size_t _chunkNum = _end >> _power2;
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
        std::size_t _front = _start - 1;
        std::size_t _chunkNum = _front >> _power2;
        return _chunks[_chunkNum] + (_front & _chunk_mask);
    }
    
    void _shrink_to_fit(bool shrinkFront)
    {
        // Special case for empty container
        if (empty()) {
            for (auto&& chunk: _chunks)
                _valAlloc.deallocate(chunk, _chunk_size);
            _chunks.clear();
            _start = _end = 0;
            return;
        }
        // Remove unused chunks from the front
        while (shrinkFront && _start >= _chunk_size) {
            _valAlloc.deallocate(_chunks.front(), _chunk_size);
            _chunks.erase(_chunks.begin());
            _start -= _chunk_size;
            _end -= _chunk_size;
        }
        // Remove unused chunks from the back
        while (capacity() - _end >= _chunk_size) {
            _valAlloc.deallocate(_chunks.back(), _chunk_size);
            _chunks.pop_back();
        }
    }
};

template <typename _valType, unsigned _power2, typename _Alloc = std::allocator<_valType>>
void swap(chunk_vector<_valType, _power2, _Alloc>& s, chunk_vector<_valType, _power2, _Alloc>& t)
{
    s.swap(t);
}

#endif  // INCLUDE_CHUNK_VECTOR_H
