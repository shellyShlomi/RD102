#ifndef ILRD_RD102_PING_PONG_FUNC_H
#define ILRD_RD102_PING_PONG_FUNC_H

#include "ping_pong.h"

void *GetInAddr(struct sockaddr *sa);
void CreatHints(addrinfo_t *hints, int ai_family, int ai_socktype, int ai_flags);
int CreatSockt(int *sockfd, int ai_family, int ai_socktype, int ai_protocol);
int SetSocket(int sockfd, int level, int opt_name, void* opt_val, socklen_t opt_len);

#endif /* ILRD_RD102_PING_PONG_FUNC_H */
