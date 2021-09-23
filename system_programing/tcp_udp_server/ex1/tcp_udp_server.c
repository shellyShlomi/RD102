

#include "ping_pong.h"

#include <sys/select.h>
#include <sys/fcntl.h>

#include "ping_pong_func.h"

#include "udp_local_ping_pong_server.h"
#include "tcp_local_ping_pong_server.h"

#define RED ("\033[0;31m")
#define GREEN ("\033[0;32m")
#define CYAN ("\033[0;36m")
#define PURPLE ("\033[0;35m")

#define RESET ("\033[0m")

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
    int tcp_fd = -1;
    int maxfdp1 = 0;

    fd_set rset;
    void sig_chld(int);

    int sockfd = 0;
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_STREAM, AI_PASSIVE);

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

    fcntl(sockfd, F_SETFL, O_NONBLOCK);
    fcntl(sockfd, F_SETFL, O_ASYNC);

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


    while (1)
    {

        // get maxfd
        maxfdp1 = max(sockfd, udpfd) + 1;
        maxfdp1 = max(maxfdp1, STDIN_FILENO) + 1;
        // set server_fd and udp_fd in readset
        FD_ZERO(&rset);
        FD_SET(sockfd, &rset);
        FD_SET(udpfd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        struct timeval time_out = {7, 0};

        time_out.tv_sec = 7;

        if (!select(maxfdp1, &rset, NULL, NULL, &time_out))
        {
            puts("Timed Out!");
        }

        if (FD_ISSET(sockfd, &rset)) /*tcp*/
        {
            tcp_fd = AcceptConection(sockfd);
            if (-1 == tcp_fd)
            {
                close(sockfd);
                close(udpfd);
                perror("accept failed\n");
            }

            puts(CYAN);
            ReadIncomingPackegsTcp(tcp_fd, "pong");
            puts(RESET);

            close(tcp_fd);
            printf("selectserver: socket %d hung up\n", tcp_fd); /* connection closed*/

            continue;
        }

        if (FD_ISSET(udpfd, &rset)) /*udp*/
        {
            puts(GREEN);
            if (0 > ReadIncomingPackegs(udpfd, "pong"))
            {
                perror("recvfrom");
            }

            puts(RESET);
            continue;
        }

        if (FD_ISSET(0, &rset)) //stdin
        {
            if (QUIT == ReadIncomingPackegsStdIn(0, "pong"))
            {
                close(sockfd);
                close(udpfd);
                return 0;
            }

            continue;
        }
        FD_SET(sockfd, &rset);
        FD_SET(udpfd, &rset);
        FD_SET(STDIN_FILENO, &rset);
    }
    return 0;
}

int ReadIncomingPackegsStdIn(int sockfd, const char *o_msg)
{
    char buf[100] = {0};

    if (0 < read(sockfd, buf, sizeof(buf)))
    {

        if (0 == strncmp(buf, "quit\n", 5))
        {
            puts(RED);
            puts("I quit!");
            puts(RESET);

            return QUIT;
        }
        else if (0 == strncmp(buf, "ping\n", 5))
        {
            puts(PURPLE);
            puts(o_msg);
            puts(RESET);
        }
    }

    return EXIT_SUCCESS;
}
