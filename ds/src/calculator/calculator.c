/*  Developer: Shelly Shlomi;									*
 *  Status:;											        *
 *  Date Of Creation:05.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: ;							    	            *
 *  Description:	calulator with moduls of: addition,         * 
 *                  subtraction, multiplication, division       *	
 *					multiplication, division			        */

#include <stdlib.h> /*EXIT_SUCCESS*/
#include <assert.h>
#include <string.h> /*strlen*/

#include "calculator.h"
#include "stack.h"

#define OPERATION_FUNC_SIZE 256
#define STATE_ARR_SIZE 3
#define RETURN_VAL 2
#define UNUSED(x) (void)(x)

typedef struct state state_t;
typedef struct calculator calculator_t;
typedef struct lut_state lut_state_t;

typedef enum calc_state 
{
    WAIT_FOR_DIGIT,
    WAIT_FOR_OPERATOR,
    ERROR_STATE
}calc_state_t;

typedef enum return_val_user 
{
    ERROR
}return_val_user_t;

struct lut_state 
{
    calc_state_t state;
    int (*OperFunc)(calc_state_t **next_state, calculator_t *calc);

};

struct state
{
    calc_state_t state;
    lut_state_t (*operation_state_lut)[OPERATION_FUNC_SIZE];
};

struct calculator
{
    stack_t *operators_stack;
    stack_t *digit_stack;
    char *expr;
    char **end_ptr_expr;
    state_t *active_state;
    state_t (*states)[STATE_ARR_SIZE];
};

/*-------------------------------------------------init Calculate--------------------------------------------------------------*/

static calculator_t *Init(char *expression);

/*-------------------------------------------------init states funcs-----------------------------------------------------------*/
static void InitStatElem(calculator_t *calc);
static state_t *WaitForOperationInit();
static state_t *WaitForDigitInit();
static state_t *ErrorStateInit();

/*-------------------------------------------------operaion funcs--------------------------------------------------------------*/
static int DigitFunc(calc_state_t **next_state, calculator_t *calc);
static int ErrStaet(calc_state_t **next_state, calculator_t *calc);
static int DoNothing(calc_state_t **next_state, calculator_t *calc);
static int DigitBracket(calc_state_t **next_state, calculator_t *calc);

/*---------------------------------------------------imple funcs---------------------------------------------------------------*/


double Calculate(const char *expression, double *result)
{
    calculator_t *calc = NULL;
    int res = 0;
    char *event = (char *)expression;
    calc_state_t *next_state = NULL;
    
    assert(expression);
    assert(result);

    calc = Init(event);
    
    while ('\0'!= *event && ERROR != res && ERROR_STATE != calc->active_state->state)
    {
       res = (calc->active_state->operation_state_lut[(size_t)(*event)]->OperFunc(&next_state, calc));
       calc->active_state = calc->states[*next_state];
       ++event;
    }
    
    return (res);

}

static calculator_t *Init(char *expression)
{
    static calculator_t *calc = {NULL};
    size_t exp_len = 0;
    calc->operators_stack = NULL;
    calc->digit_stack = NULL;

    assert(expression);

    exp_len = strlen(expression);

    calc->operators_stack = StackCreate(exp_len);
    if (calc->operators_stack)
    {
        return NULL;
    }

    calc->digit_stack = StackCreate(exp_len);
    if (calc->digit_stack)
    {
        calc->operators_stack = NULL;
        StackDestroy(calc->operators_stack);
        return NULL;
    }

    InitStatElem(calc);

    return calc;
}




static int DigitFunc(calc_state_t **next_state, calculator_t *calc)
{
    UNUSED(next_state);
    UNUSED(calc);

    return (EXIT_SUCCESS);
}


static int ErrStaet(calc_state_t **next_state, calculator_t *calc)
{
    UNUSED(next_state);
    UNUSED(calc);

    return (EXIT_SUCCESS);

}

static int DoNothing(calc_state_t **next_state, calculator_t *calc)
{
    UNUSED(next_state);
    UNUSED(calc);

    return (EXIT_SUCCESS);
}

static int DigitBracket(calc_state_t **next_state, calculator_t *calc)
{
    UNUSED(next_state);
    UNUSED(calc);

    return (EXIT_SUCCESS);
}




static void InitStatElem(calculator_t *calc)
{
    static state_t wait_for_digit = {0};
    static state_t wait_for_operation = {0};
    static state_t err_state = {0};
    
    wait_for_digit= *(WaitForDigitInit());
    wait_for_digit.state = WAIT_FOR_DIGIT;

    wait_for_operation = *(WaitForOperationInit());
    wait_for_operation.state = WAIT_FOR_OPERATOR;
    
    err_state = *(ErrorStateInit());
    err_state.state = ERROR_STATE;


    assert(calc);

    *(calc->states[WAIT_FOR_DIGIT]) = wait_for_digit;
    *(calc->states[WAIT_FOR_OPERATOR]) = wait_for_operation;
    *(calc->states[ERROR_STATE]) = err_state;

    (calc->active_state) = calc->states[WAIT_FOR_DIGIT];

    return;
}

static state_t *WaitForOperationInit()
{
    static state_t wait_for_oper = {0};

    static const lut_state_t do_nothing = {WAIT_FOR_OPERATOR, DoNothing};
    static const lut_state_t move_to_err = {ERROR_STATE, ErrStaet};

    static lut_state_t wait_for_oper_lut[OPERATION_FUNC_SIZE] = 
    {
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, do_nothing,
        do_nothing, do_nothing, do_nothing, do_nothing, do_nothing, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,
   };
    wait_for_oper.operation_state_lut = &wait_for_oper_lut;

   return (&wait_for_oper);
}
    

static state_t *WaitForDigitInit()
{
    static state_t wait_for_digit = {0};

    static const lut_state_t move_to_err = {ERROR_STATE, ErrStaet};
    static const lut_state_t do_nothing = {WAIT_FOR_DIGIT, DoNothing};
    static const lut_state_t digit_bracket = {WAIT_FOR_DIGIT, DigitBracket};
    static const lut_state_t digit_func = {WAIT_FOR_OPERATOR, DigitFunc};
    
    static lut_state_t wait_for_digit_lut[OPERATION_FUNC_SIZE] = 
    {
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, do_nothing, 
        do_nothing, do_nothing, do_nothing, do_nothing, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, do_nothing, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err,  
        digit_bracket, digit_bracket, move_to_err, digit_func, move_to_err, digit_func, digit_func, move_to_err, digit_func, digit_func,  
        digit_func, digit_func, digit_func, digit_func, digit_func, digit_func, digit_func, digit_func, move_to_err, move_to_err,  
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, 
        move_to_err, move_to_err, move_to_err, move_to_err, move_to_err, move_to_err
    };

    wait_for_digit.operation_state_lut = &wait_for_digit_lut;

    return (&wait_for_digit);

}

static state_t *ErrorStateInit()
{
    static state_t err_state = {0};

    static const lut_state_t stay_in_err = {ERROR_STATE, DoNothing};
    
    static lut_state_t error_state_lut[OPERATION_FUNC_SIZE] = 
    {
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err, stay_in_err,
            stay_in_err, stay_in_err, stay_in_err
    };

    err_state.operation_state_lut = &error_state_lut;
    
    return (&err_state); 
}