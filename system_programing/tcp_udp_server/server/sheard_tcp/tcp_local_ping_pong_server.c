
#include "ping_pong.h"
#include "ping_pong_func.h"

#include "tcp_local_ping_pong.h"
#include "tcp_local_ping_pong_server.h"

#include <asm/socket.h>

#define MAXBUFLEN 100
#define BACKLOG 10 // how many pending connections queue will hold

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
    int yes = 1;

    if (0 != CreatSockt(sockfd, servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol))
    {
        perror("CreatSockt");
        return (1);
    }

    if (SetSocket(*sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &yes,
                  sizeof(int)) < 0)
    {
        perror("SetSocket");
        return (1);
    }

    if (0 > BindClient(*sockfd, servinfo->ai_addr, servinfo->ai_addrlen))
    {
        perror("BindClient");
        return 1;
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

int ListenToPort(int sockfd)
{
    if (listen(sockfd, BACKLOG) < 0)
    {
        perror("listen");
        return (1);
    }
    return (0);
}

int AcceptConection(int sockfd)
{
    int new_fd = 0;
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);

    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_len)) == -1)
    {
        perror("accept");
        return (new_fd);
    }

    return (new_fd);
}

int ReadIncomingPackegsTcp(int sockfd, const char *o_msg)
{
    int res = 0;

    while (0 < GetInMsg(sockfd))
    {
        res = SendOutMsg(sockfd, o_msg);
        if (-1 == res)
        {
            perror("SendOutMsg");
            return (res);
        }
    }

    return (res);
}

// int ReadIncomingPackegsTcp1(int sockfd, const char *o_msg,const char * quit_msg)
// {
//     int res = 0;
//     char buf[MAXBUFLEN] = {0};

//     while (0 < GetInMsg(sockfd) && strcmp(buf, quit_msg))
//     {
//         if (-1 == (res = SendOutMsg(sockfd, o_msg)))
//         {
//             break;
//         }
//         read(STDIN_FILENO, buf, strlen(quit_msg));
//     }

//     return (res);
// }
