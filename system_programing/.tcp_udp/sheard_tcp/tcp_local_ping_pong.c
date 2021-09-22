
#include "tcp_local_ping_pong.h"
#define MAXBUFLEN 100

/* get sockaddr, IPv4 or IPv6:*/
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

int GetInMsg(int sockfd)
{
    int numbytes = 0;
    char buf[MAXBUFLEN] = {0};

    if ((numbytes = recv(sockfd, buf, sizeof(buf), 0)) == -1)
    {
        perror("recvfrom");
        return (numbytes);
    }

    buf[numbytes] = '\0';
    printf("%s\n", buf);

    return (numbytes);
}

int SendOutMsg(int sockfd, const char *msg)
{
    if ((send(sockfd, msg, strlen(msg), 0)) == -1)
    {
        perror("sendto");
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
