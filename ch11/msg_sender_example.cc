#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define MAX_TEXT 512
struct msg_st
{
	long int msg_type;
	char text[BUFSIZ];
};
int main(int argc,char *argv[])
{
  if(argc < 2)
  {
    perror("paramater is not enough!\n");
    exit(EXIT_FAILURE);
  }
  key_t key;
  key = ftok(argv[1],100);  //创建key值
  char buf[MAX_TEXT];
  printf("key is %d\n",key);
  int msgid;
  msgid = msgget(key,IPC_CREAT|0666);  //创建消息队列
  pid_t pid;
  msg_st msg;
  pid = fork();
  if(pid == 0)
  {
    while(1)
    {
      //printf("please input msg to send: ");
     
      fgets(buf,128,stdin);
     // printf("buf: %s",buf);
    
      msg.msg_type = 2;
      memcpy(msg.text,buf,MAX_TEXT);
     // printf("send %s to %d,type=2\n",msg.text,msgid);
      if(msgsnd(msgid,(void*)&msg,MAX_TEXT,0) == -1)
      {
      	perror("fail to send message\n");
      	exit(EXIT_FAILURE);
      }
    } 
  
  }
  else
  {
    while(1){
    	//printf("wait: 1\n");
    	if(msgrcv(msgid,(void*)&msg,MAX_TEXT,1,0)== -1)
    	{
      	perror("fail to receive message\n");
      	exit(EXIT_FAILURE);
      }
    	printf("1: %s\n",msg.text);	
    }
  }
  return 0; 
}