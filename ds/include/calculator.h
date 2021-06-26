#ifndef __OL_102_CALCULATOR_H__
#define __OL_102_CALCULATOR_H__

typedef enum calc_status
{
    SUCCESS,
    INVALID_EQUATION, /* syntax error */
    MATH_ERROR, /* division by 0, 0 ^ 0 */
    SYSTEM_FAIL /* inner program failure */
}calc_status_t;

calc_status_t Calculate(const char *expression, double *result);

#endif /* __OL_102_CALCULATOR_H__ */




