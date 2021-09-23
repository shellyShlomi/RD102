
#define MAXBUFLEN 100

#include "ping_pong.h"
#include "ping_pong_func.h"

#include "tcp_local_ping_pong.h"
#define MAXBUFLEN 100

/* get sockaddr, IPv4 or IPv6:*/

int GetInMsg(int sockfd)
{
    int numbytes = 0;
    char buf[MAXBUFLEN] = {0};

    if ((numbytes = recv(sockfd, buf, sizeof(buf), 0)) == -1)
    {
        perror("recv");
        return (numbytes);
    }

    buf[numbytes] = '\0';
    puts(buf);

    return (numbytes);
}

int SendOutMsg(int sockfd, const char *msg)
{
    if ((send(sockfd, msg, strlen(msg), 0)) == -1)
    {
        perror("sendto");
        return (-1);
    }

    return (0);
}
