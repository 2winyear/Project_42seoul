#ifndef LIST_HPP
#define LIST_HPP
//https://www.notion.so/LIST-bdb189e5ebd5486f8dc9ff32c4d02f45
//https://github.dev/mli42/at42ft_containers/blob/master/list.hpp
#include <iostream>


namespace ft
{
	template <typename T, class Alloc = std::allocator<T> >
	class list {
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			

			explicit list (const allocator_type& alloc = allocator_type());
			explicit list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());

			list& operator= (const list& x);


			iterator begin();
			const_iterator begin() const;
			iterator end();
			const_iterator end() const;
			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
			bool empty() const;
			size_type size() const;
			size_type max_size() const;
			reference front();
			const_reference front() const;
		
	}; //class list
} //namespace ft

#endif
