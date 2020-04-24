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
