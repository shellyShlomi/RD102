
/*  Developer: Shelly Shlomi;									*
 *  Status:done;                                                *
 *  Date Of Creation:20.09.21;									*
 *  Date Of Approval:20.09.21;									*
 *  Approved By:                                                *	 
 *  Description:  a datagram sockets "server side" localy       *
 *                localaly                                      */

#include "udp_local_ping_pong_server.h"
#define SERVERPORT "8000" // the port users will be connecting to
#define MSG "PONG"

static void PingPongUDPServer();

int main(void)
{
    PingPongUDPServer();

    return 0;
}

static void PingPongUDPServer()
{

    int sockfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);

    if ((res = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return;

    }

    /* loop through all the results and bind to the first we can*/

    if (2 == BindClientToServer(servinfo, &sockfd))
    {
        return;
    }
    freeaddrinfo(servinfo);

    printf("server: waiting to recvfrom...\n");
    ReadIncomingPackegs(sockfd, MSG);
    close(sockfd);

    return;
}

static void PingPongUDPServer();
