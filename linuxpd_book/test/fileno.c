#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	int fp1;
	FILE *stream;
	if((fp1=open("./../data/no1.txt",O_WRONLY))==-1){
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("no1.txt file is:\t%d\n",fp1);
	stream = fdopen(fp1,"a");
	if(stream == NULL){
		printf("fdopen failed\n");
	}else{
		fprintf(stream,"test fdopen");
		fclose(stream);
	}
	printf("current content is:\n");
	system("cat ./../data/no1.txt");
	close(fp1);
	return 0;

}
