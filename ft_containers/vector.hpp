#include <iostream>

template<typename _T>
VectorIterator(VectorIterator<_T> const &ve) : ptr((_T*)ve.getPtr()) {}
size_type capacity() const;
reference operator[] (size_type n);
const_reference operator[] (size_type n) const;

reference at (size_type n);
const_reference at (size_type n) const;
void reserve (size_type n);

- `operator!=`
- `operator==`
- `operator<`
- `operator<=`
- `operator>`
- `operator>=`