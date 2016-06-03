#include"daemon.h"
#include"get_param.h"
#include"http_html.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include"http_html.h"


void giveResponse(FILE *client_sock,char *req)
{
    char response_head[512]="HTTP/1/1 200 OK\r\n \
                             Server:http_server1.0\r\n  \
                             Date:2016/6/2\r\n \
                             Content-Length:112\r\n %s";

    char html[512]="<html>\r\n<head>\r\n \
                    hello \r\n</head>\r\n<body>\r\n \
                    hello everybody\r\n</body>\r\n</html>";
    wrtinfomsg2("Response to req:%s",req);
    // fprintf(client_sock,response_head,html);
}
