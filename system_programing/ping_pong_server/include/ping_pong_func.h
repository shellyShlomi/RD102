#ifndef ILRD_RD102_PING_PONG_FUNC_H
#define ILRD_RD102_PING_PONG_FUNC_H

#include "ping_pong.h"

void *GetInAddr(struct sockaddr *sa);
void CreatHints(addrinfo_t *hints, int ai_family, int ai_socktype, int ai_flags);
int CreatSockt(int *sockfd, int ai_family, int ai_socktype, int ai_protocol);
int SetSocket(int sockfd, int level, int opt_name, void* opt_val, socklen_t opt_len);
size_t GetRand(size_t from, size_t to);
int BindClient(int sockfd, const struct sockaddr *ai_addr, int ai_addrlen);
int BindClientToServer(addrinfo_t *servinfo, int *sockfd);
int BindSetSocketClientToServer(addrinfo_t *servinfo, int *sockfd);

#endif /* ILRD_RD102_PING_PONG_FUNC_H */
