---
layout: single
title: function call trace in c program
date : 2020-04-24 01:23:45 +0900
last_modified_at: 2020-04-25 03:20:41 +0900
categories: [c/c++]
tags: [programming, c/c++]
comments: true
public : true
permalink : /wiki/function_call_trace_in_c_program/
---

# backtrace functions in c source code
 When we debugging, we sometimes need to figure out how the function was called. Here, I will describe the c functions that can trace back the function call.
 In a function that requires traceback, it finds the return addresses of the functions by calling backtrace() and backtrace_symbols(), and after that, print them out with a printf statement.

## source code
### backtrace.c
```c
#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>

#define BUF_SIZE (100)

void func3()
{
	int i, num_of_addrs;
	void *buff[BUF_SIZE];
	char **symbol_str;

	num_of_addrs = backtrace(buff, BUF_SIZE);
	printf("backtrace() returned : %d \n", num_of_addrs);

	symbol_str = backtrace_symbols(buff, num_of_addrs);
	if (symbol_str == NULL) {
		printf("backtrace_symbols returned NULL");
		return;
	}

	for (i = 0; i < num_of_addrs; i++)
		printf("%s\n", symbol_str[i]);

	free(symbol_str);
}

void func2()
{
	func3();
}

void func1()
{
	func2();
}

int main(void)
{
	printf("main enter\n");
	func1();
	printf("main exit\n");
}
```
Functions are called as following order.

 - main() -> func1() -> func2() -> func3() -> backtrace(), backtrace_symbols()

backtrace() returns the number of addresses returned in buff. Each return address from the corresponding stack frame is saved in buff array.
backtrace_symbols() translates the addresses into an array of strings that describe the addresses symbolically.

## build
```bash
 $ gcc -o backtrace backtrace.c -rdynamic -g
```
 - -rdynamic : Pass the flag "-export-dynamic" to the ELF linker. This is needed to allow obtaining backtraces from within a program.
 - -g : Produce debugging information in the operating system's native format. This is needed when using "addr2line" to convert addresses into  correcponding source code line number.


## output
```bash
$ ./backtrace 
main enter
backtrace() returned : 6 
./backtrace(func3+0x2e) [0x5655555541b3]
./backtrace(func2+0xe) [0x565555554286]
./backtrace(func1+0xe) [0x565555554297]
./backtrace(main+0x1a) [0x5655555542b4]
/lib64/libc.so.6(__libc_start_main+0xeb) [0x7efbff4ffe0b]
./backtrace(_start+0x2a) [0x5655555540ca]
main exit
$
```
In this example, There are 6 elements in buff array. The result shows return address of each stack frame.  
ex) func2+0xe == 0x1286 == return address of func3() stack frame.
```bash
$ objdump -D backtrace > backtrace.lst
```
And open backtrace.lst file in text editor.
```c
0000000000001278 <func2>:
    1278:	55                   	push   %rbp
    1279:	48 89 e5             	mov    %rsp,%rbp
    127c:	b8 00 00 00 00       	mov    $0x0,%eax
    1281:	e8 ff fe ff ff       	callq  1185 <func3>
    1286:	90                   	nop                             
    1287:	5d                   	pop    %rbp
    1288:	c3                   	retq   
```


# addr2line
convert addresses into file names and line numbers.
Here is an example to convert symbol addres((func2+0xe) and (func3+0x2e)) into source code line number.
Check if the result matches the above source code.


```bash
$ nm backtrace | grep -ni func2
14:0000000000001278 T func2

$ addr2line -a -f -e backtrace 0x1286                          //0x1286 == (func2+0xe)
0x0000000000001286
func2
/home/chuljeon39a/src/backtrace/backtrace.c:31

$ nm backtrace | grep -ni func3
15:0000000000001185 T func3

$ addr2line -a -f -e backtrace 0x11a3                          //0x11a3 == (func3+0x2e)
0x00000000000011a3
func3
/home/chuljeon39a/src/backtrace/backtrace.c:13
```

# cflow
It generates a C-language flowgraph. Refer to cflow man page.
```bash
$ cflow backtrace.c 
main() <int main (void) at backtrace.c:38>:
    printf()
    func1() <void func1 () at backtrace.c:33>:
        func2() <void func2 () at backtrace.c:28>:
            func3() <void func3 () at backtrace.c:7>:
                backtrace()
                printf()
                backtrace_symbols()
                free()
$
```


