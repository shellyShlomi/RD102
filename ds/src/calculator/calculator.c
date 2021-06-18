/*  Developer: Shelly Shlomi;									*
 *  Status:done											        *
 *  Date Of Creation:05.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By: ;							    	            *
 *  Description:	calulator with moduls of: addition,         * 
 *                  subtraction, multiplication, division       *	
 *					power                                       */

#include <stdlib.h> /* strtod */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <math.h>   /* pow */

#include "calculator.h"
#include "stack.h"

#define UNUSED(x) ((void)(x))

#define STATE (3)
#define EVENTS (256)
#define OPERATORS (8)

#define PEEK_OPER(X) ((operators_t)StackPeek((X)))
#define STACK_SIZE(X) (StackSize((X)))

/* wait_for_digit state define */
#define TO_ERROER_STATE                    \
    {                                      \
        (ERROR_STATE), (PromoteExpression) \
    }
#define STAY_AT_DIGIT                         \
    {                                         \
        (WAIT_FOR_DIGIT), (PromoteExpression) \
    }
#define PUSH_DIGIT_AND_TO_OPERATOR       \
    {                                    \
        (WAIT_FOR_OPERATOR), (PushDigit) \
    }
#define STAY_AND_PUSHMINUS            \
    {                                 \
        (WAIT_FOR_DIGIT), (PushMinus) \
    }
#define STAY_AND_PUSHPARANTHESES     \
    {                                \
        (WAIT_FOR_DIGIT), (PushPara) \
    }

/* wait_for_operator state define */
#define STAY_AT_OPERATOR                         \
    {                                            \
        (WAIT_FOR_OPERATOR), (PromoteExpression) \
    }
#define TO_DIGIT_PUSHMULTIPLY                 \
    {                                         \
        (WAIT_FOR_DIGIT), (PushStackMultiply) \
    }
#define STAY_AND_CALC_PARANTHESES       \
    {                                   \
        (WAIT_FOR_OPERATOR), (CalcPara) \
    }
#define TO_DIGIT_ACTIVATEOPERATOR               \
    {                                           \
        (WAIT_FOR_DIGIT), (ActivateCalculation) \
    }

typedef struct state state_t;
typedef struct calculator calculator_t;
typedef calc_status_t (*check_math_func_t)(double, double);
typedef int (*aritmethic_action_func_t)(calculator_t *);
typedef calc_status_t (*check_active_state_t)(calculator_t *, calc_status_t, double *);

/* enum of state */
typedef enum calc_state
{
    WAIT_FOR_DIGIT,
    WAIT_FOR_OPERATOR,
    ERROR_STATE
} calc_state_t;

/* enum of operations */
typedef enum operations
{
    DONTDO,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVISION,
    POWER,
    OPEN_PARANTHESES,
    CLOSE_PARANTHESES

} operators_t;

/* the struct state */
struct state
{
    calc_state_t state;
    aritmethic_action_func_t oper_func;
};

/* the struct state */
struct calculator
{
    stack_t *oper_stack;
    stack_t *digit_stack;
    calc_state_t active_state;
    char *exp;
};

/*---------------------------------------------------calculation Manegement Functions----------------------------------------------------*/

static int InitCalculator(calculator_t *calc, char *expression);
static operators_t OperatorToEnum(char exp);
static int CalcAll(calculator_t *calc);
static void Destroy(calculator_t *calc);
static int DoCalculation(calculator_t *calc);
static int PopPara(calculator_t *calc);

static calc_status_t InvalidOrMathErrExpression(calculator_t *calc, calc_status_t res, double *result);
static calc_status_t ValidOrMathErrExpression(calculator_t *calc, calc_status_t res, double *result);

static calc_status_t DontCheck(double first, double second);
static calc_status_t PowerCheck(double first, double second);
static calc_status_t DevisionCheck(double first, double second);

/*-------------------------------------------------------State Operation Functions-------------------------------------------------------*/
static int PushMinus(calculator_t *calc);
static int PushPara(calculator_t *calc);
static int PushStackMultiply(calculator_t *calc);
static int CalcPara(calculator_t *calc);
static int ActivateCalculation(calculator_t *calc);
static int PromoteExpression(calculator_t *calc);
static int PushDigit(calculator_t *calc);

/*-----------------------------------------------------Aritmethic Action Funcions-------------------------------------------------------*/

static double Addtion(double first, double second);
static double Subtraction(double first, double second);
static double Multiplication(double first, double second);
static double Division(double first, double second);
static double Power(double first, double second);
static double DoNothing(double first, double second);

/*--------------------------------------------------------------STATE LUT---------------------------------------------------------------*/

