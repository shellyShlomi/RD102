
/*  Developer: Shelly Shlomi;									*
 *  Status:in dev;												*
 *  Date Of Creation:19.04.21;									*
 *  Date Of Approval:--.04.21;									*
 *  Approved By: ;												*
 *  Description: singly link list data structure;				*/


#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#include "sll.h"

#define FAILE 1
static int CountNode(void *data,void *param);

typedef struct s_list_node *s_list_node_ptr_t;
/*typedef s_list_node_t s_list_iter_t; .h*/

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

s_list_iter_t SLLBegin(const s_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->head);

	return list->head;
}

s_list_iter_t SLLEnd(const s_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->tail);

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

s_list_iter_t SLLInsert(s_list_iter_t where, void *data)
{
	s_list_node_ptr_t iter = NULL;
	
	assert(NULL != where);
	
	iter = (s_list_node_ptr_t)malloc(sizeof(struct s_list_node));
	
	if (NULL == iter)
	{   
		while (NULL != SLLNext(where))/* for each */
		{
			where = SLLNext(where);
		}
		return (where);
				
	}

	if (NULL == SLLNext(where))
	{
		((s_list_t *)where->data)->tail = iter;
	}
	
	*iter = *where;
	
	SLLSetData(where, data);
	
	where->next = iter;
	
	return (where);

}

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
		val = (*action_func)(SLLGetData(from), param);
		
		if (!(!val))
		{
			return (val);
		}
		
		from = SLLNext(from);
	}
	return (val);
}

s_list_iter_t SLLRemove(s_list_iter_t iter)
{
	size_t temp = (size_t)SLLNext(iter);
	
	assert(NULL != SLLNext(iter));
		
	*iter = *(SLLNext(iter));

	((s_list_node_ptr_t)temp)->data = NULL;
	((s_list_node_ptr_t)temp)->next = NULL;

	if (NULL == SLLNext(iter))
	{
		((s_list_t *)iter->data)->tail = iter;
	}
	
	free((void *)temp);

	return (iter);
	
}
void SLLDestroy(s_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->head);
	
	while (!SLLIsSameIter(SLLBegin(list), SLLEnd(list)))
	{
		SLLRemove(SLLBegin(list));
	}
	
	free(SLLBegin(list));
	
	list->head = NULL;
	list->tail = NULL;

	free(list);
	
	return;
}
size_t SLLCount(const s_list_t *list)
{
	size_t param = 0;

	SLLForEach(SLLBegin(list), SLLEnd(list), CountNode, (void *)&param);
	
	return param;
}


s_list_iter_t SLLFind(  s_list_iter_t from,
                        s_list_iter_t to,
                        int (*match_func)(const void * data,void *param),    
                        void *param)
{

	int match = 0;
	
	while (!SLLIsSameIter(from, to))
	{
		match = (*match_func)(SLLGetData(from), param);
		
		if ((!FAILE) == match)
		{
			return from; 
		}
		
		from = SLLNext(from);
	}
	
	return to; 

}



static int CountNode(void *data,void *param)
{
	(void)data;
	
	*(size_t *)param = *(size_t *)param + 1;
	

	return EXIT_SUCCESS; 
}





/*distroy not final!*/

/*
void SLLDestroy(s_list_t *list)
{
	s_list_node_ptr_t free_node = list->head;
	s_list_node_ptr_t temp_node = free_node->next;
	
	assert(NULL != list);
	assert(NULL != list->head);

	while (NULL != free_node->next)
	{
		free_node->data = NULL;
		free_node->next = NULL;

		free(free_node);
		
		free_node = temp_node;
		temp_node = free_node->next;
	}
	
	free_node->data = NULL;
	
	free(free_node);
	
	list->head = NULL;
	list->tail = NULL;

	free(list);
	

	return;

}*/
