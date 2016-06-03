/*
*tcp_chat_client.c
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

int main(int argc,char* argv[])
{
	int sockfd,len;
	struct sockaddr_in dest;
	char buf[MAXBUF + 1];
	if(argc < 3)
	{
		printf("You need input:\n\tIP and port\n");
		exit(EXIT_FAILURE);	
	}	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd > 0);
	
	bzero(&dest,sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(argv[argc-1]));
	int ret_inet_aton = inet_aton(argv[argc-2],(struct sockaddr*)&dest.sin_addr.s_addr);
	assert(ret_inet_aton != 0);
	
	int ret_conn = connect(sockfd,(struct sockaddr*)&dest,sizeof(dest));
	assert(ret_conn != -1);
	printf("server connection\n");
	pid_t pid;
	pid = fork();
	assert(pid!=-1);
	
	if(pid == 0)
	{
		while(1)
		{
			bzero(buf,MAXBUF + 1);
			len = recv(sockfd,buf,MAXBUF,0);
			if(len>0)
			{
				printf("clent: recv successful:'%s', %d byte recv\n",buf,len);	
			}	
			else if(len < 0)
			{
				perror("fail to recv\n");
				break;	
			}
			else
			{
				printf("the server close, quit\n");
				break;
			}
		}	
	}
	else
	{
		while(1)
		{
			bzero(buf,MAXBUF+1);
			printf("clent: Please input something for send:\n");
			fgets(buf,MAXBUF,stdin);
			if(!strncasecmp(buf,"quit",4))
			{
				printf("clent: I will quit!\n");
				break;
			}	
			len = send(sockfd, buf, strlen(buf)-1,0);
			if(len<0)
			{
				perror("fail to send");
				break;	
			}
		}
		
	}
	close(sockfd);
	return 0;
}