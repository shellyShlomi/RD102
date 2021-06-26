#ifndef _OL_102_FSM_H_
#define _OL_102_FSM_H_

int Calculate(const char *expression, double *result);

/* in c file
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
*/

#endif /* _OL_102_FSM_H_ */
