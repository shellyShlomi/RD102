
#include "ping_pong.h"
#include "ping_pong_func.h"


void *GetInAddr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void CreatHints(addrinfo_t *hints, int ai_family, int ai_socktype, int ai_flags)
{
    memset(hints, 0, sizeof(addrinfo_t));
    hints->ai_family = ai_family;
    hints->ai_socktype = ai_socktype;
    hints->ai_flags = ai_flags;

    return;
}

int CreatSockt(int *sockfd, int ai_family, int ai_socktype, int ai_protocol)
{
    if ((*sockfd = socket(ai_family, ai_socktype, ai_protocol)) == -1)
    {
        close(*sockfd);
        perror("socket");
        return (1);
    }
    return (0);
}
int SetSocket(int sockfd, int level, int opt_name, void *opt_val, socklen_t opt_len)
{
    if (setsockopt(sockfd, level, opt_name, opt_val, opt_len) < 0)
    {
        perror("setsockopt");
        return (-1);
    }

    return (0);
}
