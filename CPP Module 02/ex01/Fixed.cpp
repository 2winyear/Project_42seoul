#include "Fixed.hpp"

Fixed::Fixed(void)
{
    this->_value = 0;
    std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &src)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed	&Fixed::operator=(Fixed const &src)
{
	std::cout << "Assignation operation called" << std::endl;
	_value = src._value;
	return (*this);
}

int		Fixed::toInt(void) const
{
	return (_value >> _bits);
}

float	Fixed::toFloat(void) const
{
	return (_value << _bits);
}

int		Fixed::getRawBits(void) const
{
	return (_value);
}

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}