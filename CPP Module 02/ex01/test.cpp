#include <stdio.h>
#include <iostream>

class Fruit {
	public:
		virtual void peel(){printf("peeling a base class fruit\n");}; 
		void make_candy_apple(float weight);
	private:
		int weight, calories_per_oz;
};

class Apple : public Fruit {
	public:
		void peel() {printf("peeling an apple\n");};
		void bob_for(int tub_id, int number_of_attempts);
};

int main()
{
	Apple apple;
	Fruit orange;
	Fruit *p;
	
	p = &apple;
	p->peel();

	p= &orange;
	p->peel();
}