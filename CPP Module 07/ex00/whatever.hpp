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
		Whatever(int const &value)
		{
			this->value = value;
		};
		Whatever(Whatever const &other)
		{
			*this = other;
		}
		Whatever &operator=(Whatever const &other)
		{
			if (this != &other)
				this->value = other.value;
			return *this;
		}
		~Whatever(){};

		bool operator<(Whatever const &other) const
		{
			return (this->value < other.value);
		}
		bool operator>(Whatever const &other) const
		{
			return (this->value > other.value);
		}
		int getValue() const
		{
			return this->value;
		};
};

std::ostream &operator<<(std::ostream &out, Whatever const &whatever)
{
	out << whatever.getValue();
	return (out);
}

#endif
