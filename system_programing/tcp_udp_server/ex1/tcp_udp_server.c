

#define _POSIX_C_SOURCE 200112L

#include <sys/select.h>

#include <strings.h>

#include "ping_pong_func.h"

#include "udp_local_ping_pong_server.h"
#include "tcp_local_ping_pong_server.h"
#include "udp_local_ping_pong_client.h"

#define PORT 8000
#define QUIT 10
#define MAXLINE 1024
#define SERVERPORT "8000" // the port users will be connecting to
int ReadIncomingPackegsStdIn(int sockfd, const char *o_msg);

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int server_fd = 0;
    int tcp_fd = 0;
    int udp_fd = 0;
    int nready = 0;
    int maxfdp1 = 0;
    char buffer[MAXLINE];

    pid_t child_pid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    char *message = "Hello Client";
    void sig_chld(int);

    int sockfd = 0, new_sfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_STREAM, 0);

    if ((res = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return 0;
    }

    if (0 != BindClientToServer(servinfo, &sockfd))
    {
        perror("BindClientToServer");

        return 0;
    }
    freeaddrinfo(servinfo);

    if (0 != ListenToPort(sockfd))
    {
        perror("ListenToPort ");
        return 0;
    }
    int udpfd = 0;
    struct addrinfo hints_udp = {0}, *serudp = NULL;
    int res_udp = 0;

    CreatHints(&hints_udp, AF_INET, SOCK_DGRAM, AI_PASSIVE);

    if ((res_udp = getaddrinfo(NULL, SERVERPORT, &hints_udp, &serudp)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res_udp));
        return 0;
    }

    /* loop through all the results and bind to the first we can*/

    if (0 != BindClientToServer(serudp, &udpfd))
    {
        return 0;
    }
    freeaddrinfo(serudp);

    // clear the descriptor set
    FD_ZERO(&rset);

    // get maxfd
    maxfdp1 = max(sockfd, udpfd) + 1;

    for (;;)
    {

        // set server_fd and udp_fd in readset
        FD_SET(sockfd, &rset);
        FD_SET(udpfd, &rset);
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(STDOUT_FILENO, &rset);

        // select the ready descriptor
        nready = select(maxfdp1, &rset, NULL, NULL, NULL);

        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(sockfd, &rset))//tcp
        {
            len = sizeof(cliaddr);
            tcp_fd = AcceptConection(sockfd);

            if (-1 == tcp_fd)
            {
                close(sockfd);
                close(udpfd);
                perror("accept failed\n");
            }
            ReadIncomingPackegsTcp(tcp_fd, "pong");

            close(tcp_fd);
        }
        // if udp socket is readable receive the message.
        if (FD_ISSET(udpfd, &rset))//udp
        {
            ReadIncomingPackegs(udpfd, "pong");
        }

        if (FD_ISSET(0, &rset))//stdin
        {
            res = ReadIncomingPackegsStdIn(0, "pong");
            if (QUIT == res)
            {
                close(sockfd);
                close(udpfd);
                close(tcp_fd);
                return;
            }
        }
    }
}

int ReadIncomingPackegsStdIn(int sockfd, const char *o_msg)
{
    char buf[100] = {0};
    int i = 0;
    struct sockaddr_storage their_addr = {0};
    socklen_t addr_len = sizeof(their_addr);
    int numbytes = 0;

    numbytes = read(sockfd, buf, sizeof(buf));
    sleep(1);
    buf[numbytes] = '\n';
    if (0 == strncmp(buf, "quit", 4))
    {
        puts("I quit!");
        return QUIT;
    }
    else if (0 == strncmp(buf, "ping", 4))
    {
        puts("stdin pong!");
    }

    return EXIT_SUCCESS;
}
