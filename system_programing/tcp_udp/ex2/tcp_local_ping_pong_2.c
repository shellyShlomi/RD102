
/*  Developer: Shelly Shlomi;									*
 *  Status:done;                                                *
 *  Date Of Creation:20.09.21;									*
 *  Date Of Approval:20.09.21;									*
 *  Approved By:                                                *	 
 *  Description:  a stream sockets "server side" localy         *
 *                localaly                                      */

#include "tcp_local_ping_pong_server.h"
#define SERVERPORT "4951" // the port users will be connecting to
#define MAXBUFLEN 10
#define MSG "PONG"


static void PingPongUDPServer();

int main(void)
{
    PingPongUDPServer();

    return 0;
}

static void PingPongUDPServer()
{

    int sockfd = 0, new_sfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_STREAM, 0);

    if ((res = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return;
    }

    if (0 != BindClientToServer(servinfo, &sockfd))
    {
        perror("BindClientToServer");

        return;
    }
    freeaddrinfo(servinfo);

    if (0 != ListenToPort(sockfd))
    {
        perror("ListenToPort ");
        return;
    }
    printf("server: Listen To Port %s\n", SERVERPORT);

    if (0 > (new_sfd = AcceptConection(sockfd)))
    {
        perror("AcceptConection");
        return;
    }
        
    ReadIncomingPackegs(new_sfd, MSG);
    close(new_sfd);

    return;
}

