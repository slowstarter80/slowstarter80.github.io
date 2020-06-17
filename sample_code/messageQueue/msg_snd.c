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
	int msgkey = 1234;


	qid = msgget(msgkey, IPC_CREAT | 0666);

	if (qid == -1) {
		perror("msgget");
		exit(EXIT_FAILURE);
	}

	struct msgbuf msg;
	time_t t;

	for (int i = 0; i < 12; i++) {

		msg.mtype = (i%4) + 1;

		time(&t);
		snprintf(msg.mtext, sizeof(msg.mtext), "msgtype = %ld, a message at %s", msg.mtype, ctime(&t));

		if (msgsnd(qid, (void *) &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
			perror("msgsnd error");
			exit(EXIT_FAILURE);
		}
		printf("sent: %s\n", msg.mtext);
		sleep(1);
	}

	return 0;
}

