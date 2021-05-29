/*
 * note: the implementation of fsa here i did that the function (init) aligned the block to word
 * size, thats why free and alloc functions will have the same implementation for 
 * q 1.3 and for 1.1. In the case of 1.1 the init will not aligned the block to word size.
 * 
 * q	1 - fsa 
 *	malloc O(1)
 */

void *FSAAlloc(fsa_t *fsa)
{
	fsa_block_header_t *temp = NULL;

	assert(fsa);

	if (0 == FSACountFree(fsa))
	{
		return (NULL);
	}

	temp = (fsa_block_header_t *)(fsa->next_free + (char *)fsa);
	fsa->next_free += (temp)->next_free + sizeof(fsa_block_header_t);

	return (void *)temp;
}

/*	q	1 - fsa 
 *	free O(1)
 */

void FSAFree(fsa_t *fsa, void *block)
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

/*	q	1 - vsa 
 *	malloc O(n)
 * all the helper funcs arr noted here releted to alloc impl (not the VSADefragment)
 */
/*
#define VSA_SIZE sizeof(vsa_t)
#define CHUNK_SIZE sizeof(vsa_c_h_t)
#define LONG_CHUNK_SIZE (long int)(sizeof(vsa_c_h_t))
#define WORDSIZE sizeof(size_t)

#define END_OF_CHUNK_H(X) ((vsa_c_h_t *)((char *)(X) + CHUNK_SIZE))
#define NEXT_CHUNK(X) ((vsa_c_h_t *)(((char *)(X) + \
									 (size_t)labs((X)->c_size)) + CHUNK_SIZE))
#define FIRST_CHUNK(X) (vsa_c_h_t *)((vsa_c_h_t *)(X) + 1)
#define MOVE_CHUNK(X, Y) (vsa_c_h_t *)(((char *)(X)) + (Y) + CHUNK_SIZE)	
#define USER_CHUNK_START(X) (void *)((vsa_c_h_t *)(X) + 1)	
#define END_OF_POOL_AS_CHUNK_TYPE(X) ((vsa_c_h_t *)((char *)(X) + \
													VSA_SIZE + (X)->pool_size))	
*/

void *VSAAlloc(vsa_t *vsa, size_t n_bytes)
{
	void *chunk_h = NULL;

	assert(NULL != vsa);
	assert(0 < n_bytes);

	n_bytes += GetAlinedTop(n_bytes);

	chunk_h = AllocLasy(vsa, n_bytes);
	if (NULL != chunk_h)
	{
		return (chunk_h);
	}

	VSADefragment(vsa);
	return (AllocLasy(vsa, n_bytes));
}

static void *AllocLasy(vsa_t *vsa, size_t n_bytes)
{
	vsa_c_h_t *vsa_end_addres = NULL;
	vsa_c_h_t *chunk_h = NULL; /*vsa chunk header typedef*/
	long int local_n_bytes = (long int)n_bytes;
	long int cur_c_size = 0;

	assert(NULL != vsa);
	assert(0 < n_bytes);

	vsa_end_addres = END_OF_POOL_AS_CHUNK_TYPE(vsa);

	chunk_h = FIRST_CHUNK(vsa);

	while ((END_OF_CHUNK_H(NEXT_CHUNK(chunk_h)) < vsa_end_addres) &&
		   (chunk_h->c_size < local_n_bytes))
	{
		chunk_h = NEXT_CHUNK(chunk_h);
	}
	/* 
	 * if we break uot of the loop becuase chunk_h->c_size is > n_bytes
	 * need to test if we can add a new chunk header and not overflow to memory
	 * out of the bondery 
	 * END_OF_CHUNK_H - end of chunk header
	 */
	if ((END_OF_CHUNK_H(MOVE_CHUNK(chunk_h, n_bytes)) <= vsa_end_addres) &&
		(chunk_h->c_size >= local_n_bytes + LONG_CHUNK_SIZE))
	{
		cur_c_size = chunk_h->c_size;
		chunk_h->c_size = (-1) * local_n_bytes;

		/* the new chunk head get the reminder from the old size - n_byts */
		(NEXT_CHUNK(chunk_h))->c_size = cur_c_size - LONG_CHUNK_SIZE - local_n_bytes;

		return (USER_CHUNK_START(chunk_h));
	}
	/*if we break uot of the loop becuase chunk_h->c_size is == n_bytes*/
	else if (chunk_h->c_size == local_n_bytes)
	{
		chunk_h->c_size = -(chunk_h->c_size);

		return (USER_CHUNK_START(chunk_h));
	}

	return (NULL);
}

