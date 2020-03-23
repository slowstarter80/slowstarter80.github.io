---
layout: single
title: Local variable allocation order on stack
date : 2020-02-23 01:33:04 +0900
last_modified_at: 2020-03-23 22:46:16 +0900
categories: [c/c++]
tags: [programming, c/c++]
comments: true
public : true
permalink : /wiki/local_variable_allocation_order_on_stack/
---

이 글에서는 local variable이 stack에 할당될 때 어떤 순서로 할당되는지를 arm architecture에 대한 gcc/clang 각각의compiler로 생성한 결과물을 가지고 알아보겠습니다.
아래와 같이 여러개의 변수들을 선언하고 각 변수들의 주소값을 출력하도록 코드를 작성한 후, 각각의 compiler로 컴파일 하여 실행해 보겠습니다.
참고로 Stack이 쌓이는 방향은 ABI에 따라 다른데, 대부분의 경우는 높은 메모리 주소에서 낮은 메모리 주소 방향으로 쌓입니다.

# source code
```c
/* stack_order.c */
#include <stdio.h>

int main(void)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d[3] = {4, 5, 6};
	int e = 7;
	int f = 8;
	int g[3] = {9, 10, 11};

	printf("a = %d, address of a = %p\n", a, &a);
	printf("b = %d, address of b = %p\n", b, &b);
	printf("c = %d, address of c = %p\n", c, &c);
	printf("d[0] = %d, address of d[0] = %p\n", d[0], &d[0]);
	printf("d[1] = %d, address of d[1] = %p\n", d[1], &d[1]);
	printf("d[2] = %d, address of d[2] = %p\n", d[2], &d[2]);
	printf("e = %d, address of e = %p\n", e, &e);
	printf("f = %d, address of f = %p\n", f, &f);
	printf("g[0] = %d, address of g[0] = %p\n", g[0], &g[0]);
	printf("g[1] = %d, address of g[1] = %p\n", g[1], &g[1]);
	printf("g[2] = %d, address of g[2] = %p\n", g[2], &g[2]);

	return 0;
}
```
<br/>
# GCC
## Output
```bash
$ stack_order
a = 1, address of a = 0xfffee9e8
b = 2, address of b = 0xfffee9ec
c = 3, address of c = 0xfffee9f0
d[0] = 4, address of d[0] = 0xfffee9fc
d[1] = 5, address of d[1] = 0xfffeea00
d[2] = 6, address of d[2] = 0xfffeea04
e = 7, address of e = 0xfffee9f4
f = 8, address of f = 0xfffee9f8
g[0] = 9, address of g[0] = 0xfffeea08
g[1] = 10, address of g[1] = 0xfffeea0c
g[2] = 11, address of g[2] = 0xfffeea10
```
소스 코드와 출력 결과를 맞추어 보면, 먼저 선언된 변수가 stack에 늦게 할당되고, 늦게 선언된 변수가 stack에 먼저 할당된 것을 볼 수 있습니다.
예를 들어, 변수 a와 c를 비교해 봤을때, c가 a보다 더 높은 주소에 할당된 것을 알 수 있습니다.
그리고 변수들과 배열들의 순서에 대해서는, 배열이 stack에 먼저 할당되고, 변수가 배열보다 늦게 stack에 할당되어 있습니다.
예를 들어, d[], g[] 가 a,b,c,e,f 보다 높은 주소에 할당되었습니다.
그래서 stack에 할당된 순서를 높은 주소부터 낮은 주소로 나열해 보면, g[], d[], f, e, c, b, a 순입니다.
배열 내에서는 큰 index의 원소가 높은 주소에 할당되고, 작은 index의 원소가 낮은 주소에 할당된 것을 볼 수 있습니다.

## Assembly code

<br/>
# clang
## Output
```bash
a = 1, address of a = 0xfffeeac0
b = 2, address of b = 0xfffeeabc
c = 3, address of c = 0xfffeeab8
d[0] = 4, address of d[0] = 0xfffeeaac
d[1] = 5, address of d[1] = 0xfffeeab0
d[2] = 6, address of d[2] = 0xfffeeab4
e = 7, address of e = 0xfffeeaa8
f = 8, address of f = 0xfffeeaa4
g[0] = 9, address of g[0] = 0xfffeea98
g[1] = 10, address of g[1] = 0xfffeea9c
g[2] = 11, address of g[2] = 0xfffeeaa0
```
## Assembly code


