#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <limits>
#include <memory>
#include <stdexcept>

#include "algorithm.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {
template <typename _Tp, class Allocator = std::allocator<_Tp> >
class vector {
 public:
  typedef _Tp value_type;
  typedef Allocator allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef typename std::size_t size_type;
  typedef typename std::ptrdiff_t difference_type;

  typedef ft::random_access_iterator<value_type> iterator;
  typedef ft::random_access_iterator<const value_type> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  allocator_type __alloc;
  pointer __begin;
  pointer __end;
  pointer __capacity;

 public:
  /* ==============================Constructor===============================*/
  explicit vector()
      : __alloc(std::allocator<_Tp>()),
        __begin(ft::nulptr),
        __end(ft::nulptr),
        __capacity(ft::nulptr) {}
  explicit vector(size_type n, const value_type &val = value_type())
      : __alloc(std::allocator<_Tp>()) {
    __vallocate(n);
    __construct_at_end(n, val);
  }
  template <class InputIterator>
  vector(InputIterator begin, InputIterator end,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type
             * = ft::nulptr)
      : __alloc(std::allocator<_Tp>()) {
    size_type _size = ft::distance(begin, end);
    __vallocate(_size);
    __construct_at_end(_size);
    std::copy(begin, end, __begin);
  }
  vector(const vector &vec) : __alloc(vec.__alloc) {
    __vallocate(vec.size());
    __construct_at_end(vec.size(), vec.__begin, vec.__end);
  }
  vector &operator=(const vector &x) {
    if (this != &x) assign(x.__begin, x.__end);
    return *this;
  }
  /* ========================================================================*/

  /* ===============================Destructor===============================*/
  ~vector() {
    if (__begin != ft::nulptr) {
      size_type __pre_capacity = capacity();
      clear();
      __alloc.deallocate(__begin, __pre_capacity);
    }
  }
  /* ========================================================================*/

  /* ===============================Iterators================================*/
  iterator begin() { return iterator(__begin); }
  const_iterator begin() const { return const_iterator(__begin); }
  iterator end() { return iterator(__end); }
  const_iterator end() const { return const_iterator(__end); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }
  /* ========================================================================*/

  /* ===============================Capacity=================================*/
  size_type size() const { return ft::distance(__begin, __end); }
  size_type max_size() const {
    return ft::min<size_type>(std::numeric_limits<difference_type>::max(),
                              __alloc.max_size());
  }
  void resize(size_type __n, value_type val = value_type()) {
    if (size() < __n) {
      size_type __sz = __n - size();
      if (capacity() < __n) reserve(__n);
      __construct_at_end(__sz, val);
    } else if (size() > __n) {
      size_type __sz = size() - __n;
      __destruct_at_end(__sz);
    }
  }
  size_type capacity() const {
    return static_cast<size_type>(__capacity - __begin);
  }
  bool empty() const { return __begin == __end; }
  void reserve(size_type __n) {
    if (max_size() < __n) throw("too big");
    if (__n <= capacity()) return;
    pointer __prev_begin, __prev_end;
    size_type __pre_capacity = capacity();
    size_type __pre_size = size();
    __prev_begin = __prev_end = __alloc.allocate(__n);
    ft::swap(__prev_begin, __begin);
    ft::swap(__prev_end, __end);
    __construct_at_end(__pre_size, __prev_begin, __prev_end);
    __destruct_at_end(__prev_begin, __prev_end);
    __alloc.deallocate(__prev_begin, __pre_capacity);
    __capacity = __begin + __n;
  }
  /* ========================================================================*/

  /* ============================Element access==============================*/
  reference operator[](size_type __idx) { return *(__begin + __idx); }
  reference operator[](size_type __idx) const { return *(__begin + __idx); }
  reference at(size_type __idx) {
    if (__idx >= size()) {
      throw std::out_of_range("out of range");
    }
    return *(__begin + __idx);
  }
  const_reference at(size_type __idx) const {
    if (__idx >= size()) throw std::out_of_range("out of range");
    return *(__begin + __idx);
  }
  reference front() { return *__begin; }
  const_reference front() const { return *__begin; }
  reference back() { return *(__end - 1); }
  const_reference back() const { return *(__end - 1); }
  /* ========================================================================*/

  /* ===============================Modifiers================================*/
  template <class InputIterator>
  void assign(
      InputIterator __first, InputIterator __last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          ft::nulptr) {
    size_type __size = ft::distance(__first, __last);
    size_type __capa = capacity();
    if (__capa < __size) reserve(__size);
    std::copy(__first, __last, __begin);
    __end = __begin + __size;
  }
  void assign(size_type __n, const value_type &val) {
    if (capacity() < __n) reserve(__n);
    std::fill(__begin, __begin + __n, val);
    __end = __begin + __n;
  }
  void push_back(const value_type &val) {
    size_type __capa = capacity();
    if (size() == __capa) reserve(__capa ? __capa * 2 : 1);
    __construct_at_end(1, val);
  }
  void pop_back() { __destruct_at_end(1); }

