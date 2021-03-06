#include <stddef.h>
#include <stdio.h>
#include <assert.h>

#define VSA_SIZE sizeof(vsa_t)
#define CHUNK_SIZE sizeof(vsa_c_h_t)
#define WORDSIZE sizeof(size_t)

#define NEXT_CHUNK(X) (vsa_c_h_t *)((char *)(X) + ((vsa_c_h_t *)(X))->c_size + CHUNK_SIZE)
#define MOVE_CHUNK(X, N) (vsa_c_h_t *)(((char *)(X)) + CHUNK_SIZE + (N))

/* qustion 1.2 malloc
 * comments: forgot casting in line 23;
 * There are a lot of mistakes, i did not do a debug for all;  	
 * test status: fail
 */

void *LazyAlloc(vsa_t *vsa, size_t n)
{
	size_t vsa_end_addr = 0; /*needs to be (vsa_c_h_t *)*/
	long int loc_n = (long int)n;
	vsa_c_h_t *chunk_h = (vsa_c_h_t *)(vsa + 1);

	assert(vsa);

	vsa_end_addr = (size_t)(vsa_c_h_t *)((char *)vsa + VSA_SIZE + vsa->pool_size);

	while (vsa_end_addres <= NEXT_CHUNK(chunk_h))
	{

		if (chunk_h->c_size + (long int)CHUNK_SIZE) => loc_n)
			{
			(MOVE_CHUNK(chunk_h, n))->c_size = chunk_h->c_size -(long int)CHUNK_SIZE) - loc_n;

			chunk_h->c_size = -(loc_n);

			return (void *))(chunk_h + 1);
			}
		if (chunk_h->c_size == local_n_bytes)
		{
			chunk_h->c_size = -(loc_n);

			return (void *))(chunk_h + 1);
		}

		NEXT_CHUNK(chunk_h); /*the chunk is not moving forwords*/
	}
	return (NULL);
}

void *Alloc(vsa_t *vsa, size_t n)
{
	void *chunk = NULL;
	size_t alinged_n = (WORDSIZE - (n & (WORDSIZE - 1))) & (WORDSIZE - 1) + n;

	assert(vsa);

	chunk = LazyAlloc(vsa, alinged_n);
	if (!chunk)
	{
		VSADefragment(vsa);
		return (LazyAlloc(vsa, alinged_n));
	}

	return (chunk);
}

/* qustion 1.2 vsa free
 * test status: no compilation problrms, test passed;
 */
void VSAFree(void *block)
{
	assert(block);

	((vsa_c_h_t *)block - 1)->c_size *= -1;

	return;
}

/* qustion 1.1, 1.3 fsa
 * note: in the implementation the init function aligned the block to word
 * size, there for free and alloc functions will be the same implementation. 
 * test status: test passed;
 * forgot to check if there is a place to alloct
 */

void *Alloc(fsa_t *fsa)
{
	fsa_block_header_t *temp = NULL;

	assert(fsa);

	temp = (fsa_block_header_t *)(fsa->next_free + (char *)fsa + sizeof(fsa_block_header_t));
	fsa->next_free += (size_t)((fsa_block_header_t *)((char *)fsa + fsa->next_free))->next_free;

	return (void *)temp;
}

/* qustion 1.1, 1.3 
 * 
 * test status: no compilation problrms.
 */
void Free(fsa_t *fsa, void *block)
{
	fsa_block_header_t *to_free = ((fsa_block_header_t *)block - 1);
	size_t temp = 0;

	assert(fsa);
	assert(block);

	temp = fsa->next_free;
	fsa->next_free = (size_t)(fsa - (fsa_t *)to_free);
	to_free->next_free = temp - fsa->next_free;
	return;
}

/* qustion 2 sll Flip
 * test status: no compilation problrms,test passed.
 */
node_t *Flip(node_t *head)
{
	node_t *node = head;
	node_t *temp = NULL;
	node_t *next = NULL;

	assert(head);

	while (NULL != node->next)
	{
		next = node->next;
		node->next = temp;
		temp = node;
		node = next;
	}

	node->next = temp;
	return (node);
}
/* qustion 3.1
 * 
 * base on list with dummy the sll impl did in the class
 * free O(1)?? im a dummy!
 * remove O(1)
 * insert O(1)
 * creat O(n) space
 * destroy O(n)
 * count O(n)
 * 
 */

/* qustion 3.2a sll HasLoop
 * test status: no compilation problrms,test passed.
 */

int HasLoop(node_t *head)
{
	node_t *fast = head;
	node_t *slow = head;

	assert(head);

	while (NULL != fast->next && NULL != fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;

		if (slow == fast)
		{
			return (0);
		}
	}

	return (1);
}

/* qustion 3.2b sll OpenLoop
 * test status: no compilation problrms,test passed.
 */

int OpenLoop(node_t *head)
{
	node_t *fast = head;
	node_t *slow = head;

	assert(head);

	fast = NodeLoop(head);

	if (!fast)
	{
		return (1);
	}

	while (slow != fast)
	{
		slow = slow->next;
		fast = fast->next;
	}

	while (slow != fast->next)
	{
		fast = fast->next;
	}

	fast->next = NULL;

	return (0);
}
/* qustion 3.3a sll OpenLoop
 * There are a lot of mistakes, i did not do a debug for all; 
 * test status : fail  	
 */
