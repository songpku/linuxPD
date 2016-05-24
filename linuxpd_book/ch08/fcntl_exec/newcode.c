#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	printf("-------newcode--------\n");
	int i;
	int fd;
	char *ptr="helloworld\n";
	fd=atoi(argv[1]);
	i=write(fd,ptr,strlen(ptr));
	printf("write in file %d,return %d\n",fd,i);
	if(i<=0)
		perror("write");
	close(fd);	
}