static state_t lut_state[STATE][EVENTS] = {

    /* wait_for_digit state lut */
    {TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, STAY_AT_DIGIT,
     STAY_AT_DIGIT, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, STAY_AT_DIGIT, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     STAY_AND_PUSHPARANTHESES, TO_ERROER_STATE, TO_ERROER_STATE, PUSH_DIGIT_AND_TO_OPERATOR, TO_ERROER_STATE, STAY_AND_PUSHMINUS, PUSH_DIGIT_AND_TO_OPERATOR, TO_ERROER_STATE, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR,
     PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, PUSH_DIGIT_AND_TO_OPERATOR, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE},

    /* wait_for_operator state lut */
    {TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, STAY_AT_OPERATOR,
     STAY_AT_OPERATOR, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, STAY_AT_OPERATOR, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_DIGIT_PUSHMULTIPLY, STAY_AND_CALC_PARANTHESES, TO_DIGIT_ACTIVATEOPERATOR, TO_DIGIT_ACTIVATEOPERATOR, TO_ERROER_STATE, TO_DIGIT_ACTIVATEOPERATOR, TO_ERROER_STATE, TO_DIGIT_ACTIVATEOPERATOR, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_DIGIT_ACTIVATEOPERATOR, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_DIGIT_ACTIVATEOPERATOR, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE,
     TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE, TO_ERROER_STATE},

};

/* priority_lut binary lut */
static int priority_lut[OPERATORS][OPERATORS] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}};
/*  dontdo, plus, minus, multiply, division, power, open_parantheses, close_parantheses */
/*  dontdo, 
    plus,  
    minus, 
    multiply, 
    division, 
    power, 
    open_parantheses, 
    close_parantheses */

static int math_err[OPERATORS] = {0, 0, 0, 0, 1, 2, 0, 0};

static double (*lut_operator[OPERATORS])(double first, double second) =
    {DoNothing, Addtion, Subtraction, Multiplication, Division, Power};

static size_t parantheses_lut[OPERATORS] = {0, 0, 0, 0, 0, 0, 1, 0};

/* convert operator to enum function */
static operators_t OperatorToEnum(char exp)
{
    static operators_t lut_operation[EVENTS] =
        {
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            OPEN_PARANTHESES, CLOSE_PARANTHESES, MULTIPLY, PLUS, DONTDO, MINUS, DONTDO, DIVISION, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, POWER, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO,
            DONTDO, DONTDO, DONTDO, DONTDO, DONTDO, DONTDO};

    return (lut_operation[(operators_t)exp]);
}

/*-----------------------------------------------------------------imple funcs----------------------------------------------------------------------*/

calc_status_t Calculate(const char *expression, double *result)
{
    check_active_state_t check_active_state[] = {
        InvalidOrMathErrExpression,
        ValidOrMathErrExpression,
        InvalidOrMathErrExpression};
    calculator_t calc = {0};
    calc_status_t status = 0;
    char *exp = NULL;

    assert(expression);
    assert(result);

    exp = (char *)expression;

    status = InitCalculator(&calc, exp);

    while (ERROR_STATE != calc.active_state && !status && '\0' != *(exp))
    {
        status = lut_state[calc.active_state][(size_t) * (exp)].oper_func(&calc);
        calc.active_state = lut_state[calc.active_state][(size_t) * (exp)].state;
        exp = calc.exp;
    }

    return (check_active_state[calc.active_state](&calc, status, result));
}

/*-----------------------------------------------------Calculate helper func and calc management-------------------------------------------------------*/

/* return status lut funcs */
static calc_status_t InvalidOrMathErrExpression(calculator_t *calc, calc_status_t status, double *result)
{
    calc_status_t check_active_state[] = {INVALID_EQUETION, SUCCESS, MATH_ERROR};

    assert(calc);

    UNUSED(result);

    Destroy(calc);

    return (check_active_state[status]);
}

static calc_status_t ValidOrMathErrExpression(calculator_t *calc, calc_status_t status, double *result)
{
    assert(calc);

    CalcAll(calc);
    *(void **)result = StackPeek(calc->digit_stack);

    Destroy(calc);

    return (status);
}
/*------------------------*/

static int InitCalculator(calculator_t *calc, char *expression)
{
    double dummy_digit = 0.0;
    operators_t dummy_operation = PLUS;
    size_t size = 0;

    assert(calc);

    size = strlen(expression) + 1;
    calc->exp = expression;

    calc->oper_stack = StackCreate(size);
    if (NULL == calc->oper_stack)
    {
        return (SYSTEM_FAIL);
    }

    calc->digit_stack = StackCreate(size);
    if (NULL == calc->digit_stack)
    {
        StackDestroy(calc->oper_stack);
        calc->oper_stack = NULL;
        return (SYSTEM_FAIL);
    }

    calc->active_state = WAIT_FOR_DIGIT;

    StackPush(calc->digit_stack, *(void **)&dummy_digit);
    StackPush(calc->oper_stack, *(void **)&dummy_operation);

    return (SUCCESS);
}

static void Destroy(calculator_t *calc)
{
    StackDestroy(calc->oper_stack);
    StackDestroy(calc->digit_stack);

    calc->digit_stack = NULL;
    calc->oper_stack = NULL;
    calc->exp = NULL;

    return;
}

/*-----------------------------------------------------states lut functions-------------------------------------------------------*/

static int PromoteExpression(calculator_t *calc)
{
    assert(calc);

    ++calc->exp;

    return (SUCCESS);
}

