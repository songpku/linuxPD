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
    assert(argc>=2);
    
    struct sockaddr_in s_addr;
    
    int sock;
    socklen_t addr_len;
    int len;
    char buf[128];
    sock = socket(AF_INET,SOCK_DGRAM,0);
    assert(sock!=-1);
    
    memset(&s_addr,0,sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(7838);
    s_addr.sin_addr.s_addr = inet_addr(argv[argc-1]);
    
    addr_len = sizeof(s_addr);
    while(1)
    {
        fgets(buf,128,stdin);
        len = sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&s_addr,addr_len);
        assert(len>0);
        printf("send success\n");
    }
    return 0;
}