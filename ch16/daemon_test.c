#include"daemon.h"
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
