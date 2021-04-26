#include <stddef.h> /* size_t */
#include <stdio.h> 	/* printf */
#include <assert.h>	/* assert */


typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
	
};

int HasIntersection(node_t *head_1, node_t *head_2);
static void SplitIntersection(node_t *head_1, node_t *head_2);
static void Offset(node_t **head,size_t head_offset);
static size_t CountElemInList(node_t *head);

static void TestHasIntersectionWith();
static void TestHasIntersection();
static void TestSplitIntersection();
static void TestSplitIntersectionWith();

int main()
{
	TestHasIntersectionWith();
	TestHasIntersection();
	
	TestSplitIntersection();
	TestSplitIntersectionWith();
	return (0);
}


int HasIntersection(node_t *head_1, node_t *head_2)
{

	assert(NULL != head_1);
	assert(NULL != head_2);

	while (NULL != head_1->next)
	{
		head_1 = head_1->next;
	}

	while (NULL != head_2->next)
	{
		head_2 = head_2->next;
	}

	return (head_1 == head_2);
}




static void SplitIntersection(node_t *head_1, node_t *head_2)
{
	size_t counter_1 = 0;
	size_t counter_2 = 0;

	assert(NULL != head_1);
	assert(NULL != head_2);

	counter_1 = CountElemInList(head_1);
	counter_2 = CountElemInList(head_2);

	if (counter_1 < counter_2)
	{
		Offset(&head_2, counter_2 - counter_1);
	}
	else
	{
		Offset(&head_1, counter_1 - counter_2);
	}
	
	
	while(NULL != head_1->next)
	{
		if (head_1->next == head_2->next)
		{
			head_1->next = NULL;
			
			break;
		}
		head_1 = head_1->next;
		head_2 = head_2->next;		
	}
	
	
	return;
}

static size_t CountElemInList(node_t *head)
{
	size_t counter = 0;
	
	while(NULL != head)
	{
		head = head->next;
		++counter;
	}
	return (counter);
}

static void Offset(node_t **head, size_t head_offset)
{
	
	while(0 < head_offset && NULL != (*head)->next)
	{
		*head = (*head)->next;
		--head_offset;
	}
	return ;
}

/*list1  : firat1 -> f1 -> e1 -> d1 -> c1 -> b1 -> a1 -> last1 */
/*list2  : firat2 -> c2 -> c1 -> b1 -> a1 -> last1 */
static void TestHasIntersectionWith()
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
    
   
    if (1 != HasIntersection(head1, head2))
	{
		printf("HasIntersection error at line: %d\n", __LINE__);
	}

	return;
}



/*list1  : firat -> f -> e -> d -> c -> b -> a -> last */
/*list2  : firat -> c -> b -> a -> last */
static void TestHasIntersection()
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

	if (0 != HasIntersection(head1, head2))
	{
		printf("TestHasIntersection error at line: %d\n", __LINE__);
	}

	return;
}


/*list1  : firat1 -> f1 -> e1 -> d1 -> c1 -> b1 -> a1 -> last1 */
/*list2  : firat2 -> c2 -> c1 -> b1 -> a1 -> last1 */
static void TestSplitIntersectionWith()
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
    
    SplitIntersection(head1, head2);
   
    if (NULL != d1.next)
	{
		printf("SplitIntersection error at line: %d\n", __LINE__);
	}

	return;
}


/*list1  : firat -> f -> e -> d -> c -> b -> a -> last */
/*list2  : firat -> c -> b -> a -> last */
static void TestSplitIntersection()
{
	size_t size_befor = 0;
	size_t size_after = 0;
	
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

	size_befor = CountElemInList(head1);

	SplitIntersection(head1, head2);

	size_after = CountElemInList(head1);
   
    if (size_after != size_befor)
	{
		printf("SplitIntersection error at line: %d\n", __LINE__);
	}

	return;
}


