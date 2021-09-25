#ifndef ILRD_RD102_SERVER_H
#define ILRD_RD102_SERVER_H

#include "ping_pong.h"

#define QUIT (-100)
#define SERVERPORT ("8000") /* the port users will be connecting to */

#define ERORR (-1) /* must be negative! */
#define ON (1)

typedef int fd_t;

int CreatTCPSocket(fd_t *sockfd);
int CreatUDPSocket(fd_t *sockfd);

int GetIncomingPackegsStdin(const char *o_msg, const char *exit_msg, const char *si_msg);
int ServerGetIncomingPackegsTCP(int sockfd, const char *o_msg, const char *exit_msg, const char *si_msg);

void SetFdArray(fd_t *fd_arr, size_t size, fd_t *fd, size_t idx);
void CleanUp(fd_t *fd_arr, size_t size);
int max(int x, int y);

#endif /* ILRD_RD102_SERVER_H */
