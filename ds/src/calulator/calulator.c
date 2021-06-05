/*  Developer: Shelly Shlomi;									*
 *  Status:;											        *
 *  Date Of Creation:05.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: ;							    	            *
 *  Description:	calulator with moduls of: addition,         * 
 *                  subtraction, multiplication, division       *	
 *					multiplication, division			        */

#include "calculate.h"

typedef struct calculator
{
    stack_t *operands;
    stack_t *operations;
    state_t  transition[STATE][EVENT];
}calculator_t;

typedef enum state
{     
	WAIT_FOR_DIGIT,
	WAIT_FOR_OPERATOR,     
	ERROR_STATE 
} state_t;