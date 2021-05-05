/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;											*
 *  Date Of Creation:27.04.21;									*
 *  Date Of Approval:28.04.21;									*
 *  Approved By: OHAD;											*
 *  Description: doubly link list data structure;				*/
 
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "dll.h"

#define FAILE 1

typedef struct d_list_node d_list_node_t;

static int CountNode(void *data,void *param);

struct d_list_node
{
	void *data;
	d_list_iter_t next;
	d_list_iter_t prev;
};

struct d_list
{
	d_list_node_t head_dummy;
	d_list_node_t tail_dummy;
};


d_list_t *DLLCreate(void)
{
	d_list_t *list = (d_list_t *)malloc(sizeof(d_list_t));

	if (NULL == list)
	{    
		return NULL;
	}

	list->head_dummy.data = NULL;	
	list->head_dummy.prev = NULL;
	list->tail_dummy.next = NULL;
	list->tail_dummy.data = NULL;	
	
	list->head_dummy.next = &(list->tail_dummy);
	list->tail_dummy.prev = &(list->head_dummy);

	return (list);

}


int DLLIsSameIter(const d_list_iter_t iter1, const d_list_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

d_list_iter_t DLLBegin(const d_list_t *list)
{
	assert(NULL != list);

	return (list->head_dummy.next);
}

d_list_iter_t DLLEnd(const d_list_t *list)
{
	assert(NULL != list);

	return (d_list_node_t *)&(list->tail_dummy);
}

d_list_iter_t DLLNext(const d_list_iter_t iter)
{
	assert(NULL != iter);

	return (iter->next);
}


d_list_iter_t DLLPrev(const d_list_iter_t iter)
{
	assert(NULL != iter);

	return (iter->prev);
}


int DLLIsEmpty(const d_list_t *list)
{
	assert(NULL != list);

	return (DLLIsSameIter(DLLBegin(list), DLLEnd(list)));
}

d_list_iter_t DLLPushFront(d_list_t *list, void *data)
{
	assert(NULL != list);

	return (DLLInsert(DLLBegin(list), data));
}                             
 
d_list_iter_t DLLPushBack(d_list_t *list, void *data)
{
	assert(NULL != list);

	return (DLLInsert(DLLEnd(list), data));
}                             
  

void *DLLPopFront(d_list_t *list)                             
{
	void *data = NULL;
	assert(NULL != list);

	data = DLLGetData(DLLBegin(list));
	DLLRemove(DLLBegin(list));

	return (data);
} 

void *DLLPopBack(d_list_t *list)
{
	void *data = NULL;
	assert(NULL != list);
	assert(!DLLIsEmpty(list));

	data = DLLGetData(DLLPrev(DLLEnd(list)));
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return (data);
} 

void *DLLGetData(const d_list_iter_t iter)
{
	assert(NULL != iter);
	
	return (iter->data);

}

d_list_iter_t DLLInsert(d_list_iter_t where, void *data)
{
	d_list_iter_t node = NULL;
	
	assert(NULL != where);
	
	node = (d_list_iter_t)malloc(sizeof(struct d_list_node));
	
	if (NULL == node)
	{   
		while (NULL != DLLNext(where))
		{
			where = DLLNext(where);
		}
		
		return (where);
	}
	
	node->data = data;
	node->next = where;
	node->prev = where->prev;
	
	where->prev->next = node;
	where->prev = node;
	
	return (node);

}

int DLLForEach(d_list_iter_t from,
        d_list_iter_t to,
        int (*action_func)(void *data,void *param),void *param)
{
	int val = 0;
	
	assert(NULL != action_func);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!DLLIsSameIter(from, to))
	{
		val = action_func(DLLGetData(from), param);
		
		if (0 != val)
		{
			return (val);
		}
		
		from = DLLNext(from);
	}
	
	return (val);
}
/*cheng*/
d_list_iter_t DLLRemove(d_list_iter_t iter)
{
	d_list_iter_t temp_next = NULL;
	
	assert(NULL != iter->next);

	temp_next = DLLNext(iter);

	iter->prev->next = temp_next; 
	temp_next->prev = iter->prev;
	
	iter->data = NULL;
	iter->next = NULL;
	iter->prev = NULL;

	free(iter);

	return (temp_next);
	
}

void DLLDestroy(d_list_t *list)
{
	assert(NULL != list);

	
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));
	}
	
	list->head_dummy.next = NULL;
	list->tail_dummy.prev = NULL;

	free(list);
	
	return;
}

size_t DLLSize(const d_list_t *list)
{
	size_t param = 0;
	
	assert(NULL != list);

	DLLForEach(DLLBegin(list), DLLEnd(list), CountNode, (void *)&param);
	
	return (param);
}

d_list_iter_t DLLFind(d_list_iter_t from, 
                      d_list_iter_t to,
                      int (*match_func)(const void *data, const void *param),    
                      const void *param)
{

	int match = 0;

	assert(NULL != match_func);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!DLLIsSameIter(from, to))
	{
		match = match_func(DLLGetData(from), param);
		
		if (match)
		{
			return from; 
		}
		
		from = DLLNext(from);
	}
	
	return (to); 
}

int DLLMultiFind(d_list_iter_t from, 
                 d_list_iter_t to,
                 int (*match_func)(const void *data,const void *param),    
                 const void *param,
                 d_list_t *dest_list)
{
	assert(NULL != dest_list);
	assert(NULL != match_func);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!DLLIsSameIter(to, from = DLLFind(from, to, match_func, param)))
	{
		if (NULL == DLLNext(DLLPushBack(dest_list, DLLGetData(from))))
		{
			return (EXIT_FAILURE);
		}
		
		from = DLLNext(from);
	}
		
	return (EXIT_SUCCESS); 
}      

/*return to -  the lest elem that was insert to the new list*/
d_list_iter_t DLLSplice(d_list_iter_t where, 
              			d_list_iter_t from,
         	  			d_list_iter_t to)
{

	d_list_iter_t temp = NULL;

	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);

	temp = where->prev;
	
	where->prev = to->prev;
	
	to->prev = from->prev;
	
	(where->prev)->next = where;
	
	temp->next = from;
	
	(from->prev)->next = to;
	
	from->prev = temp;

	return (where->prev);
}

         	   

static int CountNode(void *data,void *param)
{
	(void)data;
	
	*(size_t *)param = *(size_t *)param + 1;

	return EXIT_SUCCESS; 
}


