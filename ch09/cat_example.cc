//------cat_example.cc-------
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void sig_usr(int sig);
int main()
{
	int i=0;
	if(signal(SIGUSR1,sig_usr) == SIG_ERR)
	{
		printf("Cannot catch sigusr1\n");
	}
	if(signal(SIGUSR2,sig_usr) == SIG_ERR)
	{
		printf("Cannot catch sigusr2\n");
	}
	while(1){
		printf("%2d\n",i);
		pause();
		++i;
	}
	return 0;	
}

void sig_usr(int sig)
{
	if(sig == SIGUSR1)
	{
		printf("received sigusr1\n");
	}
	else if(sig == SIGUSR2)
	{
		printf("received sigusr2\n");
	}else
	{
		printf("undeclared sigusr\n");
	}		
}