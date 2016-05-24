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
	char buffer[128];
	memset(buffer,'\0',128);
	printf("Process %d opening FIFO O_RDONLY\n",getpid());
	int pipe_fd = open(FIFO_NAME,O_RDONLY);
	printf("the file's descriptor is %d\n",pipe_fd);
	if(pipe_fd != -1)
	{
		res = read(pipe_fd,buffer,sizeof(buffer));
		if(res == -1)
		{	
			fprintf(stderr,"write wrror on pipe\n");
			exit(EXIT_FAILURE);
		}	
		printf("read data is %s,%d butes is write\n",buffer,res);
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