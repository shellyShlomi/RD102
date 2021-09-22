

#include "udp_local_ping_pong_client.h"

#define MYPORT "8000" // the port users will be connecting to
#define MAXBUFLEN 100
#define MSG "PING"

int main(int argc, char *argv[])
{
    int sockfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;
    (void) argc;

    CreatHints(&hints, AF_INET, SOCK_DGRAM, 0);

    if ((res = getaddrinfo(argv[1], MYPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return 1;
    }

    if (2 == ClientCreatSocket(servinfo, &sockfd))
    {
        return 1;
    }

    ReadIncomingMsgFromServer(sockfd, servinfo, MSG);

    freeaddrinfo(servinfo);

    close(sockfd);

    return 0;
}