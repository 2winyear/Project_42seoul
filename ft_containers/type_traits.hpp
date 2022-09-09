#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft {

/* nullptr_t */
const class nullptr_t {
 private:
  void operator&(void) const;

 public:
  template <typename T>
  operator T*(void) const { return 0; }

  template <typename T, typename U>
  operator T U::*(void) const { return 0; }
} nil = {};

/* integral_constant */
template < typename T, T v >
struct integral_constant {
    typedef T value_type;
    typedef integral_constant type;

    static const value_type value = v;

    operator value_type(void) const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


/* remove_cv */
template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };


/* is_integral_base */
template <typename T>
struct is_integral_base : public false_type {};

template <>
struct is_integral_base<bool> : public true_type {};

template <>
struct is_integral_base<char> : public true_type {};

template <>
struct is_integral_base<unsigned char> : public true_type {};

template <>
struct is_integral_base<signed char> : public true_type {};

template <>
struct is_integral_base<wchar_t> : public true_type {};

template <>
struct is_integral_base<short> : public true_type {};

template <>
struct is_integral_base<unsigned short> : public true_type {};

template <>
struct is_integral_base<int> : public true_type {};

template <>
struct is_integral_base<unsigned int> : public true_type {};

template <>
struct is_integral_base<long> : public true_type {};

template <>
struct is_integral_base<unsigned long> : public true_type {};

template <>
struct is_integral_base<int64_t> : public true_type {};

template <>
struct is_integral_base<uint64_t> : public true_type {};


/* is_integral */
template< class T >
struct is_integral
    : public is_integral_base<typename remove_cv<T>::type> {};


/* enable_if */
template<bool B, class T = void>
struct enable_if {};
 
template<class T>
struct enable_if<true, T> { typedef T type; };
}

#endif
