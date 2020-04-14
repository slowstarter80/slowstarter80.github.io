#include <iostream>
#include <dlfcn.h>
#include "calc.h"


typedef float(*arithmetic_t)(float, float);
typedef void (*hello_t)(void);
typedef calc* (*createFactory_t)(void);
typedef void (*destroyFactory_t)(calc *p);

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
	float a = 0, b = 0;;
	
	handle = dlopen("./libcalc.so", RTLD_LAZY);

	if (!handle) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	dlerror();    /* Clear any existing error */

	hello_t hello= (hello_t)dlsym(handle, "helloWorld");
	checkError();

	hello();

	createFactory_t createCalc = (createFactory_t)dlsym(handle, "createFactory");
	destroyFactory_t destroyCalc = (destroyFactory_t)dlsym(handle, "destroyFactory");

	if (!createCalc) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}
	if (!createCalc) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	calc *calculator = createCalc();

	std::cout<<"Input 2 numbers : "<<std::endl;
	std::cin>>a>>b;

	std::cout<<"add("<<a<<", "<<b<<") = "<<calculator->addition(a, b)<<std::endl;
	std::cout<<"sub("<<a<<", "<<b<<") = "<<calculator->subtraction(a, b)<<std::endl;
	std::cout<<"mul("<<a<<", "<<b<<") = "<<calculator->multiplication(a, b)<<std::endl;
	std::cout<<"div("<<a<<", "<<b<<") = "<<calculator->division(a, b)<<std::endl;

	destroyCalc(calculator);
	dlclose(handle);
	return 0;
}

