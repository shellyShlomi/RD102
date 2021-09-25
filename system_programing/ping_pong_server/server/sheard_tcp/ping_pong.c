#define _POSIX_C_SOURCE 200112L
#include <time.h>
#include <asm/socket.h>
#include <sys/fcntl.h>

#include "ping_pong.h"
#include "ping_pong_func.h"


#define LOOP break
#define TO_LOOP(x)    \
    {                 \
        if (x)        \
        {             \
            continue; \
        }             \
    }

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
size_t GetRand(size_t from, size_t to)
{
    time_t t;

    srand((unsigned)time(&t));

    return ((rand() % (to - from) + from));
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

int BindSetSocketClientToServer(addrinfo_t *servinfo, int *sockfd)
{
    /* loop through all the results and bind to the first we can */
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


int PrintTime(time_t time_to_p)
{
    int hours, minutes, seconds;
    struct tm *local = 0;

    local = localtime(&time_to_p);

    hours = local->tm_hour;  /* get hours since midnight (0-23)*/
    minutes = local->tm_min; /* get minutes passed after the hour (0-59)*/
    seconds = local->tm_sec; /* get seconds passed after a minute (0-59)*/

    printf(" %02d:%02d:%02d \n", hours, minutes, seconds);

    return (EXIT_SUCCESS);
}