#ifndef ITER_HPP
#define ITER_HPP
#include <iostream>
#include <string>

class Whatever {
    private:
		int value;

    public:
		Whatever()
		{

		};
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

template < typename T >
void iter(T *lst, size_t len, void (*f)(T const &))
{
	for (size_t i = 0; i < len; i++)
	{
		f(lst[i]);
	}
}
#endif
