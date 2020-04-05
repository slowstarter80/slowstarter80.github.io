#include <iostream>
#include "fourArithmeticOperation.h"
#include "fourArithmeticOperation.cpp"

int main(void)
{
	fourArithmeticOperation<float> object;

	int a = object.addition(1,2);
	std::cout<<a<<std::endl;

	a = object.subtraction(1,2);
	std::cout<<a<<std::endl;

	a = object.multiplication(1,2);
	std::cout<<a<<std::endl;

	a = object.division(1,2);
	std::cout<<a<<std::endl;


	return 0;


}
