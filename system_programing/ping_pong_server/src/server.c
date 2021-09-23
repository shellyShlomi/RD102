#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

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

    memset(&servaddr, 0, sizeof(servaddr));

    /* create listening TCP socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == server_fd)
    {
        perror("socket creation failed\n");

        return (EXIT_FAILURE);
    }

    TCPFillServerInfo(&servaddr, PORT, AF_INET, NULL);

    // binding server addr structure to server_fd
    if (-1 == bind(server_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        close(server_fd);
        perror("bind failed\n");
    }

    if (-1 == listen(server_fd, 10))
    {
        close(server_fd);
        printf("Listen failed'n");

        return (EXIT_FAILURE);
    }

    /* create UDP socket */
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (-1 == udp_fd)
    {
        close(server_fd);
        perror("socket creation failed\n");

        return (EXIT_FAILURE);
    }

    // binding server addr structure to udp sockfd
    if (-1 == bind(udp_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        close(server_fd);
        close(udp_fd);

        return (EXIT_FAILURE);
    }

    // clear the descriptor set
    FD_ZERO(&rset);

    // get maxfd
    maxfdp1 = max(server_fd, udp_fd) + 1;

    for (;;)
    {

        // set server_fd and udp_fd in readset
        FD_SET(server_fd, &rset);
        FD_SET(udp_fd, &rset);

        // select the ready descriptor
        nready = select(maxfdp1, &rset, NULL, NULL, NULL);

        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(server_fd, &rset))
        {
            len = sizeof(cliaddr);
            tcp_fd = accept(server_fd, (struct sockaddr *)&cliaddr, &len);

            if (-1 == tcp_fd)
            {
                close(server_fd);
                close(udp_fd);
                perror("accept failed\n");
            }

            TCPChatWithClient(tcp_fd, "pong");
          /*   if ((child_pid = fork()) == 0)
            {
                close(server_fd);
                bzero(buffer, sizeof(buffer));
                printf("Message From TCP client: ");
                read(tcp_fd, buffer, sizeof(buffer));
                puts(buffer);
                write(tcp_fd, (const char *)message, sizeof(buffer));
                close(tcp_fd);
                exit(0);
            } */
            close(tcp_fd);
        }
        // if udp socket is readable receive the message.
        if (FD_ISSET(udp_fd, &rset))
        {
            len = sizeof(cliaddr);
            bzero(buffer, sizeof(buffer));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udp_fd, buffer, sizeof(buffer), 0,
                         (struct sockaddr *)&cliaddr, &len);
            puts(buffer);
            sendto(udp_fd, (const char *)message, sizeof(buffer), 0,
                   (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        }
    }
}