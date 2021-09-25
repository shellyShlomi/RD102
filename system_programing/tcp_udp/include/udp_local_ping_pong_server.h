#ifndef ILRD_RD102_TCP_UDP_PING_PONG_SERVER_H
#define ILRD_RD102_TCP_UDP_PING_PONG_SERVER_H

#include "udp_local_ping_pong.h"

int BindClient(int sockfd, const struct sockaddr *ai_addr, int ai_addrlen);
int BindClientToServer(addrinfo_t *servinfo, int *sockfd);
void ReadIncomingPackegs(int sockfd, const char *o_msg);



#endif /* ILRD_RD102_TCP_UDP_PING_PONG_SERVER_H */
