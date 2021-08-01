

#include <assert.h> /*  assert    */
#include <time.h>   /*  clock_t   */
#include <string.h> /*  memmove   */
#include <stdlib.h> /* time_t, rand */

#include "bit_array.h"
#include "knights_tour.h"

typedef struct next_step_s
{
    size_t degree;
    char next_step;
} next_step_t;

/*------------- general defines ------------*/
#define BOARD_AXIS (8)
#define BIT_ARR_MAX (BitArrSetAll((bit_arr_t)0))
#define DELTA_OF_TIME_OUT ((double)10)

/*------------- addition of return_val ------------*/
#define DEAD_END (TIME_OUT + 1)

/*------------- general function ------------*/

void GetLut(char lut[][BOARD_AXIS]);

/*------------- Backtracking decleration ------------*/

static char GetNextPossibleStep(char curr_position,
                                bit_arr_t chess_board,
                                size_t index);

static return_val_t JumpToNextPosition(char curr_position,
                                       bit_arr_t chess_board,
                                       char path[BOARD_SIZE],
                                       clock_t start_time);

/*------------- Warnsdorffs decleration ------------*/
static return_val_t MoveToNextPosition(char curr_position,
                                       bit_arr_t chess_board,
                                       char path[BOARD_SIZE],
                                       clock_t start_time);

int CmpFunction(const void *data1, const void *data2);

static size_t GetDegree(char next_steps_lut[BOARD_AXIS], bit_arr_t chess_board);

static void GetPossibleSteps(next_step_t next_steps_lut[],
                             char curr_position,
                             bit_arr_t chess_board);

/***************************** Backtracking impl *****************************/

return_val_t CreateTour(char start_position, char path[BOARD_SIZE])
{
    clock_t start_time = clock();
    bit_arr_t chess_board = 0;

    assert(path);

    return (JumpToNextPosition(start_position, chess_board, path, start_time));
}

/*************************** Backtracking - iner func ***************************/
static return_val_t JumpToNextPosition(char curr_position,
                                       bit_arr_t chess_board,
                                       char path[BOARD_SIZE],
                                       clock_t start_time)
{
    size_t i = 0;
    return_val_t res = DEAD_END;
    char next_position = -2;

    assert(path);
    assert(curr_position >= 0);
    assert(curr_position < BOARD_SIZE);

    path[BitArrCountOn(chess_board)] = curr_position;
    chess_board = BitArrSetOn(chess_board, (size_t)curr_position);

    if (0 == (chess_board ^ BIT_ARR_MAX))
    {
        return (SUCCESS);
    }

    if (DELTA_OF_TIME_OUT <= (double)(clock() - start_time) / CLOCKS_PER_SEC)
    {
        return (TIME_OUT);
    }

    for (i = 0; (i < BOARD_AXIS) && (res != SUCCESS) && (res != TIME_OUT); ++i)
    {
        next_position = GetNextPossibleStep(curr_position, chess_board, i);
        if (-1 != next_position)
        {
            res = JumpToNextPosition(next_position, chess_board, path, start_time);
        }
    }

    return (res);
}

/* if there is next step return the next step and if ther is no free next step returns -1 */
static char GetNextPossibleStep(char curr_position,
                                bit_arr_t chess_board,
                                size_t index)
{
    char lut[BOARD_AXIS * BOARD_AXIS][BOARD_AXIS] = {0};
    char value = '\0';
    assert(curr_position >= 0);
    assert(curr_position < BOARD_SIZE);
    assert(index < BOARD_AXIS);

    GetLut(lut);
    value = lut[(size_t)curr_position][index];

    if ((-1 != value) && (0 == BitArrGetVal(chess_board, (size_t)value)))
    {
        return (lut[(size_t)curr_position][index]);
    }

    return (-1);
}
/*************************** Warnsdorffs impl ***************************/

return_val_t WarnsdorffsTour(char start_position, char path[BOARD_SIZE])
{
    clock_t start_time = clock();
    bit_arr_t chess_board = 0;

    assert(path);

    return (MoveToNextPosition(start_position, chess_board, path, start_time));
}

/*************************** Warnsdorffs - iner func ***************************/
static return_val_t MoveToNextPosition(char curr_position,
                                       bit_arr_t chess_board,
                                       char path[BOARD_SIZE],
                                       clock_t start_time)
{
    size_t i = 0;
    return_val_t res = DEAD_END;
    next_step_t next_steps_lut[BOARD_AXIS] = {0};
    char next_step = '\0';
    size_t degree = 0;

    assert(path);
    assert(curr_position >= 0);
    assert(curr_position < BOARD_SIZE);

    path[BitArrCountOn(chess_board)] = curr_position;
    chess_board = BitArrSetOn(chess_board, (size_t)curr_position);

    if (DELTA_OF_TIME_OUT <= ((double)(clock() - start_time) / CLOCKS_PER_SEC))
    {
        return (TIME_OUT);
    }

    GetPossibleSteps(next_steps_lut, curr_position, chess_board);

    for (i = 0; (i < BOARD_AXIS) && (res != SUCCESS) && (res != TIME_OUT); ++i)
    {
        next_step = next_steps_lut[i].next_step;
        degree = next_steps_lut[i].degree;

        if ((0 < degree) && (0 == BitArrGetVal(chess_board, (size_t)next_step)))
        {
            res = MoveToNextPosition(next_step, chess_board, path, start_time);
        }
        else if ((0 == degree) &&
                 (chess_board == BitArrSetOff(BIT_ARR_MAX, next_step)))
        {
            path[BitArrCountOn(chess_board)] = next_step;
            return (SUCCESS);
        }
    }

    return (res);
}

/* if there is next step return the next step and if ther is no free next step returns -1 */
static void GetPossibleSteps(next_step_t next_steps_lut[],
                             char curr_position,
                             bit_arr_t chess_board)
{
    size_t i = 0;

    char lut[BOARD_AXIS * BOARD_AXIS][BOARD_AXIS] = {0};

    assert(curr_position >= 0);
    assert(curr_position < BOARD_SIZE);

    GetLut(lut);

    for (i = 0; (i < BOARD_AXIS); ++i)
    {
        if (-1 < lut[(size_t)curr_position][i])
        {
            next_steps_lut[i].next_step = lut[(size_t)curr_position][i];
            next_steps_lut[i].degree =
                GetDegree(lut[(size_t)next_steps_lut[i].next_step], chess_board);
        }
    }

    qsort(next_steps_lut, BOARD_AXIS, sizeof(next_step_t), CmpFunction);

    return;
}

static size_t GetDegree(char next_steps_lut[BOARD_AXIS], bit_arr_t chess_board)
{
    size_t i = 0;
    size_t counter = 0;

    while (i < BOARD_AXIS)
    {
        if ((-1 != next_steps_lut[i]) &&
            (0 == BitArrGetVal(chess_board, (size_t)next_steps_lut[i])))
        {
            ++counter;
        }
        ++i;
    }

    return (counter);
}

int CmpFunction(const void *data1, const void *data2)
{
    return (((next_step_t *)data1)->degree - ((next_step_t *)data2)->degree);
}

void GetLut(char lut[][BOARD_AXIS])
{
    static char lut_local[BOARD_AXIS * BOARD_AXIS][BOARD_AXIS] =
        {{10, 17, -1, -1, -1, -1, -1, -1},
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

    memmove(lut, lut_local, sizeof(lut_local));

    return;
}