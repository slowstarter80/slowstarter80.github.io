#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/test_fifo"
#define FIFO_WRITE_STRING "fifo write/read test!"

int main(int argc, char *argv[])
{ 
	int fifo_fd = -1;
	int fd = -1;
	int flag = O_WRONLY; 
	
	int default_umask = umask(0);
	printf("default umask = %o\n", default_umask);
	umask(default_umask);

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

	printf("write data to fifo = %s\n", FIFO_WRITE_STRING);
	write(fd, FIFO_WRITE_STRING, strlen(FIFO_WRITE_STRING) + 1);
	close(fd);

	return 0; 
}
