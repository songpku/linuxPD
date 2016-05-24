#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

struct msgbuf{
  int type;
  char ptr[0];  
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
  printf("key is %d\n",key);
  int msgid;
  msgid = msgget(key,IPC_CREAT|0600);  //创建消息队列
  pid_t pid;
  pid = fork();
  if(pid == 0)
  {
    while(1)
    {
      printf("please input msg to send: ");
      char buf[128];
      fgets(buf,128,stdin);
      printf("buf: %s",buf);
      struct msgbuf * ptr = malloc(sizeof(struct msgbuf) + strlen(buf) + 1);
      ptr->type = 1;
      memcpy(ptr->ptr,buf,strlen(buf) + 1);
      printf("send %s to %d,type=2\n",ptr->ptr,msgid);
      if(msgsnd(msgid,ptr,strlen(buf)+1,0) == -1)
      {
      	perror("fail to send message\n");
      	exit(EXIT_FAILURE);
      }
      free(ptr);  
    } 
  
  }
  else
  {
    struct msgbuf
    {
    	int type;
    	char ptr[1024];
    };
    while(1){
    	printf("wait: 1\n");
    	struct msgbuf mybuf;
    	memset(&mybuf,'\0',sizeof(mybuf));
    	if(msgrcv(msgid,&mybuf,1024,2,0)== -1)
    	{
      	perror("fail to receive message\n");
      	exit(EXIT_FAILURE);
      }
    	printf("recv msg:%s\n",mybuf.ptr);	
    }
  }
  return 0; 
}