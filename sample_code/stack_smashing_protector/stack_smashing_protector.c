/*
 * =====================================================================================
 *
 *       Filename:  stack_smashing_protector.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/26/20 01:17:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int testFunc1()
{
	int arr[5] = {0,};
	int i = sizeof(arr)/sizeof(arr[0]);

	for (int j = 0; j < i; j++) {
		arr[j] = j;
		printf("%s, %d\n", __func__, arr[j]);
	}

	return 0; 
}

int main(void)
{
	int i = 3;
	int arr[2] = {0,};
	int j = 4;
	
	printf("Input number: ");
	scanf("%d",  &i);
	for (j = 0; j < i; j++) {
		scanf("%d", &arr[j]);
		printf("%s, %d\n", __func__, arr[j]);
	}

	testFunc1();

	return 0;
}
