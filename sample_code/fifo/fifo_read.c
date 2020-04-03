#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/test_fifo"
#define BUF_SIZE 255 

int main(int argc, char *argv[])
{ 
	int fifo_fd = -1;
	int fd = -1;
	int flag = O_RDONLY; 
	char buf[BUF_SIZE];
	int buf_size = BUF_SIZE;
	int cnt = 0;

	if (access(FIFO_PATH, F_OK) < 0) {
		fifo_fd = mkfifo(FIFO_PATH, 0777);

		if (fifo_fd < 0 ) {
			perror("mkfifo error\n");
			exit(0);
		}
	}

	fd = open(FIFO_PATH, flag);
	if (fd < 0 ) {
		perror("fifo open error\n");
		exit(0);
	}

	do {
		cnt = read(fd, buf, buf_size); 
		if(cnt > 0) {
			printf("read data from fifo: %s\n", buf); 
		}
	} while(cnt > 0);
	close(fd);

	return 0; 
}
