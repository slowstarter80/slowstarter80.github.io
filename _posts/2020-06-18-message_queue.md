---
layout: single
title: Message Queues
date : 2020-06-18 00:23:45 +0900
last_modified_at: 2020-06-18 02:47:05 +0900
categories: [c/c++]
tags: [programming,c/c++]
comments: true
public : true
---

# IPC using message queue 
 A message queues is one of IPC mechanism. It provides a way to send and get data between 2 unrelated processes.
The 2 processes access the same queue by using the same key parameter in the msgget() function. One process puts messages in queue, and the other process gets messages from the queue.
 Message are sent by using the msgsnd() function. When sending, the message type is specified. Then in the receiving process, messages can be received only ofor the desired message type. Here the message type must be a positive integer value. The queue capacity is set to MSGMNB bytes by default when creating a queue, and it can be changed by changing the msg_qbytes field of the msgid-ds structure using the msgctl() function.
 Message queue related parameters are as follow.

```
MSGMNB: Maximum number of bytes per message queue.
MSGMNI: Maximum number of message queue identifiers (system wide).
MSGMAX: Maximum size of a whole message. On some systems you may need to increase this limit. 
```

In Linux, You can check these parameter values with the commands below.

```bash
$ cat /proc/sys/kernel/msgmax 
8192
$ cat /proc/sys/kernel/msgmnb
16384
$ cat /proc/sys/kernel/msgmni
32000
```
or
```bash
$ sysctl -a | grep kernel.msg
kernel.msgmax = 8192
kernel.msgmnb = 16384
kernel.msgmni = 32000
```

<br/>
## msg_snd.c
 In this example, a message queue is created with msgkey 1234, and send a message every second. The message type is repeated 3 times in the order of 1, 2, 3 and 4.
```c
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

```

## output
```bash
$ ./msg_snd 
sent: msgtype = 1, a message at Thu Jun 18 02:34:51 2020
sent: msgtype = 2, a message at Thu Jun 18 02:34:52 2020
sent: msgtype = 3, a message at Thu Jun 18 02:34:53 2020
sent: msgtype = 4, a message at Thu Jun 18 02:34:54 2020
sent: msgtype = 1, a message at Thu Jun 18 02:34:55 2020
sent: msgtype = 2, a message at Thu Jun 18 02:34:56 2020
sent: msgtype = 3, a message at Thu Jun 18 02:34:57 2020
sent: msgtype = 4, a message at Thu Jun 18 02:34:58 2020
sent: msgtype = 1, a message at Thu Jun 18 02:34:59 2020
sent: msgtype = 2, a message at Thu Jun 18 02:35:00 2020
sent: msgtype = 3, a message at Thu Jun 18 02:35:01 2020
sent: msgtype = 4, a message at Thu Jun 18 02:35:02 2020
```

<br/>
## msg_rcv.c
```c
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

```

## output
### message type 1
```bash
$ ./msg_rcv 1
message received: msgtype = 1, a message at Thu Jun 18 02:42:40 2020
message received: msgtype = 1, a message at Thu Jun 18 02:42:44 2020
message received: msgtype = 1, a message at Thu Jun 18 02:42:48 2020
No message available for msgrcv()
```

### message type 2
```bash
$ ./msg_rcv 2
message received: msgtype = 2, a message at Thu Jun 18 02:42:41 2020
message received: msgtype = 2, a message at Thu Jun 18 02:42:45 2020
message received: msgtype = 2, a message at Thu Jun 18 02:42:49 2020
No message available for msgrcv()
```

### message type 3
```bash
$ ./msg_rcv 3
message received: msgtype = 3, a message at Thu Jun 18 02:42:42 2020
message received: msgtype = 3, a message at Thu Jun 18 02:42:46 2020
message received: msgtype = 3, a message at Thu Jun 18 02:42:50 2020
No message available for msgrcv()
```

### message type 4
```bash
$ ./msg_rcv 4
message received: msgtype = 4, a message at Thu Jun 18 02:42:43 2020
message received: msgtype = 4, a message at Thu Jun 18 02:42:47 2020
message received: msgtype = 4, a message at Thu Jun 18 02:42:51 2020
No message available for msgrcv()
```
