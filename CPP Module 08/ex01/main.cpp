
#include "span.hpp"

int main(void)
{
	srand(time(NULL));
	try
	{
		Span sp = Span(10000);
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				sp.addNumber(rand());
			}
		}
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}
