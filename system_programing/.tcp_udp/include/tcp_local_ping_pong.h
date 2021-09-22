#ifndef ILRD_RD102_TCP_UDP_PING_PONG_H
#define ILRD_RD102_TCP_UDP_PING_PONG_H


#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

/* Define the PORT to be :4951, the port users will be connecting to*/

typedef struct addrinfo addrinfo_t;

void *GetInAddr(struct sockaddr *sa);
void CreatHints(addrinfo_t *hints, int ai_family, int ai_socktype, int ai_flags);
int CreatSockt(int *sockfd, int ai_family, int ai_socktype, int ai_protocol);
int GetInMsg(int sockfd);
int SendOutMsg(int sockfd, const char *msg);

int SetSocket(int sockfd, int level, int opt_name, void *opt_val, socklen_t opt_len);


#endif /* ILRD_RD102_TCP_UDP_PING_PONG_H */
