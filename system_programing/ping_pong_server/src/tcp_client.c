

#include "tcp_local_ping_pong_client.h"

#define MYPORT "8000" // the port users will be connecting to
#define MAXBUFLEN 100
#define MSG "PING"

static void PingPongUDPClient();

int main(int argc, char *argv[])
{
    (void)argc;
    PingPongUDPClient(argv[1]);
    return 0;
}

static void PingPongUDPClient(const char *ip)
{
    int sockfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_STREAM, AI_PASSIVE);

    if ((res = getaddrinfo(ip, MYPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return;
    }

    if (0 != ClientCreatSocket(servinfo, &sockfd))
    {
        perror("ClientCreatSocket");

        return;
    }

    if (0 != ConnectSockt(sockfd, servinfo, servinfo->ai_addrlen))
    {
        perror("client: ConnectSockt");
        close(sockfd);
        return;
    }

    ReadIncomingMsgFromServerTcp(sockfd, MSG);

    freeaddrinfo(servinfo);

    close(sockfd);

    return;
}
