
/*  Developer: Shelly Shlomi;									*
 *  Status:in dev;												*
 *  Date Of Creation:19.04.21;									*
 *  Date Of Approval:--.04.21;									*
 *  Approved By: ;												*
 *  Description: singly link list data structure;				*/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "sll.h"

/*typedef struct (s_list_node *)s_list_node_t; .c*/
/*typedef s_list_node_t s_list_iter_t; .h*/


struct s_list_node
{
	void *data;
	s_list_iter_t next;
	
};

struct s_list
{
	s_list_iter_t head;
	s_list_iter_t tail;
};

/* approved by nir */
s_list_t *SLLCreate(void)
{
	s_list_iter_t dummy = NULL;
	s_list_t *list = (s_list_t *)malloc(sizeof(s_list_t));

	if (NULL == list)
	{    
		return NULL;
	}

	dummy = (s_list_iter_t)malloc(sizeof(struct s_list_node));

	if (NULL == dummy)
	{    
		free(list);
		
		return NULL;
	}
	
	dummy->data = (void *)list;
	dummy->next = NULL;
	
	list->head = dummy;
	list->tail = dummy;

	return list;

}
/*distroy not final!*/
void SLLDestroy(s_list_t *list)
{
	
	s_list_iter_t free_node = list->head;
	s_list_iter_t temp_node = free_node->next;
	
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
	
	list = NULL;
	return;

}
