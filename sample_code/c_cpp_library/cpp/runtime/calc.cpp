#include "calc.h"
#include <iostream>

extern "C" {
	extern void helloWorld();
	extern calc* createFactory();
	extern void destroyFactory(calc *p);
}

float calc::addition(float a, float b)
{
	return a+b;
}

float calc::subtraction(float a, float b)
{
	return a-b;
}

float calc::multiplication(float a, float b)
{
	return a*b;
}

float calc::division(float a, float b)
{
	return a/b;
}

void helloWorld()
{
	std::cout<<"helloWorld. I'm calc library!"<<std::endl;
}

calc* createFactory()
{
	std::cout<<"new instance in createFactory. "<<std::endl;
	return new calc;
}

void destroyFactory(calc *p)
{
	std::cout<<"delete instance in destroyFactory. "<<std::endl;
	if ( p) {
		delete p;
		p = nullptr;
	}
}
