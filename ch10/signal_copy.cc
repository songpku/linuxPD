//--------signal_copy.cc---------
#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#define BUFSIZE 1

void sig_alarm(int arg);
void sig_usr(int sig);

int file_size,count;
int main(int argc,char* argv[])
{
	pid_t pid;
	int fd_src,fd_dst,i;
	char buf[128];
	if(argc !=3){
		printf("paramters is not enough!\n");
		return -1;	
	}
	if( (fd_src = open(argv[1],O_RDONLY)) == -1)
	{
		perror("open file src fail!\n");
		exit(EXIT_FAILURE);
	}
	file_size = lseek(fd_src,0,SEEK_END);
	lseek(fd_src,0,SEEK_SET);
	if( (fd_dst = open(argv[2],O_RDWR|O_CREAT,0644)) == -1)
	{
		perror("open file dst fail!\n");
		exit(EXIT_FAILURE);
	}
	if( (pid =fork())==-1)
	{
		perror("fail to fork!\n");
		exit(EXIT_FAILURE);
	}
	if(pid > 0) //¸¸½ø³Ì
	{
		signal(SIGUSR1,sig_usr);
		do
		{
			memset(buf,'\0',128);
			if((i = read(fd_src,buf,BUFSIZE)) == -1){
				perror("fail to read\n");	
				exit(EXIT_FAILURE);
			}	
			else if(i == 0)
			{
				printf("finish read\n");
				kill(pid,SIGINT);
				break;
			}
			else
			{
					if(write(fd_dst,buf,BUFSIZE) == -1)
					{
						perror("fail to write\n");
						exit(EXIT_FAILURE);	
					}
					count += i;
					//printf("copy %d / %d\n",count,file_size);
			}
		}while(i>0);
		waitpid(pid,NULL,0);
		exit(EXIT_SUCCESS);
		printf("father process is end\n");
	}
	else if(pid ==0)
	{
		usleep(1);
		signal(SIGALRM,sig_alarm);
		ualarm(1000,1000);
		while(1)
		{
			;
		}
		printf("child process is end\n");
	}
}

void sig_alarm(int arg)
{
		kill(getppid(),SIGUSR1);
}
void sig_usr(int sig)
{
	float i;
	i = (float)count/file_size;
	printf("curent over :%0.0f %% \n",i*100);
}