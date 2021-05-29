#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#include "sll_ex.h"

#define SUCCESS_BOL 1

static void Maneger();
static void TestFilp();
static void TestHasLoopNoLoop();
static void TestHasLoopWithLoop();
static void TestFindInteNoIter();
static void TestFindInterWithIinter();
/*
static void printList(node_t *head);
*/

extern size_t CountElemInList(node_t *head);


int main()
{

	Maneger();
	
	return (0); 
}

static void Maneger()
{
	TestFilp();
	TestHasLoopNoLoop();
	TestHasLoopWithLoop();
	TestFindInteNoIter();
	TestFindInterWithIinter();
	
	return;
}

/*list  : firat -> c -> b -> a -> last */
static void TestFilp()
{
	size_t i = 0;
	size_t count = 0;
	int exp_arr[] = {5, 4, 3, 2, 1};
	node_t *head = NULL;
	node_t *fliped_head = NULL;
	
	node_t last = {NULL};
    node_t a = {NULL};
    node_t b = {NULL};
    node_t c = {NULL};
    node_t first = {NULL}; 
 
 	last.data = (void *)5;  
	a.data = (void *)4; 
	b.data = (void *)3;
	c.data = (void *)2;
	first.data = (void *)1;
	
    last.next = NULL;
    a.next = &last;
    b.next = &a;
    c.next = &b;
    first.next = &c;
 
    head = &first;
	fliped_head = Flip(head);
	
	count = CountElemInList(fliped_head);
	
	for(i = 0; i < count; ++i)
	{
		if (exp_arr[i] != *(int *)&(fliped_head->data))
		{
			printf("TestFilp error at line: %d\n", __LINE__);
		}
		
		fliped_head = fliped_head->next;
	}

	return;
}

/*list  : firat -> c -> b -> a -> last */
static void TestHasLoopNoLoop()
{
	node_t *head = NULL;

	node_t last = {NULL};
    node_t a = {NULL};
    node_t b = {NULL};
    node_t c = {NULL};
    node_t first = {NULL}; 
 
 	last.data = (void *)5;  
	a.data = (void *)4; 
	b.data = (void *)3;
	c.data = (void *)2;
	first.data = (void *)1;
	
    last.next = NULL;
    a.next = &last;
    b.next = &a;
    c.next = &b;
    first.next = &c;
 
    head = &first;

	if ((!SUCCESS_BOL) != HasLoop(head))
	{
		printf("TestHasLoopNoLoop error at line: %d\n", __LINE__);
	}


	return;
}

/*list  : firat -> f -> e -> d -> c -> b -> a -> last */
static void TestHasLoopWithLoop()
{
	node_t *head = NULL;


    node_t a1 = {NULL};
    node_t b1 = {NULL};
    node_t c1 = {NULL};
    node_t d1 = {NULL};
    node_t e1 = {NULL};
    node_t f1 = {NULL};
    node_t first1 = {NULL};
 

	a1.data = (void *)7; 
	b1.data = (void *)6;
	c1.data = (void *)5;
	d1.data = (void *)4; 
	e1.data = (void *)3;
	f1.data = (void *)2;
	first1.data = (void *)1;
	

    a1.next = &d1;
    b1.next = &a1;
    c1.next = &b1;
    d1.next = &c1;
    e1.next = &d1;
    f1.next = &e1;
    first1.next = &f1;
 
    head = &first1;

	if ((SUCCESS_BOL) != HasLoop(head))
	{
		printf("TestHasLoopWithLoop error at line: %d\n", __LINE__);
	}


	return;
}

/*list1  : firat -> f -> e -> d -> c -> b -> a -> last */
/*list2  : firat -> c -> b -> a -> last */
static void TestFindInteNoIter()
{
	node_t *head1 = NULL;

	node_t last1 = {NULL};
    node_t a1 = {NULL};
    node_t b1 = {NULL};
    node_t c1 = {NULL};
    node_t d1 = {NULL};
    node_t e1 = {NULL};
    node_t f1 = {NULL};
    node_t first1 = {NULL}; 
 
 	node_t *head2 = NULL;

	node_t last2 = {NULL};
    node_t a2 = {NULL};
    node_t b2 = {NULL};
    node_t c2 = {NULL};
    node_t first2 = {NULL}; 
 
 
 	last1.data = (void *)8;  
	a1.data = (void *)7; 
	b1.data = (void *)6;
	c1.data = (void *)5;
	d1.data = (void *)4; 
	e1.data = (void *)3;
	f1.data = (void *)2;
	first1.data = (void *)1;
	
	
	
    last1.next = NULL;
    a1.next = &last1;
    b1.next = &a1;
    c1.next = &b1;
    d1.next = &c1;
    e1.next = &d1;
    f1.next = &e1;
    first1.next = &f1;
 
 	last2.data = (void *)5;  
	a2.data = (void *)4; 
	b2.data = (void *)3;
	c2.data = (void *)2;
	first2.data = (void *)1;
	
    last2.next = NULL;
    a2.next = &last2;
    b2.next = &a2;
    c2.next = &b2;
    first2.next = &c2;

    head1 = &first1; 
    head2 = &first2;

	if (NULL != FindIntersection(head1, head2))
	{
		printf("TestFindInteNoIter error at line: %d\n", __LINE__);
	}

	return;
}

/*list1  : firat1 -> f1 -> e1 -> d1 -> c1 -> b1 -> a1 -> last1 */
/*list2  : firat2 -> c2 -> c1 -> b1 -> a1 -> last1 */
static void TestFindInterWithIinter()
{
	node_t *head1 = NULL;
	
	node_t last1 = {NULL};
    node_t a1 = {NULL};
    node_t b1 = {NULL};
    node_t c1 = {NULL};
    node_t d1 = {NULL};
    node_t e1 = {NULL};
    node_t f1 = {NULL};
    node_t first1 = {NULL}; 
 
 	node_t *head2 = NULL;

    node_t c2 = {NULL};
    node_t first2 = {NULL}; 

 	last1.data = (void *)8;  
	a1.data = (void *)7; 
	b1.data = (void *)6;
	c1.data = (void *)5;
	d1.data = (void *)4; 
	e1.data = (void *)3;
	f1.data = (void *)2;
	first1.data = (void *)1;
	
    last1.next = NULL;
    a1.next = &last1;
    b1.next = &a1;
    c1.next = &b1;
    d1.next = &c1;
    e1.next = &d1;
    f1.next = &e1;
    first1.next = &f1;
 

	c2.data = (void *)2;
	first2.data = (void *)1;
	

    c2.next = &c1;
    first2.next = &c2;

    head1 = &first1; 
    head2 = &first2;
    
    if (&c1 != FindIntersection(head1, head2))
	{
		printf("TestFindInterWithIinter error at line: %d\n", __LINE__);
	}

	return;
}
/*

static void printList(node_t *head)
{
    size_t i = 1;

    while (NULL != head)
    {
        printf("Node %ld: %d\n", i , (int)(int *)(head->data));
        head = head->next;
        i++;
    }
    return;
}

*/



