#include <iostream>
#include "fourArithmeticOperation.h"

int main(void)
{
	fourArithmeticOperation<int> int_obj;
	fourArithmeticOperation<float> float_obj;

	std::cout<<"Input 2 numbers : "<<std::endl;
	float a, b;

	std::cin>>a>>b;

	std::cout<<"shared library : int operation"<<std::endl;
	int int_operation_result = int_obj.addition(a, b);
	std::cout<<"addition("<<a<<", "<<b<<") = "<<int_operation_result<<std::endl;

	int_operation_result = int_obj.subtraction(a, b);
	std::cout<<"subtraction("<<a<<", "<<b<<") = "<<int_operation_result<<std::endl;

	int_operation_result = int_obj.multiplication(a, b);
	std::cout<<"multiplication("<<a<<", "<<b<<") = "<<int_operation_result<<std::endl;

	int_operation_result = int_obj.division(a, b);
	std::cout<<"division("<<a<<", "<<b<<") = "<<int_operation_result<<std::endl;


	std::cout<<std::endl;
	std::cout<<"shared library : float operation"<<std::endl;
	float float_operation_result = float_obj.addition(a, b);
	std::cout<<"addition("<<a<<", "<<b<<") = "<<float_operation_result<<std::endl;

	float_operation_result = float_obj.subtraction(a, b);
	std::cout<<"subtraction("<<a<<", "<<b<<") = "<<float_operation_result<<std::endl;

	float_operation_result = float_obj.multiplication(a, b);
	std::cout<<"multiplication("<<a<<", "<<b<<") = "<<float_operation_result<<std::endl;

	float_operation_result = float_obj.division(a, b);
	std::cout<<"division("<<a<<", "<<b<<") = "<<float_operation_result<<std::endl;

	return 0;
}
