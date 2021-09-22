#ifndef ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H
#define ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H
#include "tcp_local_ping_pong.h"

int ClientCreatSocket(addrinfo_t *servinfo, int *sockfd);
int ConnectSockt(int sockfd, addrinfo_t *p, int ai_addrlen);
void ReadIncomingMsgFromServer(int sockfd, const char *o_msg);

#endif /* ILRD_RD102_TCP_UDP_PING_PONG_CLIENT_H */
