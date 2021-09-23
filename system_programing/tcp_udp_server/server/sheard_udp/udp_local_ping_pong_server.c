
#include "ping_pong.h"
#include "ping_pong_func.h"
#include "udp_local_ping_pong.h"

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

// int ReadIncomingPackegs(int sockfd, const char *o_msg)
// {
//     struct sockaddr_in their_addr = {0};
//     socklen_t addr_len = sizeof(their_addr);

//     int res = 1;

//     while (0 < (res = GetInMsgU(sockfd, (struct sockaddr *)&their_addr, &addr_len)))
//     {
//         if (strcmp(inet_ntoa(their_addr.sin_addr), "127.0.0.1"))
//         {
//             puts("pong");
//             return res;
//         }

//         if (0 > SendOutMsgU(sockfd, (struct sockaddr *)&their_addr, addr_len, o_msg))
//         {
//             break;
//         }
//     }

//     return res;
// }

int ReadIncomingPackegs(int sockfd, const char *o_msg)
{
    struct sockaddr_in their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);

    int res = 1;

    if (0 >= (res = GetInMsgU(sockfd, (struct sockaddr *)&their_addr, &addr_len)))
    {
        return res;
    }
    if (strcmp(inet_ntoa(their_addr.sin_addr), "127.0.0.1"))
    {
        puts("pong");
        return res;
    }

    SendOutMsgU(sockfd, (struct sockaddr *)&their_addr, addr_len, o_msg);

    return res;
}