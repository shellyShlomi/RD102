
#include "ping_pong.h"
#include "ping_pong_func.h"
#include "udp_local_ping_pong.h"
#include "udp_local_ping_pong_client.h"

#define MAXBUFLEN 100
#define START 3
#define END 10

#define LOOP break
#define TO_LOOP(x)    \
    {                 \
        if (x)        \
        {             \
            continue; \
        }             \
    }

int ClientCreatSocketU(addrinfo_t *servinfo, int *sockfd)
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
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);
    size_t rand = GetRand(START, END);
    while (rand)
    {
        SendOutMsgU(sockfd, servinfo->ai_addr, servinfo->ai_addrlen, o_msg);
        GetInMsgU(sockfd, (struct sockaddr *)&their_addr, &addr_len);
        --rand;
        sleep(GetRand(START, END));
    }

    return;
}