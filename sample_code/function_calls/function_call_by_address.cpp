#include <iostream>

using namespace std;

void swap_call_by_address(int *num1, int *num2);

int main(int argc, char *argv[])
{
	int num1 = 3;
	int num2 = 5;

	cout << "[" <<__func__<< "] : addresses : &num1 = "<< &num1 << ", &num2 = " << &num2 <<"\n\n";

	cout << "[" << __func__ << "] : before calling swap_call_by_address() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";
	swap_call_by_address(&num1, &num2);
	cout << "[" << __func__ << "] : after calling swap_call_by_address() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";

	return 0;
}

void swap_call_by_address(int *num1, int *num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
	cout << "[" << __func__ << "] : address : num1 = " << num1 <<", num2 = " << num2 << "\n";
	cout << "[" << __func__ << "] : *num1 = " << *num1 <<", *num2 = " << *num2 << "\n\n";
}

