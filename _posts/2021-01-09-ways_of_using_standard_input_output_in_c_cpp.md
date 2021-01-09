---
layout: single
title: Ways of using standard input/output in C
date : 2021-01-09 00:23:45 +0900
last_modified_at: 2021-01-10 02:56:01 +0900
categories: [c/c++]
tags: [programming,c/c++]
comments: true
public : true
---

# c
## c code
 This is a C program that inputs one string and two numbers, and outputs the input string and numbers.
 
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
	int a, b;
	char buf[30] = {0,};

	printf("Input string : ");
	scanf("%30s", buf);

	printf("Input 2 numbers : ");
	scanf("%d%d", &a, &b);

	printf("The input string is %s\n", buf);
	printf("The input nubmers are %d and %d\n", a, b);

	return 0;
}
```
### Test case 1
```bash
$ ./c_example 
Input string : c_input
Input 2 numbers : 1 2
The input string is c_input
The input nubmers are 1 and 2
$ 
```
### Test case 2
 In this test case, enters a string("c input") containing white space and 2 numbers.
```bash
$ ./c_example 
Input string :  c input
Input 2 numbers : The input string is c
The input nubmers are 1669055165 and 22007
$ 
```
 It is weird that it didn't take two numbers, and prints two strange numbers, then exits.
### Test case 3
 In this test case, enters a string("c 1") containing white space and 2 numbers.
```bash
$ ./c_example 
Input string : c 1  
Input 2 numbers : 2 3
The input string is c
The input nubmers are 1 and 2
$ 
```
 It is also weird, but it seems to be different from "Test case 2". In this case, the inputs were entered as pushed one by one.


 The results of "Test case 2" and "Test case 3" are that when scanf get a string input using "%s", the  input ends when it encounters a white-space character such as space, tab, newline.\
 <br/>
 So in "Test case 2", only "c" is stored in "buf", and " input" is still in the buffer of stdin, then scanf("%d%d", &a, &b); is executed. In this case, scanf removes the white-space characters from stdin's buffer until non-white-space character appears. Next, since scanf uses "%d%d" to get 2 numbers, there must be numbers in the stdin's buffer. But what was in the buffer were characters(here is "input"), not numbers. So scanf exits without taking any number inputs.\
 <br/>
 In "Test case 3", only "c" is stored in "buf", and " 1" is still in the buffer of stdin. then scanf("%d%d", &a, &b); is executed, In this case, as explained above, scanf removed the white-space characters from stdin's buffer until non-white-space character sppears. Next, what was in the buffer is a number(here is 1). Since scanf used "%d%d" to get two numbers, "1" is taken by first "%d", and "2" is taken by second "%d". The last number entered "3" is still in the buffer, but there are  no more scanf calls. 
 
 
## The ways to input a string containing white space characters in c.
 There are some ways to input a string containing space characters.
### using scanf("%[^\n]s", buf);
 This reads string until it encounters a '\n'(new line), so spaces get saved as well.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
	int a, b;
	char buf[30] = {0,};

	printf("Input string : ");
	scanf("%30[^\n]s", buf);
	while ((c = fgetc(stdin)) != '\n' && c != EOF); /* Flush stdin */

	printf("Input 2 numbers : ");
	scanf("%d%d", &a, &b);

	printf("The input string is %s\n", buf);
	printf("The input nubmers are %d and %d\n", a, b);

	return 0;
}
```
#### Test case
```bash
$ ./c_example 
Input string : I am a student.
Input 2 numbers : 1 2
The input string is I am a student.
The input nubmers are 1 and 2
$ 
```

### using fgets(char *s, int size, FILE *stream);
 This reads in at most one less than size characters from stream and stores them into the buffer pointedto by s.
 Reading stops after an EOF or a newline. If a newline is read, it is stored into the buffer.
 fgets() is safer than gets() because fgets() is able to set the size of buffer pointed to by s, while gets() cannot set the size of buffer.
