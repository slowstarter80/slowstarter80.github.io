/*
 * =====================================================================================
 *
 *       Filename:  stack_orer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/02/20 00:55:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

void printFunc(int a, int b, int c, int d, int e, int f)
{
	printf("\n%s\n", __func__);
	printf("a = %d, address of a = %p\n", a, &a);
	printf("b = %d, address of b = %p\n", b, &b);
	printf("c = %d, address of c = %p\n", c, &c);
	printf("d = %d, address of d = %p\n", d, &d);
	printf("e = %d, address of e = %p\n", e, &e);
	printf("f = %d, address of f = %p\n", f, &f); 
}

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
