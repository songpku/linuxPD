//--------------daemon_exp.c-------------------
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syslog.h>
#include<time.h>
#include<sys/param.h>


int init_daemon(const char *pname, int facility)
{
    int pid;
    int i;
    //1、屏蔽关于控制终端的信号
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    //2、后台运行
    if(pid = fork())  //将父前进程退出
        exit(0);
    else if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    //3、脱离终端和进程组
    setsid();

    //4、禁止进程重新开启控制终端
    if(pid = fork())  //将父前进程退出
        exit(0);
    else if(pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    //5、关闭打开的文件描述符
    for(i=0;i<NOFILE;++i)
    {
        close(i);
    }
    open("/dev/null",O_RDONLY);
    open("/dev/null",O_RDWR);
    open("/dev/null",O_RDWR);

    //6、改变当前工作目录
    chdir("/tmp");

    //7、重设文件创建掩码
    umask(0);

    //8、处理SIGCHLD信号(子进程退出信号)
    signal(SIGCHLD,SIG_IGN);
    openlog(pname,LOG_PID,facility);
    return;
}

int main(int argc,char* argv[])
{
    FILE *fp;
    time_t ticks;
    init_daemon(argv[0],LOG_KERN);
    while(1)
    {
         sleep(1);
         ticks = time(NULL);
         syslog(LOG_INFO,"%s",asctime(localtime(&ticks)));
    }
}
