#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>

class Fixed {
    private:
        int _value;
        const static int _bits = 8;

    public:
		Fixed(void);
        Fixed(const int fixed);
		Fixed(const double fixed);
        Fixed(const Fixed& src);
        Fixed &operator=(Fixed const &src);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		int		toInt(void) const;
		float	toFloat(void) const;
		~Fixed(void);
};

#endif