
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
