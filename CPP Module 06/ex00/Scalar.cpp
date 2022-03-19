#include "Scalar.hpp"

char Scalar::toChar() const
{
	int n;

	try
	{
		n = std::stoi(this->value);
		if (n < 0 || n > 128)
			throw ImpossableException();
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	if (!isprint(n))
		throw NonDisplayException();
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
		f = std::stof(this->value);
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (f);
}

double Scalar::toDouble() const
{
	float d;

	try
	{
		d = std::stod(this->value);
	}
	catch(const std::exception& e)
	{
		throw ImpossableException();
	}
	return (d);
}

std::ostream &operator<<(std::ostream &out, const Scalar &scalar)
{
	out << "char: ";
	try
	{
		char c = scalar.toChar();
		out << "'" << c << "'" << std::endl;
	}
	catch (const std::exception &e)
	{
		out << e.what() << std::endl;
	}

	out << "int: ";
	try
	{
		int i = scalar.toInt();
		out << i << std::endl;
	}
	catch (const std::exception &e)
	{
		out << e.what() << std::endl;
	}

	out << "float: ";
	try
	{
		float f = scalar.toFloat();

		if (std::isnan(f) && std::signbit(f))
			out << "-";
		out << f;
		if (!std::isnan(f) && f - (int)f == 0)
			out << ".0";
		out << "f" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	out << "double: ";
	try
	{
		double d = scalar.toDouble();

		if (std::isnan(d) && std::signbit(d))
			out << "-";
		out << d;
		if (!std::isnan(d) && d - (int)d == 0)
			out << ".0";
		out << "f" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (out);
}
