#ifndef __OL102_PART2_H__
#define __OL102_PART2_H__

#include <stdint.h>	/* uint16_t */

#define IS_LITTLE_ENDIAN (*(uint16_t *)"\0\xF0" > 0x0100)

char *ItoaBase10          (int value, char *str);
int   AtoiBase10		  (const char *str);
char *ItoaBaseTil36       (int value, char *str, int base );
int   AtoiBaseTil36		  (const char *str, int base);
void  PrintFirstAndSecond (const char *arr1, size_t len1, const char *arr2, size_t len2, const char *arr3, size_t len3);
int   IsLittleEndian      ();

#endif /*__OL102_PART2_H__*/
