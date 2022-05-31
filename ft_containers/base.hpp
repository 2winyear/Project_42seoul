#ifndef BASE_HPP
# define BASE_HPP

namespace ft {
	template <typename T>
	struct lstNode
	{
		T 		data;
		lstNode *next;
		lstNode *prev;
	};
	
} //namespace

#endif