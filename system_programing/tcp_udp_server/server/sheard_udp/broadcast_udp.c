#include "ping_pong.h"
#include "ping_pong_func.h"

#include "udp_local_ping_pong.h"

#include "udp_ping_pong_broadcast.h"

#define ARGC_VAL 4
#define ALLOW 1

void InitBroadcastData(broadcast_udp_t *elem, char *broadcastIP, char *sendString, int broadcastPort, int broadcastPermission)
{
    elem->broadcastIP = broadcastIP;     /* First arg:  broadcast IP address */
    elem->sendString = sendString;       /* Third arg:  string to broadcast */
    elem->broadcastPort = broadcastPort; /* Second arg:  broadcast port */
    elem->broadcastPermission = broadcastPermission;
    return;
}

void InitBroadcastAddr(struct sockaddr_in *broadcastAddr,
                       int sin_family, int sin_addr_s_add_broadcastIP, int sin_port)
{
    /* Construct local address structure */
    memset(broadcastAddr, 0, sizeof(struct sockaddr_in));        /* Zero out structure */
    broadcastAddr->sin_family = sin_family;                      /* Internet address family */
    broadcastAddr->sin_addr.s_addr = sin_addr_s_add_broadcastIP; /* Broadcast IP address */
    broadcastAddr->sin_port = sin_port;                          /* Broadcast port */
    return;
}

void ValidetUserData(int argc_val, char **argv_val)
{
    if (argc_val < ARGC_VAL) /* Test for correct number of parameters */
    {
        fprintf(stderr, "Usage:  %s <IP Address> <Port> <Send String>\n", argv_val[0]);
        return;
    }
    return;
}

void SendForEver(int sockfd, broadcast_udp_t *elem, struct sockaddr *broadcastAddr)
{

    while (1)
    {
        sleep(1);
        SendOutMsgU(sockfd, broadcastAddr, sizeof(struct sockaddr), elem->sendString);
    }

    return;
}
