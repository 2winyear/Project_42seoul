#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include "./iterator_traits.hpp"
#include "./type_traits.hpp"

namespace ft {

/* random_access_iterator 임의 접근 연산자 */
template <typename T>
class random_access_iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
    typedef T* iterator_type;
    typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
    typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
    typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
    typedef typename ft::iterator_traits<iterator_type>::reference reference;
    typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;

    /* constructor & destructor */
    random_access_iterator(void) : _ptr(NULL) {}
    random_access_iterator(pointer ptr) : _ptr(ptr) {}
    template <typename x>
    random_access_iterator(const random_access_iterator &x) { *this = x; }
    ~random_access_iterator(void) {}

    operator const_iterator() const
    {
        return const_iterator(_ptr);
    }

    /* member function for util */ //?
    template <typename x>
    random_access_iterator& operator=(const random_access_iterator &x)
    {
        if (this != &x)
            _ptr = x._ptr;
        return (*this);
    }
    iterator_type base(void) const { return _ptr; }
    pointer operator->(void) const { return _ptr; }
    reference operator*(void) const { return _ptr; }
    reference operator[](difference_type n) const { return _ptr[n]; }

    /* increment & decrement */
    random_access_iterator& operator++(void) {
        ++_ptr;
        return *this;
    }
    random_access_iterator& operator--(void) {
        --_ptr;
        return *this;
    }
    random_access_iterator operator++(int) {
        random_access_iterator tmp(*this);
        ++_ptr;
        return tmp;
    }
    random_access_iterator operator--(int) {
        random_access_iterator tmp(*this);
        --_ptr;
        return tmp;
    }

    /* arithmetic operators */
    random_access_iterator operator+(difference_type n) const {
        return random_access_iterator(_ptr + n);
    }
    random_access_iterator operator-(difference_type n) const {
        return random_access_iterator(_ptr - n);
    }
    random_access_iterator& operator+=(difference_type n) const {
        _ptr += n;
        return *this;
    }
    random_access_iterator& operator-=(difference_type n) const {
        _ptr -= n;
        return *this;
    }

protected: 
    pointer	_ptr;
};

/* special case of arithmetic operators */
template <typename T>
random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n,
                                    const random_access_iterator<T>& i) {
    return random_access_iterator<T>(i.base() + n);
}

template <typename T1, typename T2>
typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& x,
                                                               const random_access_iterator<T2>& y) {
  return x.base() - y.base();
}

/* relational operators */
template <typename T1, typename T2>
bool operator==(const random_access_iterator<T1>& x,
                const random_access_iterator<T2>& y) {
  return x.base() == y.base();
}

template <typename T1, typename T2>
bool operator!=(const random_access_iterator<T1>& x,
                const random_access_iterator<T2>& y) {
  return x.base() != y.base();
}

template <typename T1, typename T2>
bool operator<(const random_access_iterator<T1>& x,
               const random_access_iterator<T2>& y) {
  return x.base() < y.base();
}

template <typename T1, typename T2>
bool operator<=(const random_access_iterator<T1>& x,
                const random_access_iterator<T2>& y) {
  return x.base() <= y.base();
}

template <typename T1, typename T2>
bool operator>(const random_access_iterator<T1>& x,
               const random_access_iterator<T2>& y) {
  return x.base() > y.base();
}

template <typename T1, typename T2>
bool operator>=(const random_access_iterator<T1>& x,
                const random_access_iterator<T2>& y) {
  return x.base() >= y.base();
}

} // namespace ft
/* constructor & destructor */

#endif