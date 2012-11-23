#include <vector>
#include <iterator>
#include <memory>
#include <cassert>

template <typename _valType, unsigned _power2>
struct chunk_vector_iterator
{
    enum consts_e {
        _chunk_size = 1 << _power2,
        _chunk_mask = _chunk_size - 1
    };
    
    typedef std::random_access_iterator_tag iterator_category;
    typedef _valType                        value_type;
    typedef _valType*                       pointer;
    typedef _valType&                       reference;
    typedef size_t                          size_type;
    typedef ptrdiff_t                       difference_type;
    
    pointer*    _chunksPtr;
    pointer     _current;
    size_type   _size;
    size_type   _index;
    
    chunk_vector_iterator(_valType** vals, size_t size, bool begin)
        : _chunksPtr(vals), _size(size), _index(begin ? 0 : size)
    {
        if (_index < size)
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
    }
    chunk_vector_iterator(const chunk_vector_iterator& cvi)
        : _chunksPtr(cvi._chunksPtr), _current(cvi._current), _size(cvi._size), _index(cvi._index)
    { }
    chunk_vector_iterator()
        : _chunksPtr(0), _current(0), _size(0), _index(0)
    { }

    reference operator*() const
    { return *_current; }

    pointer operator->() const
    { return _current; }

    chunk_vector_iterator& operator++()
    {
        ++_index;
        if (_index < _size)
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
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
        if (_index) {
            --_index;
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
        }
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
        if (_index < _size)
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
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
        if (_index < _size)
            _current = _chunksPtr[_index >> _power2] + (_index & _chunk_mask);
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
};

template<typename _valType, unsigned _power2>
inline bool operator==(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._chunksPtr == __y._chunksPtr && __x._index == __y._index; }

template<typename _valType, unsigned _power2>
inline bool operator!=(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._chunksPtr != __y._chunksPtr || __x._index != __y._index; }

template<typename _valType, unsigned _power2>
inline bool operator<(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._index < __y._index; }

template<typename _valType, unsigned _power2>
inline bool operator>(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._index > __y._index; }

template<typename _valType, unsigned _power2>
inline bool operator<=(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._index <= __y._index; }

template<typename _valType, unsigned _power2>
inline bool operator>=(chunk_vector_iterator<_valType, _power2>& __x,
	                   chunk_vector_iterator<_valType, _power2>& __y)
{ return __x._index >= __y._index; }

template<typename _valType, unsigned _power2>
inline chunk_vector_iterator<_valType, _power2> operator+(ptrdiff_t __n,
	                   chunk_vector_iterator<_valType, _power2>& __x)
{ return __x + __n; }

template <typename _valType, unsigned _power2, typename _Alloc = std::allocator<_valType> >
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
    ~chunk_vector() { clear(); }

    void push_back(const_reference x)
    {
        size_t chunkNum = _size >> _power2;
        if (_chunks.size() <= chunkNum)
            _chunks.push_back(_valAlloc.allocate(_chunk_size));
        _valType* endVal = _chunks[chunkNum] + (_size & _chunk_mask);
        _valAlloc.construct(endVal, x);
        ++_size;
    }
    void pop_back()
    {
        if (_size == 0) return;
        --_size;
        _valType* endVal = _chunks[_size >> _power2] + (_size & _chunk_mask);
        _valAlloc.destroy(endVal);
    }
    size_type size() const { return _size; }
    bool empty() const { return _size == 0; }
    void clear()
    {
        for (size_t chunkNum = 0, num2delete = _size; num2delete; ++chunkNum) {
            size_t valCount = num2delete > _chunk_size ? _chunk_size : num2delete;
            _valType* chunk = _chunks[chunkNum];
            for (size_t valNum = 0; valNum < valCount; ++valNum)
                _valAlloc.destroy(chunk + valNum);
            _valAlloc.deallocate(chunk, _chunk_size);
            num2delete -= valCount;
        }
        _chunks.clear();
        _size = 0;
    }
    void resize(size_type newSize, const_reference x)
    {
        while (newSize > _size)
            push_back(x);
        while (newSize < _size)
            pop_back();
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
    reference front() { return (*this)[0]; }
    const_reference front() const { return (*this)[0]; }
    reference back() { return (*this)[_size - 1]; }
    const_reference back() const { return (*this)[_size - 1]; }

    iterator begin()
    { return iterator(&(_chunks[0]), _size, true); }
    iterator end()
    { return iterator(&(_chunks[0]), _size, false); }
    const_iterator begin() const
    { return const_iterator(&(_chunks[0]), _size, true); }
    const_iterator end() const
    { return const_iterator(&(_chunks[0]), _size, false); }
    reverse_iterator rbegin()
    { return reverse_iterator(&(_chunks[0]), _size, false); }
    reverse_iterator rend()
    { return reverse_iterator(&(_chunks[0]), _size, true); }
    const_reverse_iterator rbegin() const
    { return const_reverse_iterator(&(_chunks[0]), _size, false); }
    const_reverse_iterator rend() const
    { return const_reverse_iterator(&(_chunks[0]), _size, true); }
};
