#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512
struct msg_st
{
	long int msg_type;
	char text[MAX_TEXT];
};

int main()
{
	int running = 1;
	struct msg_st data;
	char buffer[BUFSIZ];
	int msgid = -1;

	//������Ϣ����
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if(pid == 0){
		//����Ϣ������д��Ϣ��ֱ��д��end
		while(running)
		{
			//��������
			printf("Enter some text: ");
			fgets(buffer, BUFSIZ, stdin);
			data.msg_type = 1;    //ע��2
			strcpy(data.text, buffer);
			//����з�������
			if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
			{
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
			//����end��������
			if(strncmp(buffer, "end", 3) == 0)
				running = 0;
			sleep(1);
		}
		exit(EXIT_SUCCESS);
	}	else{
			//�Ӷ����л�ȡ��Ϣ��ֱ������end��ϢΪֹ
		while(running)
		{
			if(msgrcv(msgid, (void*)&data, BUFSIZ, 2, 0) == -1)
			{
				fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
				exit(EXIT_FAILURE);
			}
			printf("You wrote: %s\n",data.text);
			//����end����
			if(strncmp(data.text, "end", 3) == 0)
				running = 0;
		}
		//ɾ����Ϣ����
		if(msgctl(msgid, IPC_RMID, 0) == -1)
		{
			fprintf(stderr, "msgctl(IPC_RMID) failed\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
}