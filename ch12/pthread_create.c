//-------pthread_create.cc--------
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/syscall.h>

struct message
{
	int i;
	int j;
};

void *hello(struct message* str)
{
	printf("child thread: thread ID=%lu; sysPid=%ld\n",pthread_self(),syscall(SYS_gettid));
	printf("the arg.i is %d; the arg.j is %d\n",str->i,str->j);	
}

int main()
{
	struct message test;
	test.i =  10;
	test.j = 100;
	
	pthread_t ptid;
	
	pthread_create(&ptid,NULL,(void*)*hello,&test); //创建线程
	printf("parent thread: thread ID=%lu; sysPid=%ld\n",pthread_self(),syscall(SYS_gettid));
	pthread_join(ptid,NULL);
	return 0;	
}