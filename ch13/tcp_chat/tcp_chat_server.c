/*
*tcp_chat_server.c
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<assert.h>
#include<errno.h>
#define MAXBUF 1024

int main(int argc,char* argv)
{
	int sockfd,newfd;
	socklen_t len;
	struct sockaddr_in my_addr, their_addr;
	unsigned int myport, lisnum;
	char buf[MAXBUF+1];
	int ret = 0;
	
	if(argc > 3)
		myport = atoi(argv[2]);
	else
		myport = 7576;
	if(argc > 4)
		lisnum = atoi(argv[3]);
	else
		lisnum = 5;
	sockfd = socket(AF_INET,SOCK_STREAM,0);  //1、创建socket对象
	assert(sockfd!=-1);
	printf("server sockfd:%d\n",sockfd);
	
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(myport);
	if(argc>2)
		my_addr.sin_addr.s_addr = inet_addr(argv[1]);
	else
		my_addr.sin_addr.s_addr = INADDR_ANY;
	
	ret = bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr)); //2、绑定地址信息
	assert(ret!=-1);
	
	ret = listen(sockfd,lisnum);//3、
	assert(ret!=-1);
	
	printf("wait for connect\n");
	len = sizeof(struct sockaddr);
	newfd = accept(sockfd,(struct sockaddr*)&their_addr,&len);
	assert(newfd!=-1);
	
	printf("server: got connection from %s, port *d,socket %d\n",
				 inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port),newfd);
			 
	pid_t pid;
	pid = fork();
	assert(pid != -1);
	if(pid == 0)
	{
		while(1)
		{
			bzero(buf,MAXBUF+1);
			printf("server:please input message to send:\n");
			fgets(buf,MAXBUF,stdin);
			if(!strncasecmp(buf,"quit",4))
			{
				printf("server: I will quit\n");
				break;	
			}
			len = send(newfd,buf,strlen(buf)-1,0);
			if(len<0)
			{
				printf("message '%s' send failure!\errno code is %d,error message is '%s'",
								buf,errno,strerror(errno));
				break;	
			}
		}	
	}
	else
	{
		while(1)
		{
			bzero(buf,MAXBUF+1);
			len = recv(newfd,buf,MAXBUF,0);
			if(len>0)
			{
				printf("recv successful:'%s',%d byte recv\n",buf,len);
			}
			else if(len < 0)
			{
				printf("recv failure!\errno code is %d,error message is '%s'",
								errno,strerror(errno));
				break;	
			}
			else
			{
					printf("the other one close,quit\n");
			}
		}
	}
	close(newfd);
	close(sockfd);
	return 0;
}