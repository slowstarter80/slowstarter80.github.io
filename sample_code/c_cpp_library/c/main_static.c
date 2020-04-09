#include <stdio.h>
#include <stdlib.h>
#include "fourArithmeticOperation.h"


int main(void)
{

	int a = 0, b = 0;;

	printf("Input 2 numbers : \n");
	scanf("%d", &a);
	getchar();
	scanf("%d", &b);
	getchar();

	printf("add(%d, %d) = %d\n", a, b, addition(a, b));
	printf("sub(%d, %d) = %d\n", a, b, subtraction(a, b));
	printf("mul(%d, %d) = %d\n", a, b, multiplication(a, b));
	printf("div(%d, %d) = %d\n", a, b, division(a, b));

	return 0;
}

