/* C program to print all permutations with duplicates allowed*/
#include <stdio.h>
#include <string.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/* Function to print permutations of string
This function takes three parameters:
1. String
2. Starting index of the string
3. Ending index of the string. */
void permute(char *a, char *l, char *r)
{
    int i;

    if (l == r)
    {
        puts(a);
        return;
    }
    else
    {
        for (l = l; l <= r; ++l)
        {
            swap((l), (r));
            permute(a, ++l, r);
            swap((r), (l)); /*backtrack*/
        }
    }
    return;
}

/* Driver program to test above functions */
int main()
{
    char str[] = "ABC";
    int n = strlen(str);
    permute(str, str, str + n - 1);
    return 0;
}




#include "knights_tour.h"

#define BOARD_AXIS 8

static void CreateLut();


/*  typedef enum return_val
 { 
    SUCCESS,
    TIME_OUT
 } return_val_t;
    more... 


int CreateTour(char start_position, char path[BOARD_SIZE]);
int WarnsdorffsTour(char start_position, char path[BOARD_SIZE]);
 */

static void CreateLut()
{
    static char lut[BOARD_AXIS * BOARD_AXIS][BOARD_AXIS] = 
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
    {-1, -1, -1, -1, 53, 46, -1, -1}
    }
    return;
}



/*
    wan.. algorythm - GetMinDegreeStep: Successor is the step that has the smallest num of neighbors.
    is_in_chess_borders 
    is_allready_visited_spot

    advanced: add graphics
*/
