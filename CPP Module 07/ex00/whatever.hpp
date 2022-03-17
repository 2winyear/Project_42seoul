#ifndef WHATEVER_HPP
#define WHATEVER_HPP
#include <string>
#include <iostream>

template < typename T >
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template < typename T >
T const & min(T &x, T &y)
{
    return (x < y ? x : y);
}

template < typename T >
T const & max(T const & x, T const & y)
{
    return (x > y ? x : y);
}

class Whatever {
    private:
		int value;

    public:
		Whatever();
};

#endif