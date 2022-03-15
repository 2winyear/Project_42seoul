#ifndef DATA_HPP
#define DATA_HPP
#include <string>
#include <iostream>

typedef struct 
{
	int age;
	std::string name;
}Data;

uintptr_t serialize(Data *ptr);
Data* deserialize(uintptr_t raw);

#endif
