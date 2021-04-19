
#include <assert.h> /*malloc*/

#include "sll.h"

/*typedef struct (s_list_node *)s_list_node_t; .c*/
/*typedef s_list_node_t s_list_iter_t; .h*/


struct s_list_node
{
	void *data;
	struct s_list_node *next;
	
};

struct s_list
{
	s_list_node_t *head;
	s_list_node_t *tail;
};


s_list_t *SLLCreate(void)
{
	s_list_t *s_list = (s_list_t *)malloc(sizeof(s_list_t));

	if (NULL == s_list)
	{    
		return NULL;
	}

	s_list_iter_t iter = (s_list_iter_t)malloc(sizeof(s_list_node));

	if (NULL == iter)
	{    
		s_list = NULL;
		free(s_list);
		
		return NULL;
	}
	


}