int HasIntersection(node_t *head_1, node_t *head_2)
{
	size_t size_1 = 0;
	size_t size_2 = 0;
	size_t size = 0;
	size_t offset = 0;
	size_t i = 0;
	node_t *head = head_1;
	node_t *temp = head_1;
	node_t *head_two = head_2;

	assert(NULL != head_1);
	assert(NULL != head_2);

	size_1 = ListSize(head_1);
	size_2 = ListSize(head_2);

	/*	need to be here
	offset = size_1 - size_2;
	size = size_2;
*/
	if (size_1 < size_2)
	{
		head = head_2;
		temp = head_2;
		head_two = head_1;
		offset = size_2 - size_1;
		size = size_1;
	}
	offset = size_1 - size_2;
	size = size_2;

	for (i = 0; i < offset; ++i)
	{
		head = head->next;
	}

	head = temp;

	for (i = 0; i < size; ++i)
	{
		/*need to be at the end !
		head = head->next;
		head_two = head_two->next;	*/

		if (head == head_two)
		{
			return 0;
		}

		head = head->next;
		head_two = head_two->next;
	}

	return 1;
}

static size_t ListSize(node_t *head)
{
	size_t counter = 1;

	while (NULL != head->next)
	{
		head = head->next;
		++counter;
	}
	return (counter);
}

/*boolean v.1-fix*/
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

	return (head_2 == head_1);
}

/*	qustion 3.3.b
 *	SplitIntersection
 * node_t *HasIntersection(node_t *head_1, node_t *head_2)
 *
 * the helper func - what i try to inmplament at q 3.3.a*/
node_t *HasIntersection(node_t *head_1, node_t *head_2)
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

	while (NULL != head_1)
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		head_1 = head_1->next;
		head_2 = head_2->next;
	}

	return NULL;
}

/* qustion 3.3b 
 * comments: there is UNUSED variable
 * test status: no compilation problrms,test passed;
 */
int SplitIntersection(node_t *head_1, node_t *head_2)
{
	size_t size = 0;
	node_t *node = NULL;

	assert(NULL != head_1);
	assert(NULL != head_2);

	node = HasIntersection(head_1, head_2);

	if (!node)
	{
		return (1);
	}

	while (head_1->next != node)
	{
		head_1 = head_1->next;
	}

	head_1->next = NULL;

	return (0);
}

/* qustion 4 SLLRemove
 * test status: no compilation problrms,test passed; 
 */

void SLLRemove(s_list_node *node)
{
	s_list_node *temp = NULL;
	s_list_t *list = NULL;

	assert(node);

	if (node->next->next == NULL)
	{
		list = node->next->data;
		list->tail = node;
	}

	temp = node->next;
	*node = *temp;
	free(temp);

	return;
}

/* qustion 5.1 DLLRemove
 * comments: need to change the name of the free variableto diffrent name;
 * test status: no compilation problrms,test passed after casting fixed;
 */
void DLLRemove(node_t *node)
{
	node_t *temp1 = NULL;
	node_t *temp2 = NULL;
	node_t *free /*1*/ = node;

	assert(node);

	temp1 = node->next;
	temp2 = node->prev;

	free(free /*1*/);

	temp2->next = temp1;
	temp1->prev = temp2;

	return;
}

/* qustion 5.2 DLLInsert
 * comments: more fixes in the code.
 * test status: no compilation problrms,test passed;	
 */	
int DLLInsert(node_t *node, void *data)
{
	node_t *node1 = NULL;
	node_t *prev = NULL;

	assert(node);

	node1 = (node_t *)malloc(sizeof(node_t));

	if (!node1)
	{
		return (1);
	}

	node1->data = data;
	prev = node->prev;
	prev->next = node1;

	node1->prev = prev;
	node1->next = node;

	node->next /*need to be prev*/ = node1;

	return (0);
}

/*v.1-fix*/

d_list_iter_t DLLInsert(d_list_iter_t node, void *data)
{
	d_list_iter_t node1 = NULL;

	assert(node);

	node1 = (d_list_iter_t)malloc(sizeof(d_list_iter_t));

	if (!node1)
	{
		return (node);
	}

	node1->data = data;
	node1->next = node;
	node1->prev = node->prev;

	node->prev->next = node1;
	node->prev = node1;

	return (node1);
}

/* qustion 6 FindMissingNum
 * test status: no compilation problrms,test passed;	
 */	
int FindMissingNum(int arr[], size_t size)
{
	size_t i = 0;
	size_t xor = 0;

	assert(arr);

	for (i = 0; i < size + 1; ++i)
	{
		xor ^= i;
	}

	for (i = 0; i < size; ++i)
	{
		xor ^= arr[i];
	}
	return ((int)xor);
}

/* qustion 8 sll PushChar
 * The impl was not right at the test;	
 */
#define Q_SIZE 6
typedef struct circular_queue
{
	char queue[Q_SIZE];
	size_t size; /*the num of elem in the queue*/
	size_t read; /*index to read from*/

} cq_t;
void PushChar(char c, cq_t *que)
{
	assert(que);
	assert(que->size < Q_SIZE);

	if (que->read - /*que->size*/ que < Q_SIZE)
	{
		que->queue[/*que->*/ read - que->size /* + 1*/] = c;
	}
	else
	{
		que->queue[/*que->*/ read + que->size] = c;
	}

	++que->size;

	return;
}

/*v.1-fix*/

void PushChar(cq_t *que, char c)
{

	assert(que);
	assert(que->size < Q_SIZE);

	que->queue[(que->read + que->size) % Q_SIZE] = c;

	++que->size;

	return;
}

char PopChar(cq_t *que)
{
	char chr = '\0';

	assert(que);
	assert(que->size > 0);

	chr = que->queue[que->read];

	que->read = (que->read + 1) % Q_SIZE;
	--que->size;

	return chr;
}
