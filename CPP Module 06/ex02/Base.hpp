#ifndef BASE_HPP
#define BASE_HPP
#include <string>
#include <iostream>
#include <ctime>

class Base {
	private:
	public:
		Base(){};
		Base(Base const &other)
		{
			*this = other;
		};
		Base &operator=(Base const &other)
		{
			if(this != &other)
				std::cout << "other" << std::endl;
			return (*this);
		};
		
		virtual ~Base(){};
		void identify_from_pointer(Base *p);
		void identify_from_reference(Base *p);
};

Base* generate(void);
void identify(Base *);

class A : public Base {
	private:
	public:
};

class B : public Base {
	private:
	public:
};

class C : public Base {
	private:
	public:
};

#endif
