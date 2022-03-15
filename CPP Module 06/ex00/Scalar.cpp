#include "Scalar.hpp"

char Scalar::toChar() const
{
	int n;

	try
	{
		n = std::stoi(this->value);
		if (n < 0 || n > 255)
			throw ImpossableException();
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (static_cast<char>(n));
}

int Scalar::toInt() const
{
	int n;

	try
	{
		n = std::stoi(this->value);
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (n);
}

float Scalar::toFloat() const
{
	float f;

	try
	{
		f = std::stoi(this->value);
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (f);
}

double Scalar::toDouble() const
{
	float f;

	try
	{
		f = std::stoi(this->value);
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (f);
}

std::ostream &operator<<(std::ostream &os, const Scalar &scalar)
{
	os << "char: ";
	try
	{
		char c = scalar.toChar();
		os << "'" << c << "'" << std::endl;
	}
	catch (const std::exception &e)
	{
		os << e.what() << std::endl;
	}

	os << "int: ";
	try
	{
		char c = scalar.toInt();
		os << "'" << c << "'" << std::endl;
	}
	catch (const std::exception &e)
	{
		os << e.what() << std::endl;
	}
}