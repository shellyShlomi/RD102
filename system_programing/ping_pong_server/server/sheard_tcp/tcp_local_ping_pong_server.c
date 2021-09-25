#define _POSIX_C_SOURCE 200112L

#include "ping_pong.h"
#include "ping_pong_func.h"

#include "tcp_local_ping_pong.h"
#include "tcp_local_ping_pong_server.h"

#define MAXBUFLEN (100)
#define BACKLOG (10)



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

int ReadIncomingPackegsTCP(int sockfd, const char *o_msg)
{
    int res = 0;

    while (0 < (res = GetInMsg(sockfd)))
    {
        if (-1 == SendOutMsg(sockfd, o_msg))
        {
            perror("SendOutMsg");
            break;
        }
    }

    return (res);
}


