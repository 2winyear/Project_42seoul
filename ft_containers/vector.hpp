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

			/*
			typedef VectorIterator<T> iterator;
			typedef VectorIterator<const T> const_iterator;
			typedef VectorReverseIterator<T> reverse_iterator;
			typedef VectorReverseIterator<const T> const_reverse_iterator;
			*/
			template<typename _T>
			VectorIterator(VectorIterator<_T> const &ve) : ptr((_T*)ve.getPtr()) {}
			
			
			size_type capacity() const { return (this->_end_capacity - this->_start); };

			void reserve (size_type n)
			{
				if (n > this->max_size())
					throw out_of_range("length_error");	
				if (n <= this->capacity())
					return ;
			}
			
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