```c
#include <stdio.h>

int main(int argc, char *argv[])
{
	int a, b;
	char buf[30] = {0,};

	printf("Input string : ");
	fgets(buf, 30, stdin);

	printf("Input 2 numbers : ");
	scanf("%d%d", &a, &b);

	printf("The input string is %s\n", buf);
	printf("The input nubmers are %d and %d\n", a, b);

	return 0;
}
```
#### Test case
 There is a line break after "buf" is printed, because fgets() reads '\n' as well.
```bash
$ ./c_example 
Input string : I am a student
Input 2 numbers : 1 2
The input string is I am a student

The input nubmers are 1 and 2
$ 
```

### using getline(char **lineptr, size_t *n, FILE *stream);
 In the example below, buf is NULL and n is 0, then getline() will allocate a buffer for storing the line, This buffer should be freed by the user program even if getline() failed.
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a, b;
	size_t n = 0;
	char *buf = NULL;

	printf("Input string : ");
	getline(&buf, &n, stdin);

	printf("Input 2 numbers : ");
	scanf("%d%d", &a, &b);

	printf("The input string is %s\n", buf);
	printf("The input nubmers are %d and %d\n", a, b);

	free(buf);

	return 0;
}
```
#### Test case
 There is a line break after "buf" is printed, because the buffer of getline() includes the '\n' as well.
```bash
$ ./c_example 
Input string : I am a student
Input 2 numbers : 1 2
The input string is I am a student

The input nubmers are 1 and 2
$ 
```



<br />





# c++
## c++ code
 This is a c++ program that inputs one string and two numbers, and outputs the input string and numbers.
 
```c++
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int a, b;
	char buf[30] = {0,};

	cout << "Input string : ";
	cin >> buf;

	cout << "Input 2 numbers : ";
	cin >> a >> b;

	cout << "The input string is "<<buf<<"\n";
	cout << "The input nubmers are " << a << " and " << b <<"\n";

	return 0;
}
```
## Test case 1
```bash
$ ./cpp_example 
Input string : cpp_input
Input 2 numbers : 1 2
The input string is cpp_input
The input nubmers are 1 and 2
$ 
```
## Test case 2
```bash
$ ./cpp_example 
Input string : cpp input
Input 2 numbers : The input string is cpp
The input nubmers are 0 and 22079
$ 
```
 It is weird that it didn't take two numbers, and prints two strange numbers, then exits. It's same as c example case.
## Test case 3
 In this test case, enters a string("c 1") containing white space and 2 numbers.
```bash
$ ./cpp_example 
Input string : cpp 1
Input 2 numbers : 2 3
The input string is cpp
The input nubmers are 1 and 2
$ 
```
 It is also weird, but it seems to be different from "Test case 2". In this case, the inputs were entered as pushed one by one. It's same as c example case.


## The ways to input a string containing white space characters in c++.
 There are some ways to input a string containing space characters.
### using std::getline(istream& is, string& str);
```c++
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int a, b;
	string buf;

	cout << "Input string : ";
	getline(cin, buf);

	cout << "Input 2 numbers : ";
	cin >> a >> b;

	cout << "The input string is "<<buf<<"\n";
	cout << "The input nubmers are " << a << " and " << b <<"\n";

	return 0;
}
```
#### Test case
```bash
$ ./cpp_example 
Input string : This is a c++ example which inputs string containing white spaces.
Input 2 numbers : 1 2
The input string is This is a c++ example which inputs string containing white spaces.
The input nubmers are 1 and 2
$ 
```

### using std::istream::getline(char *s, streamsize n);
```c++
#include <iostream>
#include <ios>
#include <limits>
using namespace std;

int main(int argc, char *argv[])
{
	int a, b;
	char c;
	char buf[30] = {0,};

	cout << "Input string : ";
	cin.getline(buf, sizeof(buf));
	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	cout << "Input 2 numbers : ";
	cin >> a >> b;

	cout << "The input string is "<<buf<<"\n";
	cout << "The input nubmers are " << a << " and " << b <<"\n";

	return 0;
}
```
#### Test case
```bash
$ ./cpp_example 
Input string : ds jf dsjl fdsjl fsdl fsdljk fsdlj fjsldj fjsdl fsdlj fdsjl
Input 2 numbers : 1 2
The input string is ds jf dsjl fdsjl fsdl fsdljk 
The input nubmers are 1 and 2
$ 
```
