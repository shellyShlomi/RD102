/***************************************************************
* Developer: Ohad Ezra
* Status: Approved
* Reviewer: Shelly
* Group: OL102
* date: 29.7.21
* description: Implementation of kingt tour problem with backtracking
               and warnsdorff's algorithm
******************************************************************/

#include <pthread.h>   /* pthread_create */
#include <stdatomic.h> /* atomic_exchange */
#include <unistd.h>    /* sleep */
#include <stdlib.h>    /* qsort */
#include <assert.h>    /* assert */

#include "bit_array.h"
#include "knights_tour.h"

#define BOARD_AXIS (8)
#define FIVE_MINUTE (300)
#define BOARD_SIZE (64)
#define MAX_SIZE (~((bit_arr_t)0))

typedef struct warnsdorff
{
    char rank;
    char position;
} warnsdorff_t;

static atomic_int is_timeout = 0;

/*backtracking*/
static char GetNextAviableStep(bit_arr_t chess_board, char curr_position, size_t index);
static int KnightTour(bit_arr_t chess_board, char curr_position, char path[BOARD_SIZE]);

static int KnightTourWarndorff(bit_arr_t chess_board, char curr_position, char path[BOARD_SIZE]);
static void UpdateRank(warnsdorff_t *array, bit_arr_t chess_board, char curr_position);
static char GetDegree(bit_arr_t chess_board, char lut[][BOARD_AXIS], size_t row);
static int Compare(const void *data1, const void *data2);

static void *TimeOut(void *arg);
/****************************backtracking impl*********************************/

int CreateTour(char start_position, char path[BOARD_SIZE])
{
    pthread_t thread = 0;
    bit_arr_t chess_board = 0;
    int status = -1;

    if (0 != pthread_create(&thread, NULL, TimeOut, NULL))
    {
        return (FAILED);
    }

    status = KnightTour(chess_board, start_position, path);

    if (0 != pthread_cancel(thread))
    {
        return (FAILED);
    }

    return (status);
}

static int KnightTour(bit_arr_t chess_board, char curr_position, char path[BOARD_SIZE])
{
    size_t i = 0;
    char next_location = -1;
    int status = FAILED;

    path[BitArrCountOn(chess_board)] = curr_position;

    chess_board = BitArrSetOn(chess_board, curr_position);

    if (!(MAX_SIZE ^ chess_board))
    {
        return (SUCCESS);
    }

    if (is_timeout)
    {
        return (TIME_OUT);
    }

    for (i = 0; i < BOARD_AXIS && SUCCESS != status && TIME_OUT != status; ++i)
    {
        next_location = GetNextAviableStep(chess_board, curr_position, i);

        if (-1 != next_location)
        {
            status = KnightTour(chess_board, next_location, path);
        }
    }

    return (status);
}

