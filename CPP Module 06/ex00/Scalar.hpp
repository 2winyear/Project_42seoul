#ifndef SCALAR_HPP
#define SCALAR_HPP
#include <iostream>

class Scalar {
	private:
		const std::string value;
		Scalar() : value("error"){};

	public:
		Scalar(std::string const &value) : value(value){};
		~Scalar(){};
		std::string const &getValue();
		char toChar() const;
		int toInt() const;
		float toFloat() const;
		double toDouble() const;

		class ImpossableException : public std::exception
		{
			const char *what() const throw()
			{
				return "impossible";
			}
		};
		class NonDisplayException : public std::exception
		{
			const char *what() const throw()
			{
				return "Non displayable";
			}
		};
};

std::ostream &operator<<(std::ostream &os, Scalar &Scalar); 

#endif
