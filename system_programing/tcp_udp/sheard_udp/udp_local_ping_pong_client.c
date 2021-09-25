
#include "udp_local_ping_pong_client.h"
#define MAXBUFLEN 100

#define LOOP break
#define TO_LOOP(x)    \
    {                 \
        if (x)        \
        {             \
            continue; \
        }             \
    }

int ClientCreatSocket(addrinfo_t *servinfo, int *sockfd)
{

    addrinfo_t *p = servinfo;

    CreatSockt(sockfd, p->ai_family, p->ai_socktype, p->ai_protocol);

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to bind socket\n");
        return 2;
    }

    return 0;
}

void ReadIncomingMsgFromServer(int sockfd, addrinfo_t *servinfo, const char *o_msg)
{
    int numbytes = 0;
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);
    int i = NUM_TO_SEND;

    do
    {
        SendOutMsg(sockfd, servinfo->ai_addr, servinfo->ai_addrlen, o_msg);
        --i;

    } while (0 != (numbytes = GetInMsg(sockfd, (struct sockaddr *)&their_addr, &addr_len)) && i > 0);

    return;
}
