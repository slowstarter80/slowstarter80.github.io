#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "fourArithmeticOperation.h"

typedef int (*arithmetic_t)(int, int);

void checkError()
{
	char *error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
}


int main(void)
{
	void *handle;
	int a = 0, b = 0;;
	
	handle = dlopen("./libfourArithmeticOperation.so", RTLD_LAZY);

	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();    /* Clear any existing error */

	arithmetic_t add = (arithmetic_t)dlsym(handle, "addition");
	checkError();

	arithmetic_t sub = (arithmetic_t)dlsym(handle, "subtraction");
	checkError();

	arithmetic_t mul = (arithmetic_t)dlsym(handle, "multiplication");
	checkError();

	arithmetic_t div = (arithmetic_t)dlsym(handle, "division");
	checkError();

	printf("Input 2 numbers : \n");
	scanf("%d", &a);
	getchar();
	scanf("%d", &b);
	getchar();

	printf("add(%d, %d) = %d\n", a, b, add(a, b));
	printf("sub(%d, %d) = %d\n", a, b, sub(a, b));
	printf("mul(%d, %d) = %d\n", a, b, mul(a, b));
	printf("div(%d, %d) = %d\n", a, b, div(a, b));

	dlclose(handle);
	return 0;
}

