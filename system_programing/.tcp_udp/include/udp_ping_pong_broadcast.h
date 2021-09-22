#ifndef ILRD_RD102_UDP_PING_PONG_BROADCAST_H
#define ILRD_RD102_UDP_PING_PONG_BROADCAST_H

#include "udp_local_ping_pong.h"

typedef struct broadcast_udp
{
    char *broadcastIP;
    char *sendString;
    int broadcastPort;
    int broadcastPermission;
} broadcast_udp_t;

void InitBroadcastData(broadcast_udp_t *elem, char *broadcastIP, char *sendString, int broadcastPort, int broadcastPermission);
void InitBroadcastAddr(struct sockaddr_in *broadcastAddr,
                       int sin_family, int sin_addr_s_add_broadcastIP, int sin_port);
void ValidetUserData(int argc_val, char **argv_val);

void SendForEver(int sockfd, broadcast_udp_t *elem, struct sockaddr *broadcastAddr);

#endif /* ILRD_RD102_UDP_PING_PONG_BROADCAST_H */
