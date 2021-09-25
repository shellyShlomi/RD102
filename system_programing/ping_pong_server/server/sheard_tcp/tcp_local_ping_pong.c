
#define _POSIX_C_SOURCE 200112L
#include <time.h>

#include "ping_pong.h"
#include "ping_pong_func.h"

#include "tcp_local_ping_pong.h"
#define MAXBUFLEN 100

/* get sockaddr, IPv4 or IPv6:*/

int GetInMsg(int sockfd)
{
    int numbytes = 0;
    char buf[MAXBUFLEN] = {0};

    if ((numbytes = recv(sockfd, buf, sizeof(buf), 0)) == -1)
    {
        perror("recv");
        return (numbytes);
    }
    else if (0 == numbytes)
    {
        return (numbytes);
    }

    buf[numbytes] = '\0';
    printf("%s ", buf);

    return (numbytes);
}

int SendOutMsg(int sockfd, const char *msg)
{
    int res = 0;
    if ((res = send(sockfd, msg, strlen(msg), 0)) == -1)
    {
        perror("sendto");
    }

    return (res);
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