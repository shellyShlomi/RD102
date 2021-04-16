#include <stdio.h>/*print*/

/* Q 1 */
#define MAX2(a, b) ((a) > (b) ? (a) : (b))

#define MAX3(a, b, c)((a) > (b) ? MAX2((a), (c)) : MAX2((b), (c)))

/* Q 2 */
#define TO_LOWER(a)((('A' <= (a)) && ('Z' >=(a))) ? ((a) + ('a' - 'A')): (a))

/* Q 3 */
#define OFFSET(s, f)((size_t)&(((s *)0)->f)) 

int main()
{

	struct s
	{
		char c;
		int i;
		float f;
	};

	printf("%d\n",MAX3(5,10,4));
	
	printf("%ld\n" , OFFSET(struct s, f));

	printf("%c\n",TO_LOWER('D'));
	printf("%c\n",TO_LOWER('?'));
	printf("%c\n",TO_LOWER('a'));
	
	return 0;

}
