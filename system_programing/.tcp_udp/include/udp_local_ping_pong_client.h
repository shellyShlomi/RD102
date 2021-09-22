#ifndef ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H
#define ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H
#include "udp_local_ping_pong.h"

int ClientCreatSocket(addrinfo_t *servinfo, int *sockfd);
void ReadIncomingMsgFromServer(int sockfd, addrinfo_t *servinfo, const char *o_msg);

#endif /* ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H */
