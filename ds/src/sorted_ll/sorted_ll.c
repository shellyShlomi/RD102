
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
	d_list_t *sorted_ll;
	int (*cmp_func)(const void *data, const void *param);
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
	
	sorted->sorted_ll = DLLCreate();
	
	if (NULL == sorted->sorted_ll)
	{    
		sorted->sorted_ll = NULL;
		
		free(sorted);
		
		return NULL;
	}
	
	sorted->cmp_func = cmp_func;
	
	return (sorted);
}


void SortedLLDestroy(sorted_list_t *list)                    
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);	
		
	DLLDestroy(list->sorted_ll);
	
	list->sorted_ll = NULL;
	list->cmp_func = NULL;
	
	free(list);
	
	return ;
}	


int SotedLLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);	
		
	return (DLLIsEmpty((const d_list_t *)list->sorted_ll));
}



size_t SortedLLSize(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);	
		
	return (DLLSize((d_list_t *)list->sorted_ll));
}

sorted_list_iter_t SortedLLBegin(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);
	
	return (ToSortedIter(DLLBegin(list->sorted_ll), (sorted_list_iter_t *)list));


}

sorted_list_iter_t SortedLLEnd(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_ll);
	
	return (ToSortedIter(DLLEnd(list->sorted_ll), (sorted_list_iter_t *)list));
}   

sorted_list_iter_t SortedLLNext(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;
	iter_temp.node = DLLNext((d_list_iter_t)(iter.node)); 
	return (iter_temp);
}

sorted_list_iter_t SortedLLPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;
	iter_temp.node = DLLPrev((d_list_iter_t)(iter.node)); 
	return (iter_temp);
}

int SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{

	return (DLLIsSameIter(ToDListIter(iter1), ToDListIter(iter2)));
}


/*
void *           SortedLLGetData    (sorted_list_iter_t iter);


sorted_list_iter_t SortedLLRemove     (sorted_list_iter_t iter);

sorted_list_iter_t SortedLLInsert     (sorted_list_t *list, void *data);

void *		     SortedLLPopFront   (sorted_list_t *list);                              

void *           SortedLLPopBack    (sorted_list_t *list); 

sorted_list_iter_t SortedLLFind       (sorted_list_iter_t from, sorted_list_iter_t to, const void *data);

sorted_list_iter_t SortedLLFindIf     (sorted_list_iter_t from, 
				                     sorted_list_iter_t to,
				                     int (*match_func)(const void *data, const void *param),    
				                     const void *param);
				                   		                   
int              SortedLLForEach    (sorted_list_iter_t from, 
				      	             sorted_list_iter_t to,
				                     int (*action_func)(void *data,void *param),
				      	  		     void *param);

void 			 SortedLLMerge	    (sorted_list_t *dest_list, sorted_list_t *src_list);

*/
static sorted_list_iter_t ToSortedIter(d_list_iter_t iter_dll, sorted_list_iter_t *list)
{
	sorted_list_iter_t iter;
	
	assert(NULL != iter_dll);
	assert(NULL != list);
 	
	#ifdef NDEBUG
	
	(void)list;
	return ((sorted_list_iter_t)iter_dll);

	#else
	
	iter.node = iter_dll;
	iter.list = (struct sorted_list *)list;
	return (iter);
	
	#endif
 	
 	
}
static d_list_iter_t ToDListIter(sorted_list_iter_t sort_iter)
{	
	#ifdef NDEBUG
	return ((d_list_iter_t)sort_iter);

	#else

	return ((d_list_iter_t)(sort_iter.node));

	#endif

}





