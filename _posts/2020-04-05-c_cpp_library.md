---
layout: single
title: c/c++ library on Linux
date : 2020-04-05 01:23:45 +0900
last_modified_at: 2020-04-10 02:06:38 +0900
categories: [c/c++]
tags: [programming, c/c++]
comments: true
public : true
permalink : /wiki/c_cpp_library/
---

# c shared library(dynamic library)

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
### main.c
```c
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
```
## create shared library
```bash
$ gcc -Wall -fPIC -c *.c
$ gcc -shared -o libfourArithmeticOperation.so.1 *.o
$ ln -sf libfourArithmeticOperation.so.1 libfourArithmeticOperation.so
```
Here are options that is used when creating shared library.
 * -shared : Produce a shared object which can be linked with other objects to form an executable.
 * -fPIC: emit position-independent code, this is required when making a shared object
 * -fpic: almost same with fPIC, but it has GOT(global offset table) size limitation.
 * -Wl,options : Pass options to linker.(ex. -Wl,-soname,libfourArithmeticOperation.so.1  This passes "-soname=libfourArithmeticOperation.so.1" to linker. "-soname=name" set the internal DT_SONAME field to the specified name. When an executable is linked with a shared object which has a DT_SONAME field, then dynamic linker will attempt to load the shared object specified by the DT_SONAME field rather than the using the file name given to the linker.
 * For more options, refer to gcc manual.

## create executable
```bash
$ gcc -Wall -o main -L. -lfourArithmeticOperation -ldl main.c
```
## output
```bash
$ LD_LIBRARY_PATH=. ./main 
Input 2 numbers : 
3 2
add(3, 2) = 5
sub(3, 2) = 1
mul(3, 2) = 6
div(3, 2) = 1
```
<br/>   
# c static library
## source code
Let's use same fourArithmeticOperation.c/h file to create static library
For executable file, need to change source code because dlopen() and dlsym() are not necessary.
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

<!--
# Using shared library in c++
c++에서도 dlopen()과 dlsym()을 이용하여 shared library를 사용할 수 있습니다. 그런데, 한가지 주목해야 할 점은 c++은 함수 overloading을 지원한다는 점입니다. 그래서 c++의 symbol 은 mangled name으로 생성이 됩니다.
dlsym()을 하려면, 함수의 symble name을 알아야 하는데, mangled name으로 생성된 경우, symbol name을 정확히 알 수 없습니다. 
-->
