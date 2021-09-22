#ifndef ILRD_RD102_UDP_PING_PONG_CLIENT_H
#define ILRD_RD102_UDP_PING_PONG_CLIENT_H

#include "ping_pong.h"

#include "udp_local_ping_pong.h"

int ClientCreatSocketU(addrinfo_t *servinfo, int *sockfd);
void ReadIncomingMsgFromServer(int sockfd, addrinfo_t *servinfo, const char *o_msg);

#endif /* ILRD_RD102_UDP_PING_PONG_CLIENT_H */
