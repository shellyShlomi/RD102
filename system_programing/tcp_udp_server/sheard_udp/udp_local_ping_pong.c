#include "ping_pong.h"
#include "ping_pong_func.h"

#include "udp_local_ping_pong.h"
#define MAXBUFLEN 100

/* get sockaddr, IPv4 or IPv6:*/
int GetInMsgU(int sockfd, struct sockaddr *their_addr, socklen_t *addr_len)
{
    int numbytes = 0;
    char buf[MAXBUFLEN] = {0};

    if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN - 1, 0,
                             their_addr, addr_len)) == -1)
    {
        perror("recvfrom");
        return (-1);
    }

    buf[numbytes] = '\0';
    printf("%s\n", buf);

    return (numbytes);
}

int SendOutMsgU(int sockfd, struct sockaddr *their_addr, socklen_t addr_len, const char *msg)
{
    if ((sendto(sockfd, msg, strlen(msg), 0, their_addr, addr_len)) == -1)
    {
        perror("sendto");
        return (-1);
    }

    return (0);
}


