#include <stdio.h>

int testFunc1()
{
	int i = 3;
	int buf[2] = {0,};
	int j = 4;

	printf("Input number: ");
	scanf("%d",  &i);

	for (j = 0; j < i; j++) {
		buf[j] = j;
		printf("%s, %d\n", __func__, buf[j]);
	}

	return 0;
}
int main(void)
{
	testFunc1();

	return 0;
}
