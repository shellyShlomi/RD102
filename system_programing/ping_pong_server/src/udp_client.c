
#define _POSIX_C_SOURCE 200112L

#include "ping_pong.h"
#include "ping_pong_func.h"
#include "udp_local_ping_pong.h"
#include "udp_local_ping_pong_client.h"

#define MYPORT "8000" 
#define MAXBUFLEN 100
#define MSG "\033[0;33mPING \033[0m"

static void PingPongUDPClient(const char *data);

int main(int argc, char *argv[])
{
    (void) argc;
    PingPongUDPClient(argv[1]);
    return (0);
}


static void PingPongUDPClient(const char *data)
{
    int sockfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);

    if ((res = getaddrinfo(data, MYPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return ;
    }

    if (2 == ClientCreatSocketU(servinfo, &sockfd))
    {
        return ;
    }

    ReadIncomingMsgFromServer(sockfd, servinfo, MSG);

    freeaddrinfo(servinfo);

    close(sockfd);

    return ;
}