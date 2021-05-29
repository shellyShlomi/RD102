
#include <stdio.h> 
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll_ex.h"


/* implementetion */
int OpenLoop(const node_t *head);

/* Test Functions */
static void Test();
static void TestHasLoopNoLoop();
static void TestHasLoopWithLoop();
static void TestFilp();
static void TestOpenLoop();


/* helper functions */
static size_t CountElemInList(node_t *head);
static node_t *PtrLoop(node_t *head);


int main()
{
	Test();
	
	return EXIT_SUCCESS;
}


static void Test()
{
	TestHasLoopNoLoop();
	TestHasLoopWithLoop();
	TestFilp();
	TestOpenLoop();
	
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

	if ((0) != HasLoop(head))
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

	if ((1) != HasLoop(head))
	{
		printf("TestHasLoopWithLoop error at line: %d\n", __LINE__);
	}

	return;
}

static void TestOpenLoop()
{
	node_t elem1 = {NULL, NULL};
	node_t elem2 = {NULL, NULL};
	node_t elem3 = {NULL, NULL};
	node_t elem4 = {NULL, NULL};
	node_t elem5 = {NULL, NULL};
	node_t *head = &elem1;
	
	elem1.next = &elem2;
	elem2.next = &elem3;
	elem3.next = &elem4;
	elem4.next = &elem5;
    elem5.next = &elem3;
    
    OpenLoop(head);
    
    if (NULL != elem5.next)
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    if (1 != OpenLoop(head))
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    elem5.next = &elem1;
    OpenLoop(head);
    
    if (NULL != elem5.next)
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    if (1 != OpenLoop(head))
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    elem5.next = &elem2;
	OpenLoop(head);  
	 
    if (NULL != elem5.next)
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    if (1 != OpenLoop(head))
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    elem5.next = &elem5;
	OpenLoop(head); 
	    
    if (NULL != elem5.next)
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
    
    if (1 != OpenLoop(head))
    {
    	printf("test failed at line: %d\n", __LINE__);
    } 
   
	return;	
}

/*------------------------------implementetion--------------------------------*/
int HasLoop(node_t const *head)
{
	node_t *fast = (node_t *)head;
	node_t *slow = (node_t *)head;
	
	assert(NULL != head);

	while(NULL != fast->next && NULL != fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		
		if (slow == fast)
		{
			return (1);
		}
	}
	
	return (0);
}


node_t *Flip(node_t *head)
{
	node_t *node = head;
	node_t *next = NULL;
	node_t *temp = NULL;

	assert(NULL != head);
	
	next = head->next;
	head->next = NULL;

	while(NULL != next->next)
	{
		temp = next->next;
		next->next = node;
		node = next;
		next = temp; 
	}
	
	next->next = node;
	
	return (next);

}

int OpenLoop(const node_t *head)
{
	node_t *fast = NULL;
	node_t *slow = (node_t *)head;
	
	assert(NULL != head);

	fast = PtrLoop((node_t *)head);
	
	if (NULL == fast)
	{
		return (1);
	}
	
	while(slow != fast)
	{
		fast = fast->next;
		slow = slow->next;
	}
	
	while(slow != fast->next)
	{
		fast = fast->next;
	}
	
	fast->next = NULL;
	
	return (0);
}
/*------------------------------helper functions------------------------------*/

static node_t *PtrLoop(node_t const *head)
{
	node_t *fast = (node_t *)head;
	node_t *slow = (node_t *)head;
	
	assert(NULL != head);

	while(NULL != fast->next && NULL != fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		
		if (slow == fast)
		{
			return (fast);
		}
	}
	
	return (NULL);
}


static size_t CountElemInList(node_t *head)
{
	size_t counter = 1;
	
	while(NULL != head->next)
	{
		head = head->next;
		++counter;
	}
	return (counter);
}

