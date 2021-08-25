#include <stdio.h>	/* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* system */
#include <assert.h>

#define SIZE 256
#define ESC 27
#define ENTER 10

#define UNUSED(x) (void)(x)

typedef struct chars_s
{
	void (*count)(char c, struct chars_s *);
	size_t counter;
} chars_t;

int getchar();
static void MilionChar();
static void CountUp(char c, struct chars_s *arrlut);
static void CountAll(char c, struct chars_s *arrlut);
static void Esc(char c, struct chars_s *arrlut);
static void Enter(char c, struct chars_s *arrlut);

int main()
{
	MilionChar();

	return (0);
}

static void MilionChar()
{

	unsigned char c = '\0';
	size_t index = 0;
	static chars_t arrlut[SIZE] = {0};
	chars_t chars = {CountUp, 0};

	while (index < SIZE)
	{
		arrlut[index] = chars;
		++index;
	}

	arrlut[(size_t)ESC].count = Esc;
	arrlut[(size_t)'0'].count = CountAll;
	arrlut[(size_t)ENTER].count = Enter;

	while (ESC != c)
	{
		c = getchar();

		(arrlut[(size_t)c].count)(c, arrlut);
	}

	(arrlut[(size_t)ESC].count)(c, arrlut);

	return;
}

static void CountUp(char c, struct chars_s *arrlut)
{

	arrlut[(size_t)c].counter += 1;

	return;
}
static void CountAll(char c, struct chars_s *arrlut)
{
	size_t i = 0;
	size_t cur_max = 0;
	char ch = '\0';

	UNUSED(c);
	assert(arrlut);

	for (i = 0; i < SIZE; ++i)
	{
		if (cur_max < (arrlut[i].counter))
		{
			cur_max = arrlut[i].counter;
			ch = i;
		}

		arrlut[i].counter = 0;
	}
	printf("the max num of occurrenc is: %lu, and the char is : %c\n", cur_max, ch);

	return;
}

static void Esc(char c, struct chars_s *arrlut)
{
	UNUSED(c);
	UNUSED(arrlut);

	system("stty icanon echo");
	return;
}

static void Enter(char c, struct chars_s *arrlut)
{
	UNUSED(c);
	UNUSED(arrlut);

	return;
}

/*anuder vertion
void MilionChar(char c)
{
    static char lut[MAX_CHAR] = {0};

    size_t max_occurance = 0;

    size_t i = 0;

    if ('0' == character)
    {
        for (i = 0; i < MAX_CHAR; i++)
        {
            if (max_occurance < (size_t)lut[i])
            {
                max_occurance = (size_t)lut[i];
            }

            lut[i] = 0;
        }

        printf("max previous occurance = %lu\n", max_occurance);

        max_occurance = 0;

        return;
    }

    ++lut[(size_t)character];

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
}*/