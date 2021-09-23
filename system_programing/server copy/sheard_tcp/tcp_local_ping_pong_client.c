
#include "ping_pong.h"
#include "ping_pong_func.h"

#include "tcp_local_ping_pong.h"
#include "tcp_local_ping_pong_client.h"

#define MAXBUFLEN 100

int ClientCreatSocket(addrinfo_t *servinfo, int *sockfd)
{
    if (0 != CreatSockt(sockfd, servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))
    {
        perror("client: CreatSockt");
        close(*sockfd);
        return 1;
    }
    return 0;
}

int ConnectSockt(int sockfd, addrinfo_t *p, int ai_addrlen)
{
    if (connect(sockfd, p->ai_addr, ai_addrlen) < 0)
    {
        perror("client: connect");
        close(sockfd);
        return 1;
    }

    return (0);
}

void ReadIncomingMsgFromServer(int sockfd, const char *o_msg)
{
    size_t i = 0;
    do
    {
        SendOutMsg(sockfd, o_msg);
        ++i;
        GetInMsg(sockfd);

    } while (i < NUM_TO_SEND);

    return;
}
