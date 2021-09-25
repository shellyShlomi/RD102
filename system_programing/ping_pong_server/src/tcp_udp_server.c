#define _POSIX_C_SOURCE 200112L

#include <time.h>
#include <sys/select.h>
#include <sys/fcntl.h>
#include "ping_pong_func.h"
#include "server.h"

#include "udp_local_ping_pong_server.h"
#include "tcp_local_ping_pong_server.h"

#define RESET ("\033[0m")
#define GREEN ("\033[0;32m")

#define QUIT_MSG ("quit\n")
#define PING ("ping\n")
#define PONG ("PONG")
#define PONG_IO ("\033[0;35mPONG\033[0m")

#define MAXLINE (1024)
#define SIZE (2)

#define INTERVAL 7

int main()
{
    int new_tcp_fd = 0;
    int maxfd = 0;

    fd_set rset = {0};

    fd_t tcpfd = 0;
    fd_t udpfd = 0;

    fd_t fdarr[SIZE] = {0};
    SetFdArray(fdarr, SIZE, &tcpfd, 0);
    if (ERORR == CreatTCPSocket(&tcpfd))
    {
        return (ERORR);
    }

    if (ERORR == CreatUDPSocket(&udpfd))
    {
        return (ERORR);
    }

    while (ON)
    {
        struct timeval time_out = {INTERVAL, 0};
        time_out.tv_sec = INTERVAL;

        /* set server_fd and udp_fd in readset */
        FD_ZERO(&rset);
        FD_SET(tcpfd, &rset);
        FD_SET(udpfd, &rset);
        FD_SET(STDIN_FILENO, &rset);

        /* get maxfd */
        maxfd = max(maxfd, udpfd) + 1;
        maxfd = max(maxfd, tcpfd) + 1;
        maxfd = max(maxfd, STDIN_FILENO) + 1;

        if (!select(maxfd, &rset, NULL, NULL, &time_out))
        {
            printf("\nTimed Out! - ");
            PrintTime(time(NULL));
        }

        if (FD_ISSET(udpfd, &rset)) /*udp*/
        {
            if (0 > ReadIncomingPackegsUDP(udpfd, PONG))
            {
                perror("recvfrom");
            }

            continue;
        }

        if (FD_ISSET(0, &rset)) /* stdin */
        {
            if (QUIT == GetIncomingPackegsStdin(PONG_IO, QUIT_MSG, PING))
            {
                CleanUp(fdarr, SIZE);
                return (1);
            }
            continue;
        }
        if (FD_ISSET(tcpfd, &rset)) /*tcp*/
        {
            new_tcp_fd = AcceptConection(tcpfd);

            if (-1 == new_tcp_fd)
            {
                CleanUp(fdarr, SIZE);
                perror("accept failed\n");
                return (1);
            }

            if (QUIT == ServerGetIncomingPackegsTCP(new_tcp_fd, PONG, QUIT_MSG, PING))
            {
                CleanUp(fdarr, SIZE);
                return (0);
            }

            CleanUp(&new_tcp_fd, 1);

            printf("selectserver: socket %d hung up\n", new_tcp_fd); /* connection closed*/

            continue;
        }
        maxfd = 0;
    }

    return (0);
}
