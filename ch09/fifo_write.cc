//----------fifo_write.cc-------------
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<cstring>
#define FIFO_NAME "./fifo.pipe"
int main()
{	
	int res;
	char buffer[] = "hello world!";
	if(access(FIFO_NAME,0766) == -1)
	{
		res = mkfifo(FIFO_NAME,0766);  //创建有名管道
		if(res != 0)
		{
			fprintf(stderr,"Could not create fifo %s\n",FIFO_NAME);
			exit(EXIT_FAILURE);	
		}	
	}
	printf("Process %d opening FIFO O_WRONLY\n",getpid());
	int pipe_fd = open(FIFO_NAME,O_WRONLY);
	printf("the file's descriptor is %d\n",pipe_fd);
	if(pipe_fd != -1)
	{
		res = write(pipe_fd,buffer,sizeof(buffer));
		if(res == -1)
		{	
			fprintf(stderr,"write wrror on pipe\n");
			exit(EXIT_FAILURE);
		}	
		printf("write data is %s,%d butes is write\n",buffer,res);
		close(pipe_fd);
	}
	else
	{
		exit(EXIT_FAILURE);
	}
	printf("Process %d finished\n",getpid());
	exit(EXIT_SUCCESS);
	return 0;
}