/* qustion 1.1, 1.3 	
 * malloc O(1)
 *
 * comment: the implementation of fsa here i did that the function (init) 
 * aligned the block to word size, thats why free and alloc functions will
 * have the same implementation for.
 * q 1.3 and for 1.1. In the case of 1.1 the init will not aligned 
 * the block to word size.
 */

void *FSAAlloc(fsa_t *fsa)
{
	void *temp = NULL;
	
	assert(NULL != fsa);
	
	if (0 == FSACountFree(fsa))
	{
		return (NULL);
	}
	
	temp = (void *)(fsa->next_free + (char *)fsa);
	fsa->next_free = ((fsa_block_header_t *)temp)->next_free;
	
	return (temp);
}

/* qustion 1.2 
 * FSAFree O(1)		
 */

void FSAFree(fsa_t *fsa, void *mem_block)
{
	assert(NULL != mem_block);
	assert(NULL != fsa);
	
	((fsa_block_header_t *)mem_block)->next_free = fsa->next_free;
	fsa->next_free = ((size_t)((char *)mem_block - (char *)fsa));
	
	return ;
}


/* qustion 1 - vsa 
 * VSAAlloc O(n)
 * all the helper funcs arr noted here releted to alloc impl (not the VSADefragment)
 */

/*************************Vsa Macros*********************************/
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
/********************************************************************/
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
	vsa_c_h_t *chunk_h = NULL;
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
	 * if we break out of the loop becuase chunk_h->c_size is > n_bytes
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
	/*if we break out of the loop becuase chunk_h->c_size is == n_bytes*/
	if (chunk_h->c_size == local_n_bytes)
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

/*	qustion 1 
 *	VSAFree O(1)
 */
 
void VSAFree(void *chunk)
{
	assert(block);
	assert(0 > chunk_h->c_size);
	
	((vsa_c_h_t *)chunk - 1)->c_size *= -1;  
	
	return ; 

}

/* qustion 2 
 * Flip O(n)
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

/* qustion 3.2a  
 * HasLoop O(n)
 * 
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

/* qustion 3.2b
 * OpenLoop O(n)
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

/*	qustion 3.3.a
 *	HasIntersection O(n)
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

/*	qustion 3.3.b
 *	SplitIntersection O(n)
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

static void Offset(node_t **head, size_t head_offset)
{
	
	while(0 < head_offset && NULL != (*head)->next)
	{
		*head = (*head)->next;
		--head_offset;
	}
	return ;
}

/*	qustion 4
 *	SLLRemove O(1)
 *  base on list with dummy
 */

void SLLRemove(node_t *node)
{
	node_t *temp = NULL;

	assert(node);

	temp = node->next;
	node->data = temp->data;
	node->next = temp->next;
	
	if (node->next == NULL)
	{
		((list_t *)node->data)->tail = node;
	}
	
	free(temp);

	return;
}

/*	qustion 5 
 *	DLLRemove O(1)
 * 	
 */

void DLLRemove(node_t *node)
{
	assert(NULL != node->next);

	node->prev->next = node->next; 
	node->next->prev = node->prev;
	
	node->data = NULL;
	node->next = NULL;
	node->prev = NULL;

	free(node);

	return;
}


/*	qustion 5.2
 *	DLLInsert O(1)
 * 
 */
int DLLInsert(node_t *where, void *data)
{
	node_t *node = NULL;
	
	assert(where);
	
	node = (node_t *)malloc(sizeof(node_t));
	
	if (!node)
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
/*	qustion 6
 *	FindMissingNum O(n)
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

/* qustion 7
 * IsInSape
 * comment: based on the assumption that the shape has 
 * only 1 corner to the internal side of the shape 
 * O(n + m), n -> size_x_axis, m -> size_y_axis
 */
#define BOOL_FALSE 0
#define BOOL_TRUE 1

#define X_AXIS 10

int IsInSape(size_t size_x_axis, size_t size_y_axis, size_t x, size_t y, size_t matrix[][X_AXIS])
{
    size_t i = 0;
    size_t axis_counter = 0;
    size_t even_odd_counter = 0;
    
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

    if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }

    for (i = 0;i < y; ++i)
    {
        if ((1 == matrix[i][x]) && (0 == matrix[i + 1][x]))
        {
            ++axis_counter;
        }
    }
	
 	if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }
    
    for (i = x + 1; i < size_x_axis - 1; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

 	if (axis_counter & 1)
    {
        ++even_odd_counter;
        axis_counter = 0;
    }


    for (i = 0;i < x; ++i)
    {
        if ((1 == matrix[y][i]) && (0 == matrix[y][i + 1]))
        {
            ++axis_counter;
        }
    }

 	if (axis_counter & 1)
    {
        ++even_odd_counter;
    }
    
    if (3 <= even_odd_counter)
	{
	    return (TRUE);
	}
	
    return (FALSE);
}



/*
 * qustion 8
 * PushChar O(1)
 * PopChar O(1)
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
	
	return ;
}

char PopChar(cq_t *que)
{
	char chr = '\0';
	
	assert(que);
	assert(que->size > 0);
	
	chr = que->queue[que->read];

	que->read = (que->read + 1)% Q_SIZE; 
	--que->size;
	
	return chr;
}

