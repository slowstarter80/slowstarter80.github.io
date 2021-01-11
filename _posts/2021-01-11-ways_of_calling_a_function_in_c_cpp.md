---
layout: single
title: Ways of calling a function in c/c++ programming
date : 2021-01-11 00:23:45 +0900
last_modified_at: 2021-01-12 02:40:24 +0900
categories: [c/c++]
tags: [programming,c/c++]
comments: true
public : true
---

# c
 In c programming, functions can be invoked in two ways, one is **call by value** and the other is **call by reference**.
Actual parameters are the variables, constants, or expressions used in the actual routine calls, whereas formal parameters are the variables declared in a routine definition. parameters passed to function, and formal parameters are the parameters received by function.

## call by value
 Values of actual parameters are copied to function's formal parameters, and actual parameters and formal parameters are stored in different memory addresses. Thus, changing the values of formal parameters within the function definition does not change the value of actual parameters. 
### example of call by value
```c
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
```
### execution
```bash
$ ./function_call_by_value 
[main] : addresses : &num1 = 0x7fffdeecbf40, &num2 = 0x7fffdeecbf44

[main] : before calling swap_call_by_value() : num1 = 3, num2 = 5

[swap_call_by_value] : addresses : &num1 = 0x7fffdeecbf0c, &num2 = 0x7fffdeecbf08
[swap_call_by_value] : num1 = 5, num2 = 3

[main] : after calling swap_call_by_value() : num1 = 3, num2 = 5
$ 
```
 As shown in the results above, the values of num1, num2 changed in the swap_call_by_value() function were not reflected in num1 and num2 of the main() function. And the addresses of num1 and num2 in main() function and the addresses of num1 and num2 in the swap_call_by_value() function are different.

## call by reference
 This method copies the addresses of variables in calling function to the formal parameters of the function definition. Then, since the formal parameters have the addresses of actual variables of calling function, the values stored in the addresses can be changed in callee function, and this changed values are reflected in the actual variables of the calling function. This is because it directly changes the values of the addresses.

### example of call by reference
```c
#include <stdio.h>

void swap_call_by_reference(int *num1, int *num2);

int main(int argc, char *argv[])
{
	int num1 = 3;
	int num2 = 5;

	printf("[%s] : addresses : &num1 = %p, &num2 = %p\n\n", __func__, &num1, &num2);

	printf("[%s] : before calling swap_call_by_reference() : num1 = %d, num2 = %d\n", __func__, num1, num2);
	swap_call_by_reference(&num1, &num2);
	printf("[%s] : after calling swap_call_by_reference() : num1 = %d, num2 = %d\n", __func__, num1, num2);

	return 0;
}

void swap_call_by_reference(int *num1, int *num2)
{
	int tmp = *num1;
	*num1 = *num2;
	*num2 = tmp;
	printf("[%s] : addresses : num1 = %p, num2 = %p\n", __func__, num1, num2);
	printf("[%s] : *num1 = %d, *num2 = %d\n", __func__, *num1, *num2);
}
```

### execution
```bash
$ ./function_call_by_reference 
[main] : addresses : &num1 = 0x7ffcec31cd30, &num2 = 0x7ffcec31cd34

[main] : before calling swap_call_by_reference() : num1 = 3, num2 = 5
[swap_call_by_reference] : addresses : num1 = 0x7ffcec31cd30, num2 = 0x7ffcec31cd34
[swap_call_by_reference] : *num1 = 5, *num2 = 3
[main] : after calling swap_call_by_reference() : num1 = 5, num2 = 3
```

 
<br/>
<br/>
# c++
 In c++ programming, functions can be invoked in ways: **call by value**, **call by reference** and **call by address**
 
## call by value
 Values of actual parameters are copied to function's formal parameters, and actual parameters and formal parameters are stored in different memory addresses. Thus, changing the values of formal parameters within the function definition does not change the value of actual parameters. This is same as c's "call by value".
### c++ example

