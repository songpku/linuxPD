//----------redirect_who_sort.cc-------------
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){
	int fds[2];
	if(pipe(fds) == -1){
		perror("pipes");
		exit(EXIT_FAILURE);
	}
	if(fork()==0)
	{         //��һ���ӽ���
		char buf[128];
		printf("fds0 is %d\n",fds[0]);
		dup2(fds[0],0);      //���˺ͱ�׼�����0������  
		close(fds[1]);    //�ر�д�ˣ�����Ϊ������
		printf("fds0 is %d\n",fds[0]);
		execlp("sort","sort",(char*)0);
	}	
	else
	{
		if(fork()==0){
			dup2(fds[1],1);
			close(fds[0]);
			execlp("who","who",(char*)0);	
		}	else{
				close(fds[0]);
				close(fds[1]);
				wait(NULL);
				wait(NULL);
		}
	}
	return 0;
}