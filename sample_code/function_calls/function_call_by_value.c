#include <stdio.h>

void swap_call_by_value(int num1, int num2);

int main(int argc, char *argv[])
{
	int num1 = 3;
	int num2 = 5;

	printf("[%s] : addresses : &num1 = %p, &num2 = %p\n\n", __func__, &num1, &num2);

	printf("[%s] : before calling swap_call_by_value() : num1 = %d, num2 = %d\n\n", __func__, num1, num2);
	swap_call_by_value(num1, num2);
	printf("[%s] : after calling swap_call_by_value() : num1 = %d, num2 = %d\n", __func__, num1, num2);

	return 0;
}

void swap_call_by_value(int num1, int num2)
{
	int tmp = num1;
	num1 = num2;
	num2 = tmp;
	printf("[%s] : addresses : &num1 = %p, &num2 = %p\n", __func__, &num1, &num2);
	printf("[%s] : num1 = %d, num2 = %d\n\n", __func__, num1, num2);
}