static char GetNextAviableStep(bit_arr_t chess_board, char curr_position, size_t index)
{

    static char lut[BOARD_SIZE][BOARD_AXIS] = {{10, 17, -1, -1, -1, -1, -1, -1},
                                               {11, 18, 16, -1, -1, -1, -1, -1},
                                               {12, 19, 17, 8, -1, -1, -1, -1},
                                               {13, 20, 18, 9, -1, -1, -1, -1},
                                               {14, 21, 19, 10, -1, -1, -1, -1},
                                               {15, 22, 20, 11, -1, -1, -1, -1},
                                               {-1, 23, 21, 12, -1, -1, -1, -1},
                                               {-1, -1, 22, 13, -1, -1, -1, -1},
                                               {18, 25, -1, -1, -1, -1, -1, 2},
                                               {19, 26, 24, -1, -1, -1, -1, 3},
                                               {20, 27, 25, 16, 0, -1, -1, 4},
                                               {21, 28, 26, 17, 1, -1, -1, 5},
                                               {22, 29, 27, 18, 2, -1, -1, 6},
                                               {23, 30, 28, 19, 3, -1, -1, 7},
                                               {-1, 31, 29, 20, 4, -1, -1, -1},
                                               {-1, -1, 30, 21, 5, -1, -1, -1},
                                               {26, 33, -1, -1, -1, -1, 1, 10},
                                               {27, 34, 32, -1, -1, 0, 2, 11},
                                               {28, 35, 33, 24, 8, 1, 3, 12},
                                               {29, 36, 34, 25, 9, 2, 4, 13},
                                               {30, 37, 35, 26, 10, 3, 5, 14},
                                               {31, 38, 36, 27, 11, 4, 6, 15},
                                               {-1, 39, 37, 28, 12, 5, 7, -1},
                                               {-1, -1, 38, 29, 13, 6, -1, -1},
                                               {34, 41, -1, -1, -1, -1, 9, 18},
                                               {35, 42, 40, -1, -1, 8, 10, 19},
                                               {36, 43, 41, 32, 16, 9, 11, 20},
                                               {37, 44, 42, 33, 17, 10, 12, 21},
                                               {38, 45, 43, 34, 18, 11, 13, 22},
                                               {39, 46, 44, 35, 19, 12, 14, 23},
                                               {-1, 47, 45, 36, 20, 13, 15, -1},
                                               {-1, -1, 46, 37, 21, 14, -1, -1},
                                               {42, 49, -1, -1, -1, -1, 17, 26},
                                               {43, 50, 48, -1, -1, 16, 18, 27},
                                               {44, 51, 49, 40, 24, 17, 19, 28},
                                               {45, 52, 50, 41, 25, 18, 20, 29},
                                               {46, 53, 51, 42, 26, 19, 21, 30},
                                               {47, 54, 52, 43, 27, 20, 22, 31},
                                               {-1, 55, 53, 44, 28, 21, 23, -1},
                                               {-1, -1, 54, 45, 29, 22, -1, -1},
                                               {50, 57, -1, -1, -1, -1, 25, 34},
                                               {51, 58, 56, -1, -1, 24, 26, 35},
                                               {52, 59, 57, 48, 32, 25, 27, 36},
                                               {53, 60, 58, 49, 33, 26, 28, 37},
                                               {54, 61, 59, 50, 34, 27, 29, 38},
                                               {55, 62, 60, 51, 35, 28, 30, 39},
                                               {-1, 63, 61, 52, 36, 29, 31, -1},
                                               {-1, -1, 62, 53, 37, 30, -1, -1},
                                               {58, -1, -1, -1, -1, -1, 33, 42},
                                               {59, -1, -1, -1, -1, 32, 34, 43},
                                               {60, -1, -1, 56, 40, 33, 35, 44},
                                               {61, -1, -1, 57, 41, 34, 36, 45},
                                               {62, -1, -1, 58, 42, 35, 37, 46},
                                               {63, -1, -1, 59, 43, 36, 38, 47},
                                               {-1, -1, -1, 60, 44, 37, 39, -1},
                                               {-1, -1, -1, 61, 45, 38, -1, -1},
                                               {-1, -1, -1, -1, -1, -1, 41, 50},
                                               {-1, -1, -1, -1, -1, 40, 42, 51},
                                               {-1, -1, -1, -1, 48, 41, 43, 52},
                                               {-1, -1, -1, -1, 49, 42, 44, 53},
                                               {-1, -1, -1, -1, 50, 43, 45, 54},
                                               {-1, -1, -1, -1, 51, 44, 46, 55},
                                               {-1, -1, -1, -1, 52, 45, 47, -1},
                                               {-1, -1, -1, -1, 53, 46, -1, -1}};

    if (-1 != lut[(size_t)curr_position][index] &&
        0 == BitArrGetVal(chess_board, lut[(size_t)curr_position][index]))
    {
        return (lut[(size_t)curr_position][index]);
    }

    return (-1);
}

static void *TimeOut(void *arg)
{
    int time = FIVE_MINUTE;

    while (0 < time)
    {
        time = sleep(time);
    }

    atomic_exchange(&is_timeout, 1);

    return (NULL);
}

/****************************Warnsdorffs impl*********************************/
int WarnsdorffsTour(char start_position, char path[BOARD_SIZE])
{
    pthread_t thread = 0;
    bit_arr_t chess_board = 0;
    int status = -1;

    if (0 != pthread_create(&thread, NULL, TimeOut, NULL))
    {
        return (FAILED);
    }

    status = KnightTourWarndorff(chess_board, start_position, path);

    if (0 != pthread_cancel(thread))
    {
        return (FAILED);
    }

    return (status);
}

static int KnightTourWarndorff(bit_arr_t chess_board, char curr_position, char path[BOARD_SIZE])
{
    warnsdorff_t array[BOARD_AXIS] = {{0, 0}};
    size_t i = 0;
    char degree = -1;
    int status = FAILED;

    path[BitArrCountOn(chess_board)] = curr_position;

    chess_board = BitArrSetOn(chess_board, curr_position);

    if (!(MAX_SIZE ^ chess_board))
    {
        return (SUCCESS);
    }

    if (is_timeout)
    {
        return (TIME_OUT);
    }

    UpdateRank(array, chess_board, curr_position);
    qsort(array, BOARD_AXIS, sizeof(char), Compare);

    for (i = 0; i < BOARD_AXIS && SUCCESS != status && TIME_OUT != status; ++i)
    {
        degree = array->rank;
        printf("rank: %d\n", array->rank);

        if (0 != degree)
        {
            status = KnightTourWarndorff(chess_board, array->position, path);
        }
    }

    return (status);
}

