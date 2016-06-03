#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define MAXLINE 4096
int main(int argc,char* argv[])
{
	socklen_t len;
	struct sockaddr *cliaddr;
	char buf[MAXLINE];
	time_t ticks;
	ticks = time(NULL);
	snprintf(buf,sizeof(buf),"%¡£24s\r\n",ctime(&ticks));
	write(0,buf,strlen(buf));

	close(0);
	exit(EXIT_SUCCESS);


}
