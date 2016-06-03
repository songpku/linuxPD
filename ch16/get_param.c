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
#include"http_server.h"

int get_arg(char *cmd)
{
		FILE* fp;
        char buffer[1024];
        size_t bytes_read;
        char* match;
        fp = fopen ("/etc/test_httpd.conf", "r");
        bytes_read = fread (buffer, 1, sizeof (buffer), fp);
        fclose (fp);

        if (bytes_read == 0 || bytes_read == sizeof (buffer))
                return 0;
        buffer[bytes_read] = '\0';

        if(!strncmp(cmd,"home_dir",8))
        {
                match = strstr (buffer, "home_dir=");
                if (match == NULL)
                        return 0;
                bytes_read=sscanf(match,"home_dir=%s",home_dir);
                return bytes_read;
        }

        else if(!strncmp(cmd,"port",4))
        {
                match = strstr (buffer, "port=");
                if (match == NULL)
                        return 0;
                bytes_read=sscanf(match,"port=%s",port);
                return bytes_read;
        }

        else if(!strncmp(cmd,"ip",2))
        {
                match = strstr (buffer, "ip=");
                if (match == NULL)
                        return 0;
                bytes_read=sscanf(match,"ip=%s",ip);
                return bytes_read;
        }
        else if(!strncmp(cmd,"back",4))
        {
                match = strstr (buffer, "back=");
                if (match == NULL)
                        return 0;
                bytes_read=sscanf(match,"back=%s",back);
                return bytes_read;
        }
	     else
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
