/*  Developer: Shelly Shlomi;									*
 *  Status:done;                                                *
 *  Date Of Creation:20.09.21;									*
 *  Date Of Approval:20.09.21;									*
 *  Approved By:                                                *	 
 *  Description:  a datagram sockets broadcast to the local     *
 *                network                                       */

#include "udp_ping_pong_broadcast.h"
#define ALLOW 1

static void UDPBroadcastPingPong(int num_of_data, char *data[]);

int main(int argc, char *argv[])
{
    UDPBroadcastPingPong(argc, argv);

    return 0;
}

static void UDPBroadcastPingPong(int num_of_data, char *data[])
{

    int sock;                         /* Socket */
    broadcast_udp_t elem;             /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */

    ValidetUserData(num_of_data, data);
    InitBroadcastData(&elem, data[1], data[3], atoi(data[2]), ALLOW);

    /* Create socket for sending/receiving datagrams */
    if ((CreatSockt(&sock, AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket() failed");
    }

    SetSocket(sock, SOL_SOCKET, SO_BROADCAST, (void *)&elem.broadcastPermission, sizeof(elem.broadcastPermission));

    InitBroadcastAddr(&broadcastAddr, AF_INET, inet_addr(elem.broadcastIP), htons(elem.broadcastPort));

    SendForEver(sock, &elem, (struct sockaddr *)&broadcastAddr);
    return;

    return;
}
