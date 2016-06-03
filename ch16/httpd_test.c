#include"daemon.h"
#include"get_param.h"
#include<string.h>
int main(int argc,char* argv[])
{
    struct sockaddr_in addr;
    int sock_fd,addrlen;
    init_daemon(argv[0],LOG_INFO);
    if(get_arg("home_dir")==0)
    {
        sprintf(home_dir,"%s","/tmp");
    }
    if(get_arg("ip")==0)
    {
        get_addr("eth0");
    }
    if(get_arg("port")==0)
    {
        sprintf(port,"%s","80");
    }
    if(get_arg("back")==0)
    {
        sprintf(back,"%s","5");
    }
}
