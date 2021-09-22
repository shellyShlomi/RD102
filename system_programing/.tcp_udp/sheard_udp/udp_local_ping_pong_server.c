
#include "udp_local_ping_pong_server.h"

#define MAXBUFLEN 100

#define LOOP break
#define TO_LOOP(x)    \
    {                 \
        if (x)        \
        {             \
            continue; \
        }             \
    }

int BindClientToServer(addrinfo_t *servinfo, int *sockfd)
{
    /* loop through all the results and bind to the first we can*/

    addrinfo_t *p = servinfo;
    for (; p != NULL; p = ((addrinfo_t *)p)->ai_next)
    {
        TO_LOOP(CreatSockt(sockfd, p->ai_family, p->ai_socktype, p->ai_protocol));
        TO_LOOP(BindClient(*sockfd, p->ai_addr, p->ai_addrlen));
        LOOP;
    }

    if (p == NULL)
    {
        fprintf(stderr, "server: failed to bind socket\n");
        return 2;
    }

    return 0;
}

int BindClient(int sockfd, const struct sockaddr *ai_addr, int ai_addrlen)
{
    if (bind(sockfd, ai_addr, ai_addrlen) == -1)
    {
        close(sockfd);
        perror("server: bind");
        return (1);
    }
    return (0);
}

void ReadIncomingPackegs(int sockfd, const char *o_msg)
{
    int i = 0;
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);
    int res = 0;

    while (i < NUM_TO_SEND && 0 != (GetInMsg(sockfd, (struct sockaddr *)&their_addr, &addr_len)) && res == 0)
    {
        sleep(1);
        res = SendOutMsg(sockfd, (struct sockaddr *)&their_addr, addr_len, o_msg);
        ++i;
    }

    return;
}
