#define _POSIX_C_SOURCE 200112L
#include <sys/fcntl.h>

#include "ping_pong.h"
#include "ping_pong_func.h"
#include "udp_local_ping_pong.h"

#include "udp_local_ping_pong_server.h"

int ReadIncomingPackegsUDP(int sockfd, const char *o_msg)
{
    struct sockaddr_in their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);

    int res = 1;
    fcntl(STDIN_FILENO, F_SETFD, O_ASYNC);

    if (0 >= (res = GetInMsgU(sockfd, (struct sockaddr *)&their_addr, &addr_len)))
    {
        return res;
    }
    printf("\n");

    if (strcmp(inet_ntoa(*(struct in_addr *)GetInAddr((struct sockaddr *)&their_addr)), "127.0.0.1"))
    {
        puts(o_msg);
        return res;
    }

    SendOutMsgU(sockfd, (struct sockaddr *)&their_addr, addr_len, o_msg);

    return res;
}