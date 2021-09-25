#ifndef ILRD_RD102_TCP_PING_PONG_H
#define ILRD_RD102_TCP_PING_PONG_H

int GetInMsg(int sockfd);
int SendOutMsg(int sockfd, const char *msg);
int PrintTime(time_t time_to_p);

#endif /* ILRD_RD102_TCP_PING_PONG_H */
