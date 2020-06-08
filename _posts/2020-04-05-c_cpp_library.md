---
layout: single
title: c/c++ library on Linux
date : 2020-04-05 01:23:45 +0900
last_modified_at: 2020-06-08 18:05:37 +0900
categories: [c/c++]
tags: [programming, c/c++]
comments: true
public : true
---

# c shared library
## source code
### fourArithmeticOperation.h
```c
#ifndef __FOURARITHMETICOPERATION_
#define __FOURARITHMETICOPERATION_

int addition(int a, int b);
int subtraction(int a, int b);
int multiplication(int a, int b);
int division(int a, int b);

#endif
```
### fourArithmeticOperation.c
```c
#include "fourArithmeticOperation.h"

int addition(int a, int b)
{
	return a+b;
}

int subtraction(int a, int b)
{
	return a-b;
}

int multiplication(int a, int b)
{
	return a*b;
}

int division(int a, int b)
{
	return a/b;
}
```
## create shared library
```bash
$ gcc -Wall -fPIC -c fourArithmeticOperation.c
$ gcc -shared -o libfourArithmeticOperation.so.1 fourArithmeticOperation.o
$ ln -sf libfourArithmeticOperation.so.1 libfourArithmeticOperation.so
```
Here are options that is used when creating shared library.
 * -shared : Produce a shared object which can be linked with other objects to form an executable.
 * -fPIC: emit position-independent code, this is required when making a shared object
 * -fpic: almost same with fPIC, but it has GOT(global offset table) size limitation.
 * -Wl,options : Pass options to linker.(ex. -Wl,-soname,libfourArithmeticOperation.so.1  This passes "-soname=libfourArithmeticOperation.so.1" to linker. "-soname=name" set the internal DT_SONAME field to the specified name. When an executable is linked with a shared object which has a DT_SONAME field, then dynamic linker will attempt to load the shared object specified by the DT_SONAME field rather than the using the file name given to the linker.
 * For more options, refer to gcc manual.

# Executable file(linking at build time)
## source code
### main_shared.c
```c
#include <stdio.h>
#include <dlfcn.h>
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
```
## build executable file with "-l" option.
```bash
gcc -Wall -o main_shared main_shared.c -L. -lfourArithmeticOperation
```
Here are options that is used when linking library
 * -Ldir : search library specified by -l from "dir"  
   ex) -L. : search library from current directory(.)
 * -llibraryname : specify library name to link.  
   ex) -lfourArithmeticOperation : the library to be linked is "libfourArithmeticOperation.so"

## output
```bash
$ LD_LIBRARY_PATH=. ./main_shared
Input 2 numbers : 
3 2
add(3, 2) = 5
sub(3, 2) = 1
mul(3, 2) = 6
div(3, 2) = 1
```
<br/>   

# Executable file(loading library at runtime)
## source code
### main_load_runtime.c
```c
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

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
```

## build executable file
```bash
$ gcc -Wall -o main_load_runtime main_load_runtime.c -ldl
```
 * -ldl : need to specify libdl.so library to use dlopen(), dlsym() function.

## output
```bash
$ ./main_load_runtime 
Input 2 numbers : 
4
3
add(4, 3) = 7
sub(4, 3) = 1
mul(4, 3) = 12
div(4, 3) = 1
```

<br/>
# c static library
## source code
Let's use same fourArithmeticOperation.c/h file to create static library

## create static library
 ```bash
$ gcc -Wall -c fourArithmeticOperation.c
$ ar -cvr libfourArithmeticOperation.a fourArithmeticOperation.o
 ```
Here are options that is used when creating static library.
 * -c : Create the archive.
 * -v : requests the verbose version of an operation.
 * -r : Insert the files member... into archive (with replacement).

 * For more options, refer to gcc manual.

### main_static.c
```c
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

```
## create executable

```bash
$ gcc -o main_static main_static.c libfourArithmeticOperation.a
```
## output
```bash
$ ./main_static 
Input 2 numbers : 
2 3
add(2, 3) = 5
sub(2, 3) = -1
mul(2, 3) = 6
div(2, 3) = 0
```
<br/>
<br/>
# c++ shared library
## source code(used c++ class template)
### fourArithmeticOperation.h
```cpp
#ifndef __FOURARITHMETICOPERATION_
#define __FOURARITHMETICOPERATION_

template <typename T>
class fourArithmeticOperation {
	public :
		T addition(T a, T b);
		T subtraction(T a, T b);
		T multiplication(T a, T b);
		T division(T a, T b);
};

#endif
```

