#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<errno.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<assert.h>

int main(int argc,char* argv[])
{
    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;
    
    int sock;
    socklen_t addr_len;
    int len;
    char buf[128];
    sock = socket(AF_INET,SOCK_DGRAM,0);
    assert(sock!=-1);
    
    memset(&s_addr,0,sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(7838);
    s_addr.sin_addr.s_addr = INADDR_ANY;
    int ret_bind = bind(sock,(struct sockaddr*)&s_addr,sizeof(s_addr));
    assert(ret_bind!=-1);    
    printf("%s: %d is ready for recv message.\n",inet_ntoa(s_addr.sin_addr),s_addr.sin_port);
    
    addr_len = sizeof(c_addr);
    while(1)
    {
        len = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&c_addr,&addr_len);
        assert(len>0);
        buf[len] = '\0';
        printf("receive from %s:%d\n    %s\n\r",inet_ntoa(c_addr.sin_addr),ntohs(c_addr.sin_port),buf);
    }
    return 0;
}