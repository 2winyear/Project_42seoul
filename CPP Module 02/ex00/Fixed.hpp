#ifndef FIXED_HPP
#define FIXED_HPP
#include <iostream>

class Fixed {
    private:
        int _value;
        const static int _bits = 8;

    public:
        int getRawBits( void ) const;
        void setRawBits( int const raw );

		Fixed(void);
		Fixed(const Fixed &src);
		~Fixed(void);
		Fixed &operator=(Fixed const &src);
};

#endif