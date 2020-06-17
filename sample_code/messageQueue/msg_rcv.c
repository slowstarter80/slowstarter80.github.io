#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
	long mtype;
	char mtext[80];
};

int main(int argc, char *argv[])
{
	int qid ;
	int msgtype = 1;
	int msgkey = 1234;

	if (argc == 2) {
		msgtype = atoi(argv[1]);
	}
	else {
		printf("invalid parameter()\n");
		return 0;
	}


	qid = msgget(msgkey, IPC_CREAT | 0666);

	if (qid == -1) {
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	struct msgbuf msg;
	time_t t;

	msg.mtype = msgtype;

	while(1) {

		if (msgrcv(qid, (void *) &msg, sizeof(msg.mtext), msgtype, IPC_NOWAIT) == -1) {
			if (errno != ENOMSG) {
				perror("msgrcv");
				exit(EXIT_FAILURE);
			}
			printf("No message available for msgrcv()\n");
			break;

		} else {
			printf("message received: %s\n", msg.mtext);
		}
	}

	return 0;
}

