#ifndef ILRD_RD102_UDP_PING_PONG_SERVER_H
#define ILRD_RD102_UDP_PING_PONG_SERVER_H
#include "ping_pong.h"

#include "udp_local_ping_pong.h"

int ReadIncomingPackegsUDP(int sockfd, const char *o_msg);

#endif /* ILRD_RD102_UDP_PING_PONG_SERVER_H */