### fourArithmeticOperation.cpp
```cpp
#include "fourArithmeticOperation.h"

template class fourArithmeticOperation<float>;
template class fourArithmeticOperation<int>;

template <typename T>
T fourArithmeticOperation<T>::addition(T a, T b)
{
	return a+b+a+b;
}

template <typename T>
T fourArithmeticOperation<T>::subtraction(T a, T b)
{
	return a-b;
}

template <typename T>
T fourArithmeticOperation<T>::multiplication(T a, T b)
{
	return a*b;
}

template <typename T>
T fourArithmeticOperation<T>::division(T a, T b)
{
	return a/b;
}
```
## create shared library
```bash
$ g++ -Wall -fPIC -c fourArithmeticOperation.cpp
$ g++ -shared -o libfourArithmeticOperation.so.1 fourArithmeticOperation.o
$ ln -sf libfourArithmeticOperation.so.1 libfourArithmeticOperation.so
```

<br/>   
# Executable file(linking at build time)
## source code
### main_shared.c
```cpp
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
```

## build executable file with "-l" option.
```bash
g++ -Wall -o main_shared main_shared.cpp -L. -lfourArithmeticOperation
```
## output
```bash
$ LD_LIBRARY_PATH=. ./main_shared 
Input 2 numbers : 
3 -4
shared library : int operation
addition(3, -4) = -1
subtraction(3, -4) = 7
multiplication(3, -4) = -12
division(3, -4) = 0

shared library : float operation
addition(3, -4) = -1
subtraction(3, -4) = 7
multiplication(3, -4) = -12
division(3, -4) = -0.75
```

<br/>   
# Executable file(loading library at runtime)
In c++, shared library can be loaded at runtime by using dlopen(). By the way, one thing to note is that c++ supports function overloading. So, symbol in c++ is created with mangled name.(ex. in c, if function name is "addition", then symbol name is same with function("addition"), but in c++, several characters are added before and after the function name, so the symbol name is like "_ZN23additionIiE8"). To do call dlsym(), you need to know the symbol name of the function, but if it is created with a mangled name, you cannot know the symbol name exactly. To solve this, you need to create a symbol name in C type by using ***extern "C"*** in front of the function. In this case, you can't use c++'s overloading feature.(This doesn't mean that you can't use c++ in library code, you only need to have a C type symbol for symbols that are exposed outside. The internal library function can be implemented in c++).  
One more thing to say is that dlsym() is to obtain address of function symbol, not for class object. To load object and all its functions, we can do it by creating factory function which instantiates the class. 

## source code
### calc.h
```cpp
#ifndef __CALC_
#define __CALC_

class calc {
	public :
		float addition(float a, float b);
		float subtraction(float a, float b);
		float multiplication(float a, float b);
		float division(float a, float b);
};

#endif
```
### calc.cpp
```cpp
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
```

## create shared library
```bash
$ gcc -Wall -fPIC -c calc.cpp 
$ gcc -shared -o libcalc.so.1 calc.o
$ ln -sf libcalc.so.1 libcalc.so
```

### main_runtime.cpp
```cpp
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

```
## build executable file with "-l" option. 
```bash
g++ -Wall -o main_runtime main_runtime.cpp -L. -lcalc
```
If we implement class methods in header file, then no need to add "-L. -lcalc" option. Otherwise, it need to specify where the methods are implemented by using "-l" option.

## output
```bash
$ LD_LIBRARY_PATH=. ./main_runtime 
helloWorld. I'm calc library!
new instance in createFactory. 
Input 2 numbers : 
3 2
add(3, 2) = 5
sub(3, 2) = 1
mul(3, 2) = 6
div(3, 2) = 1.5
delete instance in destroyFactory. 
```
<br/>

# c++ static library
## source code
Let's use same fourArithmeticOperation.c/h file to create static library

## create static library
 ```bash
$ gcc -Wall -c fourArithmeticOperation.c
$ ar -cvr libfourArithmeticOperation.a fourArithmeticOperation.o
 ```

### main_static.c(same with main_shared.c)
```c
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
```
## build executable file(link static library) 
```bash
g++ -Wall -o main_static main_static.cpp libfourArithmeticOperation.a
```

## output
```bash
$ ./main_static 
Input 2 numbers : 
3 2
shared library : int operation
addition(3, 2) = 5
subtraction(3, 2) = 1
multiplication(3, 2) = 6
division(3, 2) = 1

shared library : float operation
addition(3, 2) = 5
subtraction(3, 2) = 1
multiplication(3, 2) = 6
division(3, 2) = 1.5
```
