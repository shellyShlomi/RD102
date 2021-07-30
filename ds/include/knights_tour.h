#ifndef _RD_102_KNIGHTS_TOUR_H_
#define _RD_102_KNIGHTS_TOUR_H_

#include <stddef.h>     /* size_t */

#define BOARD_SIZE (64)

 typedef enum return_val
 { 
    SUCCESS,
    TIME_OUT
 } return_val_t;


return_val_t CreateTour(char start_position, char path[BOARD_SIZE]);
return_val_t WarnsdorffsTour(char start_position, char path[BOARD_SIZE]);



/*
    wan.. algorythm - GetMinDegreeStep: Successor is the step that has the smallest num of neighbors.
    is_in_chess_borders 
    is_allready_visited_spot

    advanced: add graphics
*/

#endif /* _RD_102_KNIGHTS_TOUR_H_ */

