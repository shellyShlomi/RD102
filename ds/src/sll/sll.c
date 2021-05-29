
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;											*
 *  Date Of Creation:19.04.21;									*
 *  Date Of Approval:20.04.21;									*
 *  Approved By: final approved by NIR;							*
 *  Description: singly link list data structure;				*/


#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll.h"

#define FAILE 1

typedef struct s_list_node *s_list_node_ptr_t;

static int CountNode(void *data,void *param);

struct s_list_node
{
	void *data;
	s_list_node_ptr_t next;
	
};

struct s_list
{
	s_list_node_ptr_t head;
	s_list_node_ptr_t tail;
};

/* approved by nir */
s_list_t *SLLCreate(void)
{
	s_list_node_ptr_t dummy = NULL;
	
	s_list_t *list = (s_list_t *)malloc(sizeof(s_list_t));

	if (NULL == list)
	{    
		return NULL;
	}

	dummy = (s_list_node_ptr_t)malloc(sizeof(struct s_list_node));

	if (NULL == dummy)
	{    
		free(list);
		
		return NULL;
	}
	
	SLLSetData(dummy, list);
	
	dummy->next = NULL;

	list->head = dummy;
	list->tail = dummy;

	return list;

}


/* approved by nir */
int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

/* Approved by Shir */
s_list_iter_t SLLBegin(const s_list_t *list)
{
	assert(NULL != list);

	return list->head;
}

/* Approved by Shir */
s_list_iter_t SLLEnd(const s_list_t *list)
{
	assert(NULL != list);

	return list->tail;
}

/* approved by nir */
s_list_iter_t SLLNext(const s_list_iter_t iter)
{
	assert(NULL != iter);

	return iter->next;
}

/* approved by nir */
int SLLIsEmpty (const s_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->tail);
	assert(NULL != list->head);

	return SLLIsSameIter(list->tail, list->head);
}

/* approved by nir */
void SLLSetData(s_list_iter_t iter, void *data)
{
	assert(NULL != iter);
	
	iter->data = data;

	return;
}

/* approved by nir */
void *SLLGetData(const s_list_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;

}

/* Approved by Shir */
s_list_iter_t SLLInsert(s_list_iter_t where, void *data)
{
	s_list_node_ptr_t node = NULL;
	
	assert(NULL != where);
	
	node = (s_list_node_ptr_t)malloc(sizeof(struct s_list_node));
	
	if (NULL == node)
	{   
		while (NULL != SLLNext(where))
		{
			where = SLLNext(where);
		}
		
		return (where);
	}

	if (NULL == SLLNext(where))
	{
		((s_list_t *)SLLGetData(where))->tail = node;
	}
	
	*node = *where;
	
	SLLSetData(where, data);
	
	where->next = node;
	
	return (where);

}

/* Approved by Shir */
int SLLForEach(s_list_iter_t from,
        s_list_iter_t to,
        int (*action_func)(void *data,void *param),void *param)
{
	int val = 1;
	
	assert(NULL != action_func);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!SLLIsSameIter(from, to))
	{
		val = action_func(SLLGetData(from), param);
		
		if (0 != val)
		{
			return (val);
		}
		
		from = SLLNext(from);
	}
	return (val);
}

/* Approved by Shir */

s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	size_t temp = (size_t)SLLNext(iter);
	
	assert(NULL != iter);
		
	*iter = *(SLLNext(iter));

	SLLSetData((s_list_node_ptr_t)temp, NULL);
	
	((s_list_node_ptr_t)temp)->next = NULL;

	if (NULL == SLLNext(iter))
	{
		((s_list_t *)SLLGetData(iter))->tail = iter;
	}
	
	free((void *)temp);

	return (iter);
	
}

/*test if push back failedtest if find failed secound part*/


/* Approved by Shir */
void SLLDestroy(s_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->head);
	assert(NULL != list->tail);
	
	while (!SLLIsSameIter(SLLBegin(list), SLLEnd(list)))
	{
		SLLRemove(SLLBegin(list));
	}
	
	SLLSetData(SLLBegin(list), NULL);
	
	free(SLLBegin(list));
	
	list->head = NULL;
	list->tail = NULL;

	free(list);
	
	return;
}

/* Approved by Shir */
size_t SLLCount(const s_list_t *list)
{
	size_t param = 0;
	
	assert(NULL != list);

	SLLForEach(SLLBegin(list), SLLEnd(list), CountNode, (void *)&param);
	
	return param;
}

/* Approved by Shir */
s_list_iter_t SLLFind(  s_list_iter_t from,
                        s_list_iter_t to,
                        int (*match_func)(const void * data,void *param),    
                        void *param)
{

	int match = 1;

	assert(NULL != match_func);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!SLLIsSameIter(from, to))
	{
		match = match_func(SLLGetData(from), param);
		
		if ((!FAILE) == match)
		{
			return from; 
		}
		
		from = SLLNext(from);
	}
	
	return to; 
}

/*eden boy approved*/
void SLLAppend(s_list_t *dest, s_list_t *src)
{

	assert(NULL != src);
	assert(NULL != dest);
	
	if(SLLIsEmpty(src))
	{
		return ;
	}
	
	*(SLLEnd(dest)) = *(SLLBegin(src));
	
	SLLEnd(src)->data = (void *)dest;
	
	dest->tail = src->tail;
	
	/* the dest list is ready */
	
	/* the next two steps makes the head of src to be dummy */
	SLLSetData(SLLBegin(src), (void *)src); 	
	
	(src->head)->next = NULL;

	/* close the src lise to be empty (head and tail points to dummy)*/	
	src->tail = src->head;
	
	return ;
	
}


static int CountNode(void *data,void *param)
{
	(void)data;
	
	*(size_t *)param = *(size_t *)param + 1;

	return EXIT_SUCCESS; 
}


