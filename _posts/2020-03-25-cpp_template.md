---
layout: single
title: c++ template
date : 2020-03-25 23:59:59 +0900
last_modified_at: 2020-03-26 02:29:58 +0900
categories: [c/c++]
tags: [programming, c++]
comments: true
public : true
permalink : /wiki/cpp_template/
---

# c++ template
c++ template allows you to declare/implement a generic function/class that has a type parameter T instead of declaring/implementing all functions/classes that have the same function for each data type. And compiler generates functions/classs of corresponding type if necessary according to its actual code.
There are 2 kind of c++ template that one is function template and another is class template. When use template to function, it is a function template, and when use template to class, it is a class template. There is no conceptual difference.

## function template
### source code
 Either 'typename' or 'class' can be used in the angle bracksets. they are same meaning.  
ex) cpp_template_function.cpp
```cpp
#include <iostream>

using namespace std; 

template <typename T>
T add(T a1, T a2)
{
	return a1 + a2;
}

template <typename t1, typename t2>
t2 sub(t1 a1, t2 a2)
{
	return a1 - a2;
}

int main(void)
{
	cout<<"template int type add 1 + 2 = "<<add<int>(1, 2)<<endl;;
	cout<<"template float type add 1.0 + 2.0 = "<<add<float>(1.0, 2.0)<<endl;;
	cout<<"template float type sub 1.0 - 2.0 = "<<sub(1, 2.0)<<endl;;

	return 0;
}
``` 
### Output 
```bash
$ ./cpp_template_function
template int type add 1 + 2 = 3
template float type add 1.0 + 2.0 = 3
template float type sub 1.0 - 2.0 = -1
```
First output, type T is replaced with int.
Second output, type T is replaced with float.
Third output, type t1 is replaced with int, type t2 is replaced with float.
Angle brackets(<>) and data type between angle brackets can be omitted if the data type to replace type T is clear. For ex). there is no angle brackets at third output. But if you want to call a function which is of specific data type, you need to specify it explicitly. For ex). add<float>(1, 2) will call add function of float data type.


## class template
 In case of class template, the angle brackets and data type cannot be omitted.
### source code
ex) cpp_template_class.cpp
```cpp 
#include <iostream>

using namespace std; 

template <typename T>
class divide
{
	public :
		T result;

		divide(T a, T b) {
			result = a / b;
		}

		void showResult() {
			cout<<"result = "<<result<<endl;
		}
};


int main(void)
{
	divide<int> aClass(4,3);
	divide<float> bClass(4.0,3.0);

	aClass.showResult();
	bClass.showResult();

	return 0;
}
```
### Output 
```bash
$ ./cpp_template_class 
result = 1
result = 1.33333 
```
First output, it's division operation of int types, so the result is 1
Second output, it's division operation of float type, so the result is 1.33333


#template specialization
Basically, the code is generated with a function or class declared as a template, but it means that the template is not use for what you implemented for a specific type, but use the one you implemented.




# Side note.
If you use template, source code would be more simple because you don't need to declare/implement for each type, but this does not mean that actual executable file size is also smaller than declaring/implementing for each type. 

