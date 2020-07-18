#include <thread>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mutex>
using namespace std;
#define THREAD_COUNT (2)
static int count = 0;
std::mutex mtx;

static void thread_function(char *arg)
{
	int i = 0;
	char *thread_name = arg;
	for (i = 0; i < 1000000; i++) {
		mtx.lock();
		count++;
		cout<<thread_name<<" i = " <<i<<", count = "<<count<<endl;
		mtx.unlock();
	}
	sleep(2);
	cout<<endl;
	cout<<thread_name<<" i = " <<i<<", count = "<<count<<endl;
}

int main(int argc, char *argv[])
{
	std::thread thread_id[THREAD_COUNT];
	char thread_name[THREAD_COUNT][20];
	char buf[20] = {0,};

	for (int i = 0; i < THREAD_COUNT; i++) {
		snprintf(buf, 9, "thread_%d", i);
		memcpy(thread_name[i], buf, sizeof(buf));
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		thread_id[i] = std::thread(thread_function, thread_name[i]);
	}

	for (int i = 0; i < THREAD_COUNT; i++) {
		thread_id[i].join();
	}

	return 0;
}