```c++
#include <iostream>

using namespace std;

void swap_call_by_value(int num1, int num2);

int main(int argc, char *argv[])
{
	int num1 = 3;
	int num2 = 5;

	cout << "[" <<__func__<< "] : addresses : &num1 = "<< &num1 << ", &num2 = " << &num2 <<"\n\n";

	cout << "[" << __func__ << "] : before calling swap_call_by_value() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";
	swap_call_by_value(num1, num2);
	cout << "[" << __func__ << "] : after calling swap_call_by_value() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";

	return 0;
}

void swap_call_by_value(int num1, int num2)
{
	int tmp = num1;
	num1 = num2;
	num2 = tmp;
	cout << "[" << __func__ << "] : address : &num1 = " << &num1 <<", &num2 = " << &num2 << "\n";
	cout << "[" << __func__ << "] : num1 = " << num1 <<", num2 = " << num2 << "\n\n";
}
```
### execution
```bash
$ ./function_call_by_value 
[main] : addresses : &num1 = 0x7fff9859ec60, &num2 = 0x7fff9859ec64

[main] : before calling swap_call_by_value() : num1 = 3, num2 = 5

[swap_call_by_value] : address : &num1 = 0x7fff9859ec2c, &num2 = 0x7fff9859ec28
[swap_call_by_value] : num1 = 5, num2 = 3

[main] : after calling swap_call_by_value() : num1 = 3, num2 = 5
```
 As shown in the result above, the changes of swap_call_by_value() are not affected the variables of main(). The addresses of num1 and num2 of main() and the addresses of num1 and num2 of swap_call_by_value() are different.

## call by reference
 This method copies the references of an actual parameters into the formal parameters. The references are used to access the actual parameters, so the changes made in callee function affect the values of actual variables.

### c++ example
```c++
#include <iostream>

using namespace std;

void swap_call_by_reference(int &num1, int &num2);

int main(int argc, char *argv[])
{
	int num1 = 3;
	int num2 = 5;

	cout << "[" <<__func__<< "] : addresses : &num1 = "<< &num1 << ", &num2 = " << &num2 <<"\n\n";

	cout << "[" << __func__ << "] : before calling swap_call_by_reference() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";
	swap_call_by_reference(num1, num2);
	cout << "[" << __func__ << "] : after calling swap_call_by_reference() : num1 = " << num1 << ", num2 = " << num2 << "\n\n";

	return 0;
}

void swap_call_by_reference(int &num1, int &num2)
{
	int tmp = num1;
	num1 = num2;
	num2 = tmp;
	cout << "[" << __func__ << "] : address : &num1 = " << &num1 <<", &num2 = " << &num2 << "\n";
	cout << "[" << __func__ << "] : num1 = " << num1 <<", num2 = " << num2 << "\n\n";
}
```
### execution
```bash
$ ./function_call_by_reference 
[main] : addresses : &num1 = 0x7fff0a32ce60, &num2 = 0x7fff0a32ce64

[main] : before calling swap_call_by_reference() : num1 = 3, num2 = 5

[swap_call_by_reference] : address : &num1 = 0x7fff0a32ce60, &num2 = 0x7fff0a32ce64
[swap_call_by_reference] : num1 = 5, num2 = 3

[main] : after calling swap_call_by_reference() : num1 = 5, num2 = 3
$ 
```
 As shown in the result above, the changes in swap_call_by_reference() are reflected in the variables of main() function. The addresses of num1 and num2 of main() and the addresses of num1 and num2 of swap_call_by_reference() are same.

## call by address
 This method copies the address of actual variables into the formal parameters. Thus in callee function, the address is used to access the actual variables of caller function. This means the changes made in callee function affect the values of actual variable.
 
### c++ example
```c++
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
```
### execution
```bash
$ ./function_call_by_address 
[main] : addresses : &num1 = 0x7fff15e6b5e0, &num2 = 0x7fff15e6b5e4

[main] : before calling swap_call_by_address() : num1 = 3, num2 = 5

[swap_call_by_address] : address : num1 = 0x7fff15e6b5e0, num2 = 0x7fff15e6b5e4
[swap_call_by_address] : *num1 = 5, *num2 = 3

[main] : after calling swap_call_by_address() : num1 = 5, num2 = 3
$ 
```
 As shown in the result above, the changes in swap_call_by_reference() are reflected in the variables of main() function.
