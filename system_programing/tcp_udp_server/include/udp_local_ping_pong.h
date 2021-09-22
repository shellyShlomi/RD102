#ifndef ILRD_RD102_UDP_PING_PONG_H
#define ILRD_RD102_UDP_PING_PONG_H

#include "ping_pong.h"

int GetInMsgU(int sockfd, struct sockaddr *their_addr, socklen_t *addr_len);
int SendOutMsgU(int sockfd, struct sockaddr *their_addr, socklen_t addr_len, const char *msg);


#endif /* ILRD_RD102_UDP_PING_PONG_H */