static int ActivateCalculation(calculator_t *calc)
{
    operators_t index = DONTDO;

    assert(calc);

    index = OperatorToEnum(*(calc->exp));

    while (1 < STACK_SIZE(calc->oper_stack) &&
           priority_lut[PEEK_OPER(calc->oper_stack)][index])
    {
        DoCalculation(calc);
    }

    StackPush(calc->oper_stack, *(void **)&index);

    ++calc->exp;

    return (SUCCESS);
}

static int CalcPara(calculator_t *calc)
{
    static calc_status_t status[] = {INVALID_EQUETION, SUCCESS};
    size_t cur_operator = 0;

    assert(calc);

    while (1 < STACK_SIZE(calc->oper_stack) &&
           OPEN_PARANTHESES != PEEK_OPER(calc->oper_stack))
    {
        DoCalculation(calc);
    }

    cur_operator = parantheses_lut[PEEK_OPER(calc->oper_stack)];

    StackPop(calc->oper_stack);

    ++calc->exp;

    return (status[cur_operator]);
}

static int PushMinus(calculator_t *calc)
{
    static calc_status_t status[] = {SUCCESS, MATH_ERROR};
    operators_t peek_oper = DONTDO;
    void *peek_digit = NULL;
    operators_t multiply = MULTIPLY;
    double num = -1;

    assert(calc);

    peek_digit = StackPeek(calc->digit_stack);
    peek_oper = PEEK_OPER(calc->oper_stack);

    StackPush(calc->digit_stack, *(void **)&num);
    StackPush(calc->oper_stack, *(void **)&multiply);

    ++calc->exp;

    return (status[(!(*(double *)&peek_digit)) & (peek_oper == POWER)]);
}

static int PushPara(calculator_t *calc)
{
    operators_t parantheses = OPEN_PARANTHESES;

    assert(calc);

    StackPush(calc->oper_stack, *(void **)&parantheses);

    ++calc->exp;

    return (SUCCESS);
}

static int PushStackMultiply(calculator_t *calc)
{
    operators_t multiply = MULTIPLY;

    assert(calc);

    while (priority_lut[PEEK_OPER(calc->oper_stack)][multiply])
    {
        DoCalculation(calc);
    }

    StackPush(calc->oper_stack, *(void **)&multiply);
    PushPara(calc);

    return (SUCCESS);
}

static int PushDigit(calculator_t *calc)
{
    double res = 0.0;
    char *end = NULL;
    void *num_in_stack = NULL;
    operators_t peek_OPER = DONTDO;
    check_math_func_t check_func[] = {DontCheck, DevisionCheck, PowerCheck};

    assert(calc);

    num_in_stack = StackPeek(calc->digit_stack);
    peek_OPER = PEEK_OPER(calc->oper_stack);

    res = strtod(calc->exp, &end);

    StackPush(calc->digit_stack, *(void **)&res);

    calc->exp = end;

    return (check_func[math_err[peek_OPER]](res, *(double *)&num_in_stack));
}

/*---------------------------------------------------math error chack functions-------------------------------------------------------*/
static calc_status_t DevisionCheck(double first, double second)
{
    calc_status_t status[] = {SUCCESS, MATH_ERROR};

    UNUSED(second);

    return (status[!first]);
}
static calc_status_t PowerCheck(double first, double second)
{
    calc_status_t status[] = {SUCCESS, SUCCESS, MATH_ERROR};

    return (status[!first + !second]);
}

static calc_status_t DontCheck(double first, double second)
{
    UNUSED(second);
    UNUSED(first);

    return (SUCCESS);
}

/*---------------------------------------------------Calculation func---------------------------------------------------------*/
static int DoCalculation(calculator_t *calc)
{
    void *first = NULL;
    void *second = NULL;

    assert(calc);

    second = StackPeek(calc->digit_stack);
    StackPop(calc->digit_stack);

    first = StackPeek(calc->digit_stack);
    StackPop(calc->digit_stack);

    *(double *)&first =
        lut_operator[PEEK_OPER(calc->oper_stack)](*(double *)&first, *(double *)&second);

    StackPush(calc->digit_stack, first);
    StackPop(calc->oper_stack);

    return (SUCCESS);
}

static int CalcAll(calculator_t *calc)
{
    aritmethic_action_func_t operation_handler[] = {DoCalculation, PopPara};

    assert(calc);

    while (0 < STACK_SIZE(calc->oper_stack)) /*compute the dummy of both stacks 0.0 && PLUS*/
    {
        operation_handler[parantheses_lut[PEEK_OPER(calc->oper_stack)]](calc);
    }

    return (SUCCESS);
}

static int PopPara(calculator_t *calc)
{
    assert(calc);

    StackPop(calc->oper_stack);

    return (SUCCESS);
}

/*---------------------------------------------------Aritmetics functions-------------------------------------------------------*/
static double Addtion(double first, double second)
{
    return (first + second);
}

static double Multiplication(double first, double second)
{
    return (first * second);
}

static double Division(double first, double second)
{
    return (first / second);
}

static double Subtraction(double first, double second)
{
    return (first - second);
}

static double Power(double first, double second)
{
    return (pow(first, second));
}

static double DoNothing(double first, double second)
{
    UNUSED(first);
    UNUSED(second);

    return (SUCCESS);
}