  iterator insert(iterator __ret, const value_type &val) {
    size_type __capa = capacity();
    difference_type __diff = ft::distance(begin(), __ret);
    if (__capa == size()) reserve(__capa ? __capa * 2 : 1);
    pointer __pos = __begin + __diff;
    __construct_at_end(1, val);
    std::copy(__pos, __end - 1, __pos + 1);
    *__pos = val;
    return __pos;
  }
  void insert(iterator __pos, size_type __n, const value_type &val) {
    size_type __capa = capacity();
    difference_type __diff = ft::distance(begin(), __pos);
    if (__capa < size() + __n) reserve(size() + __n);
    pointer __iter = __begin + __diff;
    __construct_at_end(__n, val);
    std::copy(__iter, __end - __n, __iter + __n);
    std::fill(__iter, __iter + __n, val);
  }
  template <class InputIterator>
  void insert(
      iterator __pos, InputIterator __first, InputIterator __last,
      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * =
          ft::nulptr) {
    size_type __capa = capacity();
    difference_type __n = ft::distance(__first, __last);
    difference_type __diff = ft::distance(begin(), __pos);
    if (__capa < size() + __n) reserve(size() + __n);
    pointer __iter = __begin + __diff;
    __construct_at_end(__n, 0);
    std::copy(__begin + __diff, __end, __iter + __n);
    std::copy(__first, __last, __iter);
  }
  iterator erase(iterator __pos) {
    difference_type diff = ft::distance(begin(), __pos);
    pointer __iter = __begin + diff;
    std::copy(__iter + 1, __end, __iter);
    __destruct_at_end(1);
    return iterator(__iter);
  }
  iterator erase(iterator __first, iterator __last) {
    difference_type __len = ft::distance(__first, __last);
    std::copy(__last, end(), __first);
    __destruct_at_end(__len);
    return __first;
  }
  void swap(vector &vec) {
    ft::swap(__begin, vec.__begin);
    ft::swap(__end, vec.__end);
    ft::swap(__capacity, vec.__capacity);
    ft::swap(__alloc, vec.__alloc);
  }
  void clear() { __destruct_at_end(this->__begin); }
  /* ========================================================================*/

  /* ===============================Allocator================================*/
  allocator_type get_allocator() const { return __alloc; }
  /* ========================================================================*/

 private:
  void __vallocate(size_type __n) {
    if (__n > max_size()) throw std::length_error("too big");
    __end = __begin = __alloc.allocate(__n);
    __capacity = __begin + __n;
  }
  void __construct_at_end(size_type __n) {
    for (; __n; --__n) __alloc.construct(__end++);
  }
  void __construct_at_end(size_type __n, _Tp __val) {
    for (; __n; --__n) __alloc.construct(__end++, __val);
  }
  void __construct_at_end(size_type __n, pointer first, pointer end) {
    for (; __n && first != end; --__n) __alloc.construct(__end++, *(first++));
  }
  void __destruct_at_end(pointer pos) {
    for (; __end != pos;) __alloc.destroy(--__end);
  }
  void __destruct_at_end(size_type __n) {
    for (; __n && __end; --__n) __alloc.destroy(--__end);
  }
  void __destruct_at_end(pointer first, pointer end) {
    for (; first != end;) __alloc.destroy(--end);
  }
};

/* ===============================Non-member===============================*/
template <typename __Tp, class Allocator>
bool operator==(const ft::vector<__Tp, Allocator> &__lhs,
                const ft::vector<__Tp, Allocator> &__rhs) {
  return __lhs.size() == __rhs.size() &&
         ft::equal(__lhs.begin(), __lhs.end(), __rhs.begin());
}
template <typename __Tp, class Allocator>
bool operator!=(const ft::vector<__Tp, Allocator> &__lhs,
                const ft::vector<__Tp, Allocator> &__rhs) {
  return !(__lhs == __rhs);
}
template <typename __Tp, class Allocator>
bool operator<(const ft::vector<__Tp, Allocator> &__lhs,
               const ft::vector<__Tp, Allocator> &__rhs) {
  return ft::lexicographical_compare(__lhs.begin(), __lhs.end(), __rhs.begin(),
                                     __rhs.end());
}
template <typename __Tp, class Allocator>
bool operator<=(const ft::vector<__Tp, Allocator> &__lhs,
                const ft::vector<__Tp, Allocator> &__rhs) {
  return !(__lhs > __rhs);
}
template <typename __Tp, class Allocator>
bool operator>(const ft::vector<__Tp, Allocator> &__lhs,
               const ft::vector<__Tp, Allocator> &__rhs) {
  return __rhs < __lhs;
}
template <typename __Tp, class Allocator>
bool operator>=(const ft::vector<__Tp, Allocator> &__lhs,
                const ft::vector<__Tp, Allocator> &__rhs) {
  return !(__lhs < __rhs);
}
template <typename __Tp, class Allocator>
void swap(ft::vector<__Tp, Allocator> &x, ft::vector<__Tp, Allocator> &y) {
  x.swap(y);
}
/* ========================================================================*/
}  // namespace ft

#endif  // __VECTOR_HPP__
