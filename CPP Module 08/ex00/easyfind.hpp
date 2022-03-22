#ifndef EASYFIND_HPP
#define EASYFIND_HPP
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <deque>
#include <algorithm>

class OutOfRangeException : public std::exception
{
public:
	const char *what() const throw()
	{
		return "Out of range";
	}
};

template <typename T>
typename T::iterator easyfind(T container, int value)
{
	typename T::iterator it;
	it = std::find(container.begin(), container.end(), value);
	if (it == container.end())
		throw OutOfRangeException();
	return it;
}

#endif
