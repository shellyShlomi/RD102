#define _POSIX_C_SOURCE 200112L

#include <time.h>
#include <asm/socket.h>
#include <sys/fcntl.h>
#include <sys/select.h>

#include "ping_pong.h"
#include "ping_pong_func.h"
#include "tcp_local_ping_pong.h"
#include "tcp_local_ping_pong_server.h"

#include "server.h"

#define GREEN ("\033[0;32m")
#define QUIT_MSG ("\033[0;31m I QUIT\033[0m")
#define B_RED ("\033[1;31m")
#define RED ("\033[0;31m")
#define CYAN ("\033[0;36m")
#define PONG_IO ("\033[0;35mPONG\033[0m")
#define RESET ("\033[0m")
#define _RESET_              \
    {                        \
        printf("%s", RESET); \
        printf("%s", "");    \
    }

#define BUFSIZE (100)

#define INTERVAL 7

static void PrintDiff(time_t start_t);

/********************************** CreatSocket **********************************/

int CreatTCPSocket(fd_t *sockfd)
{
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_STREAM, AI_PASSIVE);

    if ((res = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return (ERORR);
    }

    if (0 != BindClientToServer(servinfo, sockfd))
    {
        perror("BindClientToServer");

        return (ERORR);
    }

    fcntl(*sockfd, F_SETFD, O_NONBLOCK);

    freeaddrinfo(servinfo);
    if (0 != ListenToPort(*sockfd))
    {
        perror("ListenToPort ");
        return (ERORR);
    }

    return (EXIT_SUCCESS);
}

int CreatUDPSocket(fd_t *sockfd)
{
    struct addrinfo hints = {0}, *servinfo = NULL;
    int res = 0;

    CreatHints(&hints, AF_INET, SOCK_DGRAM, AI_PASSIVE);

    if ((res = getaddrinfo(NULL, SERVERPORT, &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
        return (0);
    }

    if (0 != BindClientToServer(servinfo, sockfd))
    {
        return (0);
    }

    freeaddrinfo(servinfo);
    return (EXIT_SUCCESS);
}

int GetIncomingPackegsStdin(const char *o_msg, const char *exit_msg, const char *si_msg)
{
    char buf[BUFSIZE] = {0};

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    fcntl(STDIN_FILENO, F_SETFL, O_ASYNC);

    _RESET_;
    if (NULL != fgets(buf, sizeof(buf), stdin))
    {
        if (0 == strncasecmp(buf, exit_msg, strlen(exit_msg)))
        {
            printf("%s", RED);
            printf(QUIT_MSG);
            _RESET_;

            return (QUIT);
        }
        else if (0 == strncasecmp(buf, si_msg, strlen(si_msg)))
        {
            printf("%s ", o_msg);
            printf("send at : ");
            PrintTime(time(NULL));
            printf("\n");
            _RESET_;
        }
    }
    printf("%s", RESET);
    return (EXIT_SUCCESS);
}

int ServerGetIncomingPackegsTCP(int sockfd, const char *o_msg, const char *exit_msg, const char *si_msg)
{
    int res = 1;
    int res_io = 1;
    int res_sand_msg = 1;
    int ready = 0;

    time_t start_t = time(NULL);

    fd_set rset = {0};
    struct timeval time_out = {0};

    fcntl(sockfd, F_SETFL, O_ASYNC);

    while ((0 < res) && (-1 != res_sand_msg) && QUIT != res_io)
    {
        int maxfd = 0;
        FD_ZERO(&rset);
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(sockfd, &rset);

        maxfd = max(maxfd, sockfd) + 1;
        maxfd = max(maxfd, STDIN_FILENO) + 1;

        time_out.tv_sec = INTERVAL;

        if (ERORR == (ready = select(maxfd, &rset, NULL, NULL, &time_out)))
        {
            perror("select");
            break;
        }
        if (!FD_ISSET(STDIN_FILENO, &rset) && !FD_ISSET(sockfd, &rset) && res != 0)
        {
            printf("\n\033[1;0mTimed Out!\033[0m\n");
            printf("privius PING recv at :\t");
            PrintTime(start_t);
            PrintDiff(start_t);
            continue;
        }
        if (FD_ISSET(STDIN_FILENO, &rset))
        {
            start_t = time(NULL);
            _RESET_;
            res_io = GetIncomingPackegsStdin(PONG_IO, exit_msg, si_msg);
            continue;
        }
        if (FD_ISSET(sockfd, &rset))
        {
            start_t = time(NULL);
            printf("%s", CYAN);
            res = GetInMsg(sockfd);
            if (0 > res)
            {
                break;
            }
            sleep(1);
            _RESET_;
            printf("\n");
            
            if (-1 == (res_sand_msg = SendOutMsg(sockfd, o_msg)))
            {
                perror("SendOutMsg");
                break;
            }
        }
    }
    res = (res_io == QUIT) ? QUIT : res;
    return (res);
}

void SetFdArray(fd_t *fd_arr, size_t size, fd_t *fd, size_t idx)
{
    size_t i = 0;
    for (i = idx; i < size; ++i)
    {
        fd_arr[i] = *(fd + i - idx);
    }

    return;
}

void CleanUp(fd_t *fd_arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        close(fd_arr[i]);
    }

    return;
}

int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

static void PrintDiff(time_t start_t)
{
    time_t now = time(NULL);
    time_t diff = difftime(now, start_t);
    char *color_start = RESET;
    char *color_num = GREEN;

    if (diff >= 7)
    {
        color_start = B_RED;
        color_num = B_RED;
    }
    printf("Time now :\t\t");
    PrintTime(now);
    printf("%srecv timediff :  \t%s%ld%s\n", color_start, color_num, diff, RESET);
    printf("%s", "\n");

    return;
}