static size_t GetAlinedTop(size_t data)
{
	size_t align_diff = 0;

	/* setiing data to WORDSIZE alignment */
	align_diff = (WORDSIZE - (data & (WORDSIZE - 1))); /* WORDSIZE - (% WORDSIZE) */
	/* % WORDSIZE to avoid addition of WORDSIZE when the data is aligned */
	align_diff &= (WORDSIZE - 1);
	return (align_diff);
}

/*	q	1 - vsa 
 *	free O(1)
 */
 
void VSAFree(void *chunk)
{
	assert(block);
	assert(0 > chunk_h->c_size);
	
	((vsa_c_h_t *)chunk - 1)->c_size *= -1;  
	
	return ; 

}

/*	q	2 
 *	flip O(n)
 * base on list with no dummy 
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

/* q	3.1
 * 
 * base on list with dummy the sll impl did in the class
 * 
 * next O(1)
 * remove O(1)
 * insert O(1), amortize on failure O(n)
 * creat O(1) time
 * destroy O(n)
 * count O(n)
 * IsSameIter O(1)
 * GetData O(1)
 * end O(1)
 * begin O(1)
 */

/* q	3.2.a 
 * HasLoop
 * base on list with no dummy
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
			return (1);
		}
	}

	return (0);
}

/* q	3.2.b
 * OpenLoop
 * base on list with no dummy
 * static node_t *NodeLoop(node_t *head)
 */

node_t *NodeLoop(node_t *head)
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
			return (fast);
		}
	}

	return (NULL);
}

int OpenLoop(node_t *head)
{
	node_t *fast = head;
	node_t *slow = head;

	assert(head);

	fast = NodeLoop(head);

	if (!fast)
	{
		return (0);
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

	return (1);
}

/*	q	3.3.a
 *	HasIntersection
 *  base on list with no dummy
 */
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

/*	q	3.3.b
 *	SplitIntersection
 *  base on list with no dummy
 */

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

	while (NULL != head_1->next)
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

	while (NULL != head)
	{
		head = head->next;
		++counter;
	}
	return (counter);
}

/*	q	4
 *	SLLRemove
 *  base on list with dummy
 */

void SLLRemove(node_t *node)
{
	s_list_iter_t temp = NULL;
	s_list_t *list = NULL;

	assert(node);

	temp = node->next;
	*node = *temp;
	
	if (node->next == NULL)
	{
		list = node->data;
		list->tail = node;
	}
	
	free(temp);

	return;
}

/*	q	5.1
 *	DLLRemove
 * 	
 */

void DLLRemove(node_t *node)
{
	node_t *temp1 = NULL;
	node_t *temp2 = NULL;
	node_t *to_free = node;

	assert(node);

	temp1 = node->next;
	temp2 = node->prev;

	free(to_free);
	to_free = NULL;

	temp2->next = temp1;
	temp1->prev = temp2;

	return;
}

/*	q	5.2
 *	DLLInsert
 * 
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

	node->data = data;
	node->next = where;
	node->prev = where->prev;

	where->prev->next = node;
	where->prev = node;

	return (0);
}

/*	q	6
 *	FindMissingNum
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

/*	q	7
 *	IsInSape
 * 
 */
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
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]) && && && &&)
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



/*
 * q 8
 * PushChar
 * PopChar
 */

#define Q_SIZE 6
typedef struct circular_queue
{
	char queue[Q_SIZE];
	size_t size; /*the num of elem in the queue*/
	size_t read; /*index to read from*/

} cq_t;

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

	chr = que->queue[que->read % Q_SIZE];

	que->read = (que->read + 1) % Q_SIZE;
	--que->size;

	return chr;
}

