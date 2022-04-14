#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <string>
//index of
//robots.txt

namespace ft {
	template <class Type, class Allocator = std::allocator<Type> >
	// template <class Allocator = allocator<bool>>
	// class vector<bool, Allocator>
	class vector {
		private:
			allocator_type  _alloc;
			pointer         _start;
			pointer         _end;
			pointer         _end_capacity;
		
		public:
			typedef Type value_type;
			typedef Type value_type;
			typedef Type const const_value_type;
			typedef Allocator allocator_type;
			
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			size_type max_size() const { return (this->_alloc.max_size()); };

			template<typename _T>
			VectorIterator(VectorIterator<_T> const &ve) : ptr((_T*)ve.getPtr()) {}
			
			size_type capacity() const;
			void reserve (size_type n);
			
			reference operator[] (size_type n);
			const_reference operator[] (size_type n) const;

			reference at (size_type n);
			const_reference at (size_type n) const;
	}; // class

	// 
	// void assign(size_type count, const Type& value);
	// void assign(initializer_list<Type> init_list);
	// template <class InputIterator>
	// void assign(InputIterator first, InputIterator last);

};	//namespace ft

/*
operator!=
operator==
operator<
operator<=
operator>
operator>=
*/

#endif
