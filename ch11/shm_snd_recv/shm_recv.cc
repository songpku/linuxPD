/*
*利用共享内存实现全双工通讯
*参数为两个字符串，分别为发送方和接收方名字
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<string>
#include<cstring>
#include<queue>
#include<iostream>

using namespace std;
int main(int argc,char* argv[])
{
	/*
	if(argc < 3)
	{
		perror("parameter insufficient!\n");
		exit(EXIT_FAILURE);
	}
	string snd_name = argv[1];
	string recv_name = argv[2];
	*/
	int running = 1;
	int shid,semid,value;
	string *sharem = NULL;
	sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_flg = SEM_UNDO;

	if((semid = semget((key_t)123456,1,0666|IPC_CREAT)) == -1)
	{
		perror("fail to semget\n");
		exit(EXIT_FAILURE);
	}
	shid = shmget((key_t)654321,(size_t)2048,0600|IPC_CREAT); //创建共享内存
	if(shid == -1)
	{
		perror("fail to shmget\n");
		exit(EXIT_FAILURE);
	}
	sharem = (string*)shmat(shid,NULL,0); //挂接共享内存到当前进程
	if(sharem == NULL)
	{
		perror("fail to shmat\n");
		exit(EXIT_FAILURE);
	}

	string input;
	
	while(running){
		if((value=semctl(semid,0,GETVAL))==1){
			printf("\nread msg,value=%d:\n",value);
			sem_b.sem_op = -1;
			if(semop(semid,&sem_b,1) == -1)
			{
				perror("fail to P\n");
				exit(EXIT_FAILURE);
			}
			cout<<*sharem<<endl;
		}
		if(input == "end")
		{
			--running;
		}

	}
	shmdt(sharem);
	shmctl(shid,IPC_RMID,0);
	semctl(semid,IPC_RMID,0);
	
	return 0;
}
