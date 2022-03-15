#include "Data.hpp"

int main()
{
	Data seungyel;

	seungyel.name = "seungyel";
	seungyel.age = 23;

	uintptr_t out = serialize(&seungyel);

	Data *data = deserialize(out);

	std::cout << "Name: " << data->name << std::endl;
	std::cout << "Age: " << data->age << std::endl;
}
