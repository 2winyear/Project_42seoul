#include "mutantstack.cpp"

int main(void)
{
	MutantStack<int> mstack;
	mstack.push(9);
	mstack.push(7);
	std::cout << "top : " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "size : " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();

	while (it != mstack.end())
	{
		std::cout << "m stack : " << *it << std::endl;
		++it;
	}
	return 0;
}
