
#include <stddef.h> /* size_t */
#include <assert.h>

#include "bit_map.h"

#define BOOL_FALSE 0
#define BOOL_TRUE 1

#define X_AXIS 10


int IsInSape(size_t size_x_axis, size_t size_y_axis, size_t x, size_t y, size_t matrix[][X_AXIS])
{
    size_t i = 0;
    size_t axis_counter = 0;
    
	assert(matrix);
	assert(0 < size_x_axis);
	assert(0 < size_y_axis);
	assert(y < size_y_axis);
	assert(x < size_x_axis);

    if (1 == matrix[y][x] || 0 == x || 0 == y || 
    	(size_x_axis - 1) == x || (size_y_axis - 1) == y)
    {
        return (BOOL_FALSE);
    }
    
    for (i = y + 1; i < size_y_axis - 1; ++i)
    {
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]))
        {
            ++axis_counter;
        }
    }

    if (0 == (axis_counter & 1))
    {
        return (BOOL_FALSE);
    }


    for (i = 0;i < y; ++i)
    {
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]))
        {
            ++axis_counter;
        }
    }

    if (0 != (axis_counter & 1))
    {
        return (BOOL_FALSE);
    }


    for (i = x + 1; i < size_x_axis - 1; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

    if (0 == (axis_counter & 1))
    {
        return (BOOL_FALSE);
    }


    for (i = 0;i < x; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

    if (0 != (axis_counter & 1))
    {
        return (BOOL_FALSE);
    }

    return (BOOL_TRUE);
}

