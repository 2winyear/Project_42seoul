#include "Fixed.hpp"
Fixed::Fixed(void)
{
    _value = 0;
}

Fixed::~Fixed(void)
{

}

Fixed::Fixed(const int value)
{
    _value = value << _bits;
    std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value)
{
    _value = roundf(value * (1 << _bits));
}

Fixed::Fixed(const Fixed &src)
{
    *this = src;
}

Fixed const &Fixed::max(Fixed const & f1, Fixed const & f2)
{
    if (f1 < f2)
        return(f2);
    return (f1);
}

Fixed const &Fixed::min(Fixed const & f1, Fixed const & f2)
{
    if (f1 < f2)
        return(f1);
    return (f2);
}

Fixed   &Fixed::operator=(Fixed const &src)
{
    _value = src._value;
    return (*this);
}

Fixed   &Fixed::operator++(void)
{
    this->_value++;
    return (*this);
}

Fixed   Fixed::operator++(int)
{
    Fixed f(*this);
    this ->_value++;
    return (f);
}

Fixed   Fixed::operator+(Fixed const &src) const
{
    return (Fixed(this->toFloat() + src.toFloat()));
}

Fixed   Fixed::operator-(Fixed const &src) const
{
    return (Fixed(this->toFloat() - src.toFloat()));
}

Fixed   Fixed::operator*(Fixed const &src) const
{
    return (Fixed(this->toFloat() * src.toFloat()));
}

Fixed   Fixed::operator/(Fixed const &src) const
{
    return (Fixed(this->toFloat() / src.toFloat()));
}


bool	Fixed::operator<(Fixed const &src) const
{
    return (this->_value < src._value);
}

bool	Fixed::operator>(Fixed const &src) const
{
	return (this->_value > src._value);
}

bool    Fixed::operator>=(Fixed const &src) const
{
	return (this->_value >= src._value);
}

bool    Fixed::operator<=(Fixed const &src) const
{
	return (this->_value <= src._value);
}

bool    Fixed::operator!=(Fixed const &src) const
{
	return (this->_value != src._value);
}

bool    Fixed::operator==(Fixed const &src) const
{
	return (this->_value == src._value);
}

int     Fixed::toInt(void) const
{
    return (_value >> _bits);
}

float   Fixed::toFloat(void) const
{
    return (float(_value) / (1 << _bits));
}

int     Fixed::getRawBits(void) const
{
    return (_value);
}

void    Fixed::setRawBits(int const raw)
{
    this->_value = raw;
}

std::ostream&   operator<<(std::ostream &out, const Fixed &fixed)
{
    out << fixed.toFloat();
    return out;
}
