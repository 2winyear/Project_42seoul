#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>
#include <cmath>
class Fixed {
    private:
        int _value;
        const static int _bits = 8;
    public:
        Fixed(void);
        Fixed(const int value);
        Fixed(const float value);
        Fixed(const Fixed& src);

        Fixed   &operator=(Fixed const &src);
        Fixed   &operator++(void);
        Fixed   operator++(int);
        bool    operator<(Fixed const &src) const;
		bool    operator>(Fixed const &src) const;
		bool    operator>=(Fixed const &src) const;
		bool    operator<=(Fixed const &src) const;
		bool    operator!=(Fixed const &src) const;
		bool    operator==(Fixed const &src) const;
        Fixed   operator+(Fixed const &src) const;
        Fixed   operator-(Fixed const &src) const;
        Fixed   operator*(Fixed const &src) const;
        Fixed   operator/(Fixed const &src) const;
        static  const Fixed &max(Fixed const & f1, Fixed const & f2);
        static  const Fixed &min(Fixed const & f1, Fixed const & f2);
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        int     toInt(void) const;
        float   toFloat(void) const;
        ~Fixed(void);
};
std::ostream &operator<<(std::ostream &out, const Fixed & fixed);
#endif
