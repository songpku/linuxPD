#include"log_proc.h"
#include<string.h>

void wrtinfomsg(char *msg)
{
    syslog(LOG_INFO,"%s",msg);
}

void wrtinfomsg2(char *format,char* name)
{
    char buf[128];
    sprintf(buf,format,name);
    wrtinfomsg(buf);
}
