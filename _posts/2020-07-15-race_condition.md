---
layout: single
title: Race condition
date : 2020-07-15 00:23:45 +0900
last_modified_at: 2020-07-17 02:29:18 +0900
categories: [c/c++]
tags: [programming,c/c++]
comments: true
public : true
---

 A race condition occurs when two or more threads access a shared resource(such a file or variable) at the same time. In this case, each thread races to read and to write shared resource simultaneously. When each thread read variable at the same time, those threads will read the same value and perform their operations on the value. And when those threads write the computed value to the shared variable, the last value written overwrites the previously written value. The race condition may or may not occur depending on the timing of each thread access the shared variable, so you should be careful.

# example code
## C code
 Here is example code to increment the value of count variable by 1. If 2 threads call the inc() function, the value of count can be 2 or 1. In C-language code, it is a single statement that increases the value by 1. 

```c
static count = 0;
void inc()
{
	count++;
}
```
## Assembly code(arm aarch32 code for example)
 But in Assembly code, it consists of several statements that read, increment, and store the value.
 So, if 2 threads call the inc() function at the same time, when reading count value, 2 thread may read 0, increase 1 each, and store 1 each, so 1 may be stored. Or even if a thread is executed first, several statements(read, increment, and store count values) may not work atomically, so there is no guarantee that the final value is 2. For example, an interrupt occurs during execution of those statements.

```c
...
inc:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0


	ldr	r3, .L2                @ load count's address
	ldr	r3, [r3]               @ load value of count to r3
	add	r3, r3, #1             @ increment r3 by 1
	ldr	r2, .L2                @ load count's address
	str	r3, [r2]               @ store r3 to count's address


	nop
	add	sp, fp, #0
	@ sp needed
	ldr	fp, [sp], #4
	bx	lr
.L3:
	.align	2
.L2:
	.word	count
```

# race condition example in C, and how to avoid race condition by using mutex
## pthread.c
```c
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define THREAD_COUNT (2)
static int count = 0;

static void *thread_function(void *arg)
{
	int i = 0;
	char *thread_name = arg;
	for (i = 0; i < 1000000; i++) {
		count++;
		printf("%s i = %d, count = %d\n", thread_name, i, count);
	}
	sleep(2);
	printf("\n");
	printf("%s i = %d, count = %d\n", thread_name, i, count);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t thread_id[THREAD_COUNT];
	char thread_name[THREAD_COUNT][20];
	int ret = 0;
	char buf[20] = {0,};

	for (int i = 0; i < THREAD_COUNT; i++) {
		snprintf(buf, 9, "thread_%d", i);
		memcpy(thread_name[i], buf, sizeof(buf));
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		ret = pthread_create(&thread_id[i], NULL, &thread_function, thread_name[i]);
		if (ret != 0) {
			printf("pthread_create thread_id[%d] failed!!!\n", i);
		}
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		ret = pthread_join(thread_id[i], NULL);
		if (ret != 0) {
			printf("pthread_join thread_id[%d] failed!!!\n", i);
		}
	}

	return 0;
}
```
## output
```bash
...
thread_1 i = 999998, count = 1999987
thread_1 i = 999999, count = 1999988

thread_0 i = 1000000, count = 1999988

thread_1 i = 1000000, count = 1999988
```
 In above example, there are 2 threads that call thread_function(), and thread_function() has a for loop that executes count++ 1000000 times.
 Therefor, the final value of count should be 2000000, but the actual result is 1999988, which is less than 2000000. 

## pthread_mutex.c
 In this example code, pthread_mutex_lock() and pthread_mutex_unlock() are used to avoid race condition.
```c
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define THREAD_COUNT (2)
static int count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void *thread_function(void *arg)
{
	int i = 0;
	char *thread_name = arg;
	for (i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
		printf("%s i = %d, count = %d\n", thread_name, i, count);
	}
	sleep(2);
	printf("\n");
	printf("%s i = %d, count = %d\n", thread_name, i, count);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t thread_id[THREAD_COUNT];
	char thread_name[THREAD_COUNT][20];
	int ret = 0;
	char buf[20] = {0,};

	for (int i = 0; i < THREAD_COUNT; i++) {
		snprintf(buf, 9, "thread_%d", i);
		memcpy(thread_name[i], buf, sizeof(buf));
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		ret = pthread_create(&thread_id[i], NULL, &thread_function, thread_name[i]);
		if (ret != 0) {
			printf("pthread_create thread_id[%d] failed!!!\n", i);
		}
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		ret = pthread_join(thread_id[i], NULL);
		if (ret != 0) {
			printf("pthread_join thread_id[%d] failed!!!\n", i);
		}
	}

	return 0;
}
```
## output
```bash
...
thread_0 i = 999998, count = 1999999
thread_0 i = 999999, count = 2000000

thread_1 i = 1000000, count = 2000000

thread_0 i = 1000000, count = 2000000
```
 In this example, the value of count is 2000000, as expected.
