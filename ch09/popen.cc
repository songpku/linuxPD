//----------redirect_who_sort.cc-------------
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<cstring>
int main(){
	FILE* finput,*foutput;
	char buf[128];
	finput = popen("echo test!","r");
	foutput = popen("cat","w");
	read(fileno(finput),buf,strlen("test!"));
	write(fileno(foutput),buf,strlen("test!"));
	pclose(finput);
	pclose(foutput);
	
	return 0;
}