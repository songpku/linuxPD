#include"get_param.h"
#include"http_html.h"
#include"log_proc.h"
#include<netinet/in.h>
#include<arpa/inet.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<net/if.h>

int get_arg(char *name)
{
    char logmsg[128];
    sprintf(logmsg,"get param: %s",name);
    wrtinfomsg(logmsg);
    return 0;
}

int get_addr(char *name)
{
    int inet_sock;
    struct ifreq ifr;
    inet_sock = socket(AF_INET,SOCK_DGRAM,0);
    strcpy(ifr.ifr_name,name);
    if(ioctl(inet_sock,SIOCGIFADDR,&ifr)<0)
    {
        wrtinfomsg("error: ioctl");
        exit(EXIT_FAILURE);
    }
    sprintf(ip,"%s",inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
}
