#include <stdio.h> /* printf */

#define MAX_CHAR (256)

static void TestPrintMaxOccurrenceSameChar();
static void TestCountOnBits();

void PrintMaxOccurrenceSameChar(char character);
size_t CountSetBits(long num);

int main()
{
    TestPrintMaxOccurrenceSameChar();
    TestCountOnBits();

    return (0);
}

size_t CountSetBits(long num)
{
    size_t count = 0;

    while (0 != num)
    {
        num &= (num - 1);
        count++;
    }

    return (count);
}

void PrintMaxOccurrenceSameChar(char character)
{
    static char lut_count[MAX_CHAR] = {0};

    size_t max_occurance = 0;

    size_t i = 0;

    if ('0' == character)
    {
        for (i = 0; i < MAX_CHAR; i++)
        {
            if (max_occurance < (size_t)lut_count[i])
            {
                max_occurance = (size_t)lut_count[i];
            }

            lut_count[i] = 0;
        }

        printf("max previous occurance = %lu\n", max_occurance);

        max_occurance = 0;

        return;
    }

    ++lut_count[(size_t)character];

    return;
}

static void TestPrintMaxOccurrenceSameChar()
{
    char *str1 = "OhadEzra12.6.1991,aa0";
    char *str2 = "12345643211 0";

    size_t i = 0;

    while ('\0' != *str1)
    {
        PrintMaxOccurrenceSameChar(*str1);

        ++str1;
    }

    while ('\0' != *str2)
    {
        PrintMaxOccurrenceSameChar(*str2);

        ++str2;
    }

    return;
}

static void TestCountOnBits()
{
    long data[] = {0xffffffffffffffff, 0x0, 0x7, 0xaa, 0x1};

    size_t actual = 0;
    size_t expected[] = {64, 0, 3, 4, 1};

    size_t size = sizeof(data) / sizeof(data[0]);
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        actual = CountSetBits(data[i]);

        if (actual != expected[i])
        {
            printf("test CountOnBits failed at index: %lu in line: %d\n", i, __LINE__);
        }
    }

    return;
}