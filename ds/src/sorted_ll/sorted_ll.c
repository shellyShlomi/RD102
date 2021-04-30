
/*  Developer: Shelly Shlomi;									*
 *  Status:in development;										*
 *  Date Of Creation:28.04.21;									*
 *  Date Of Approval:--.04.21;									*
 *  Approved By: ;												*
 *  Description:Sorted doubly link list data structure;			*/

#include <assert.h> /* assert */
#include <stdlib.h>	/* malloc */

#include "sorted_ll.h"


struct sorted_list
{
	d_list_t *sorted_list;
	int (*cmp_func)(const void *data, const void *param);/*-1,1,0*/
};


static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_iter_t *list);
static d_list_iter_t ToDListIter(sorted_list_iter_t sort_iter);



sorted_list_t *SortedLLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	sorted_list_t *sorted = NULL;
	
	assert(NULL != cmp_func);	
	
	sorted = (sorted_list_t *)malloc(sizeof(sorted_list_t));

	if (NULL == sorted)
	{    
		return NULL;
	}
	
	sorted->sorted_list = DLLCreate();
	
	if (NULL == sorted->sorted_list)
	{    
		sorted->sorted_list = NULL;
		
		free(sorted);
		
		return NULL;
	}
	
	sorted->cmp_func = cmp_func;
	
	return (sorted);
}




void SortedLLDestroy(sorted_list_t *list)                    
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);	
		
	DLLDestroy(list->sorted_list);
	
	list->sorted_list = NULL;
	list->cmp_func = NULL;
	
	free(list);
	
	return ;
}	




int SotedLLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);	
		
	return (DLLIsEmpty((const d_list_t *)list->sorted_list));
}




size_t SortedLLSize(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);	
		
	return (DLLSize((d_list_t *)list->sorted_list));
}




sorted_list_iter_t SortedLLBegin(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	return (ToSortedIter(DLLBegin(list->sorted_list), (sorted_list_iter_t *)list));


}




sorted_list_iter_t SortedLLEnd(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	return (ToSortedIter(DLLEnd(list->sorted_list), (sorted_list_iter_t *)list));
}   




sorted_list_iter_t SortedLLNext(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLNext(ToDListIter(iter))); 
	
	return (iter_temp);
}




sorted_list_iter_t SortedLLPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;

	*((d_list_iter_t *)(&iter_temp)) = (DLLPrev(ToDListIter(iter))); 

	return (iter_temp);
}




int SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
	return (DLLIsSameIter(ToDListIter(iter1), ToDListIter(iter2)));
}



sorted_list_iter_t SortedLLFindIf    (sorted_list_iter_t from, 
				                      sorted_list_iter_t to,
				                      int (*match_func)(const void *data, const void *param),    
				                      const void *param)
{
	
	sorted_list_iter_t iter_temp = {NULL};
	
	assert(NULL != match_func);
	
	*((d_list_iter_t *)(&iter_temp)) = 
	(DLLFind(ToDListIter(from), ToDListIter(to), match_func, param));
	
	return (iter_temp);

}




sorted_list_iter_t SortedLLFind     (sorted_list_iter_t from, 
									sorted_list_iter_t to, 
									const void *data, 
									sorted_list_t *list)
{
	
	int cmopare = 0;

	assert(NULL != list);
	assert(NULL != from);
	assert(NULL != to);
	
	while (!SortedLLIsSameIter(from, to))
	{
		cmopare = list->cmp_func(SortedLLGetData(from), data);
		
		if (0 < cmopare)
		{
			return from; 
		}
		
		from = SortedLLNext(from);
	}
	
	return (to); 
	
}




void *SortedLLGetData(sorted_list_iter_t iter)
{
	
	return (DLLGetData(ToDListIter(iter)));
}




void *SortedLLPopFront(sorted_list_t *list)                         
{

	return (DLLPopFront(list->sorted_list));

}




void *SortedLLPopBack(sorted_list_t *list)                         
{

	return (DLLPopBack(list->sorted_list));

}


int SortedLLForEach(sorted_list_iter_t from, 
  	             	sorted_list_iter_t to,
                 	int (*action_func)(void *data,void *param),
  	  		     	void *param)
{
	
	return (DLLForEach(ToDListIter(from), ToDListIter(to), action_func, param));
	
}



/*


sorted_list_iter_t SortedLLRemove     (sorted_list_iter_t iter);


sorted_list_iter_t SortedLLInsert     (sorted_list_t *list, void *data);


void 			 SortedLLMerge	    (sorted_list_t *dest_list, sorted_list_t *src_list);

*/


static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_iter_t *list)
{
	sorted_list_iter_t iter;
	
	assert(NULL != iter_dll);
	assert(NULL != list);
 	
	#ifdef DEBUG
	
	(void)list;
	return ((sorted_list_iter_t)iter_dll);

	#else
	
	iter.node = iter_dll;
	iter.sorted_list = (struct sorted_list *)list;
	return (iter);
	
	#endif
 	
 	
}




static d_list_iter_t ToDListIter(sorted_list_iter_t sort_iter)
{	
	#ifdef DEBUG
	return ((d_list_iter_t)sort_iter);

	#else

	return ((d_list_iter_t)(sort_iter.node));

	#endif

}