static void UpdateRank(warnsdorff_t *array, bit_arr_t chess_board, char curr_position)
{
    size_t i = 0;

    static char lut[BOARD_SIZE][BOARD_AXIS] = {{10, 17, -1, -1, -1, -1, -1, -1},
                                               {11, 18, 16, -1, -1, -1, -1, -1},
                                               {12, 19, 17, 8, -1, -1, -1, -1},
                                               {13, 20, 18, 9, -1, -1, -1, -1},
                                               {14, 21, 19, 10, -1, -1, -1, -1},
                                               {15, 22, 20, 11, -1, -1, -1, -1},
                                               {-1, 23, 21, 12, -1, -1, -1, -1},
                                               {-1, -1, 22, 13, -1, -1, -1, -1},
                                               {18, 25, -1, -1, -1, -1, -1, 2},
                                               {19, 26, 24, -1, -1, -1, -1, 3},
                                               {20, 27, 25, 16, 0, -1, -1, 4},
                                               {21, 28, 26, 17, 1, -1, -1, 5},
                                               {22, 29, 27, 18, 2, -1, -1, 6},
                                               {23, 30, 28, 19, 3, -1, -1, 7},
                                               {-1, 31, 29, 20, 4, -1, -1, -1},
                                               {-1, -1, 30, 21, 5, -1, -1, -1},
                                               {26, 33, -1, -1, -1, -1, 1, 10},
                                               {27, 34, 32, -1, -1, 0, 2, 11},
                                               {28, 35, 33, 24, 8, 1, 3, 12},
                                               {29, 36, 34, 25, 9, 2, 4, 13},
                                               {30, 37, 35, 26, 10, 3, 5, 14},
                                               {31, 38, 36, 27, 11, 4, 6, 15},
                                               {-1, 39, 37, 28, 12, 5, 7, -1},
                                               {-1, -1, 38, 29, 13, 6, -1, -1},
                                               {34, 41, -1, -1, -1, -1, 9, 18},
                                               {35, 42, 40, -1, -1, 8, 10, 19},
                                               {36, 43, 41, 32, 16, 9, 11, 20},
                                               {37, 44, 42, 33, 17, 10, 12, 21},
                                               {38, 45, 43, 34, 18, 11, 13, 22},
                                               {39, 46, 44, 35, 19, 12, 14, 23},
                                               {-1, 47, 45, 36, 20, 13, 15, -1},
                                               {-1, -1, 46, 37, 21, 14, -1, -1},
                                               {42, 49, -1, -1, -1, -1, 17, 26},
                                               {43, 50, 48, -1, -1, 16, 18, 27},
                                               {44, 51, 49, 40, 24, 17, 19, 28},
                                               {45, 52, 50, 41, 25, 18, 20, 29},
                                               {46, 53, 51, 42, 26, 19, 21, 30},
                                               {47, 54, 52, 43, 27, 20, 22, 31},
                                               {-1, 55, 53, 44, 28, 21, 23, -1},
                                               {-1, -1, 54, 45, 29, 22, -1, -1},
                                               {50, 57, -1, -1, -1, -1, 25, 34},
                                               {51, 58, 56, -1, -1, 24, 26, 35},
                                               {52, 59, 57, 48, 32, 25, 27, 36},
                                               {53, 60, 58, 49, 33, 26, 28, 37},
                                               {54, 61, 59, 50, 34, 27, 29, 38},
                                               {55, 62, 60, 51, 35, 28, 30, 39},
                                               {-1, 63, 61, 52, 36, 29, 31, -1},
                                               {-1, -1, 62, 53, 37, 30, -1, -1},
                                               {58, -1, -1, -1, -1, -1, 33, 42},
                                               {59, -1, -1, -1, -1, 32, 34, 43},
                                               {60, -1, -1, 56, 40, 33, 35, 44},
                                               {61, -1, -1, 57, 41, 34, 36, 45},
                                               {62, -1, -1, 58, 42, 35, 37, 46},
                                               {63, -1, -1, 59, 43, 36, 38, 47},
                                               {-1, -1, -1, 60, 44, 37, 39, -1},
                                               {-1, -1, -1, 61, 45, 38, -1, -1},
                                               {-1, -1, -1, -1, -1, -1, 41, 50},
                                               {-1, -1, -1, -1, -1, 40, 42, 51},
                                               {-1, -1, -1, -1, 48, 41, 43, 52},
                                               {-1, -1, -1, -1, 49, 42, 44, 53},
                                               {-1, -1, -1, -1, 50, 43, 45, 54},
                                               {-1, -1, -1, -1, 51, 44, 46, 55},
                                               {-1, -1, -1, -1, 52, 45, 47, -1},
                                               {-1, -1, -1, -1, 53, 46, -1, -1}};

    for (i = 0; i < BOARD_AXIS; ++i)
    {
        *(array + i)->position = lut[(size_t)curr_position][i];

        if (-1 == *(array + i)->position)
        {
            *(array + i)->rank = 0;
        }
        else
        {
            *(array + i)->rank = GetDegree(chess_board, lut, *(array + i)->position);
        }
    }

    return;
}

static char GetDegree(bit_arr_t chess_board, char lut[][BOARD_AXIS], size_t row)
{
    size_t i = 0;
    size_t count = 0;
    
    for (i = 0; i < BOARD_AXIS; ++i)
    {
        if (-1 != lut[row][i])
        {
            count += !BitArrGetVal(chess_board, lut[row][i]);
        }
    }
    return (count);
}

static int Compare(const void *data1, const void *data2)
{
    assert(data1);
    assert(data2);

    return (((warnsdorff_t *)data2)->rank - ((warnsdorff_t *)data1)->rank);
}