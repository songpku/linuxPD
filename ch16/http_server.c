#include"daemon.h"
#include"get_param.h"
#include"http_html.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include"log_proc.h"
#include<arpa/inet.h>
#include<unistd.h>
#include"http_server.h"
#include"http_html.h"

int main(int argc,char* argv[])
{
    struct sockaddr_in addr;
    int sock_fd,addrlen;
    char buf[128];
    init_daemon(argv[0],LOG_INFO);
    if(get_arg("home_dir")==0)
    {
        sprintf(home_dir,"%s","/tmp");
    }
    wrtinfomsg2("home_dir: %s",home_dir);
    if(get_arg("ip")==0)
    {
        get_addr("eno16777736");
    }
    wrtinfomsg2("ip: %s",ip);
    if(get_arg("port")==0)
    {
        sprintf(port,"%s","80");
    }
    wrtinfomsg2("port: %s",port);
    if(get_arg("back")==0)
    {
        sprintf(back,"%s","5");
    }
    wrtinfomsg2("back: %s",back);

    if((sock_fd = socket(PF_INET,SOCK_STREAM,0))<0)
    {
        wrtinfomsg("error: socket");
        exit(EXIT_FAILURE);
    }

    addrlen = 1;
    setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,&addrlen,sizeof(&addrlen)); //允许重用本地地址和端口

    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(port));
    addr.sin_addr.s_addr = inet_addr(ip);
    if(bind(sock_fd,(struct sockaddr*)&addr,sizeof(addr))<0)
    {
        wrtinfomsg("error: bind");
        exit(EXIT_FAILURE);
    }
    if(listen(sock_fd,atoi(back))<0)
    {
        wrtinfomsg("error: listen");
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        int len;
        int new_fd;
        addrlen = sizeof(struct sockaddr);

        wrtinfomsg("wait for connection");
        new_fd = accept(sock_fd,(struct sockaddr*)&addr,&addrlen);
        if(new_fd < 0)
        {
            wrtinfomsg("error: accept");
            exit(EXIT_FAILURE);
        }
        wrtinfomsg("accept");
        sprintf(buf,"Connection come from: %s:%d",inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        wrtinfomsg(buf);

        pid_t pid;
        pid = fork();
        if(pid == 0)
        {
           // close(sock_fd);
            bzero(buf,MAXBUF+1);
            //if((len = recv(new_fd,buf,MAXBUF,0))>0)
           if(1)
            {
                FILE* clientFP = fdopen(new_fd,"w");
                if(clientFP == NULL)
                {
                    wrtinfomsg("error:clientFP");
                    exit(EXIT_FAILURE);
                }
                else
                {
                   char Req[MAXPATH + 1]="";
                   sscanf(buf,"GET %s HTTP",Req);
                   bzero(buf,MAXBUF+1);
                   wrtinfomsg2("Request get the file:\" %s \"\n",Req);
                   giveResponse(clientFP,Req);
                   fclose(clientFP);
                }
            }
            else
            {
              wrtinfomsg("Req is empty");
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
           // close(new_fd);
            continue;
        }

    }
}
