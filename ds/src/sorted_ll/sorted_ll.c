
/*  Developer: Shelly Shlomi;									*
 *  Status:done;												*
 *  Date Of Creation:28.04.21;									*
 *  Date Of Approval:--.04.21;									*
 *  Approved By: Last Reviewer - Anna Pest;						*
 *  Description:Sorted doubly link list data structure;			*/

#include <assert.h> /* assert */
#include <stdlib.h>	/* malloc */

#include "sorted_ll.h"

#define SUCCESS 1
#define FAILURE 0


struct sorted_list
{
	d_list_t *sorted_list;
	int (*cmp_func)(const void *data, const void *param);
};


typedef struct data_and_list_encp
{
	void *data;
	sorted_list_t *list;

}data_and_list_t;

	
static sorted_list_iter_t DLLToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list);
static d_list_iter_t SortedToDLListIter(sorted_list_iter_t sort_iter);

static int IsBiger(const void *data1,const void *data2);
static data_and_list_t StructFunc(const void *data, sorted_list_t *list);


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




int SortedLLIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);	
		
	return (DLLIsEmpty(list->sorted_list));
}




size_t SortedLLSize(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);	
		
	return (DLLSize(list->sorted_list));
}




sorted_list_iter_t SortedLLBegin(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	return (DLLToSortedIter(DLLBegin(list->sorted_list), (sorted_list_t *)list));


}




sorted_list_iter_t SortedLLEnd(const sorted_list_t *list)
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	return (DLLToSortedIter(DLLEnd(list->sorted_list), (sorted_list_t *)list));
}   




sorted_list_iter_t SortedLLNext(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLNext(SortedToDLListIter(iter))); 
	
	return (iter_temp);
}




sorted_list_iter_t SortedLLPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = iter;

	*((d_list_iter_t *)(&iter_temp)) = (DLLPrev(SortedToDLListIter(iter))); 

	return (iter_temp);
}




int SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
	return (DLLIsSameIter(SortedToDLListIter(iter1), SortedToDLListIter(iter2)));
}



sorted_list_iter_t SortedLLFindIf(sorted_list_iter_t from, 
			                      sorted_list_iter_t to,
			                      int (*match_func)(const void *data, const void *param),    
			                      const void *param)
{
	
	sorted_list_iter_t iter_temp = {NULL};
	
	assert(from.sorted_list == to.sorted_list);
	assert(NULL != match_func);
	
	iter_temp = from;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLFind(SortedToDLListIter(from), 
												SortedToDLListIter(to), 
												match_func, param));
	return (iter_temp);

}




sorted_list_iter_t SortedLLFind(sorted_list_iter_t from, 
								sorted_list_iter_t to, 
								const void *data, 
								sorted_list_t *list)
{

	data_and_list_t param_struct = {NULL};
	sorted_list_iter_t iter_temp = {NULL};
		
	assert(from.sorted_list == to.sorted_list);
	assert(from.sorted_list == list);

	param_struct = StructFunc(data, list);
	
	iter_temp = from;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLFind(SortedToDLListIter(from), 
												SortedToDLListIter(to), 
												IsBiger, 
												(void *)(&param_struct)));
	return (iter_temp);
}




void *SortedLLGetData(sorted_list_iter_t iter)
{
	
	return (DLLGetData(SortedToDLListIter(iter)));
}




void *SortedLLPopFront(sorted_list_t *list)                         
{
	assert(NULL != list);

	return (DLLPopFront(list->sorted_list));

}




void *SortedLLPopBack(sorted_list_t *list)                         
{
	assert(NULL != list);
	
	return (DLLPopBack(list->sorted_list));

}




int SortedLLForEach(sorted_list_iter_t from, 
  	             	sorted_list_iter_t to,
                 	int (*action_func)(void *data,void *param),
  	  		     	void *param)
{
	assert(from.sorted_list == to.sorted_list);
	assert(NULL != action_func);
		
	return (DLLForEach(SortedToDLListIter(from), SortedToDLListIter(to), action_func, param));
	
}

sorted_list_iter_t SortedLLInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t insert_iter = {NULL};
	
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	insert_iter = SortedLLFind(SortedLLBegin(list), 
								SortedLLEnd(list), 
								data, 
								list);
									
	return (DLLToSortedIter(DLLInsert(SortedToDLListIter(insert_iter), data), list));
	
	
}





sorted_list_iter_t SortedLLRemove(sorted_list_iter_t iter)
{
	
	sorted_list_iter_t remove_iter = iter;
	
	*((d_list_iter_t *)(&remove_iter)) = DLLRemove(SortedToDLListIter(iter));
	
	return (remove_iter);

}





void SortedLLMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{

	sorted_list_iter_t to = {NULL};	
	sorted_list_iter_t where = {NULL};
	sorted_list_iter_t dest_end = {NULL};
	sorted_list_iter_t src_end = {NULL};
	sorted_list_iter_t src_begin = {NULL};
	
	assert(NULL != src_list);
	assert(NULL != dest_list);
	assert(dest_list != src_list); 
	
	where = SortedLLBegin(dest_list);/* take the data for find */
	
	dest_end = SortedLLEnd(dest_list);
	src_end = SortedLLEnd(src_list);
	
	src_begin = SortedLLBegin(src_list);
	to = SortedLLBegin(src_list);
						 
	while (!SortedLLIsEmpty(src_list)) 
			
	{
		if (SortedLLIsEmpty(dest_list))
		{
		
			DLLSplice(SortedToDLListIter(where), 
					  SortedToDLListIter(src_begin),
					  SortedToDLListIter(src_end)
					  );
			return;
	
		}
	/* 	if the begining of dest is smallr then the beginig of src - 
		look for the new where in dest wich is larger then the src beging    */
		where = SortedLLFind(where, dest_end, SortedLLGetData(src_begin), dest_list);
	
	/*look for the TO in src wich is larger then the WHERE in dest - SortedToDLListIter(to)*/		
		to = SortedLLFind(src_begin, src_end, SortedLLGetData(where), src_list);
		
	/* 	if the to and the where are equle looks for the first to of the smaller data
		new data needs to be insert after */	
		
		while (0 == src_list->cmp_func(	SortedLLGetData(SortedLLPrev(to)), 
										SortedLLGetData(where)))
		{
			to = SortedLLPrev(to);
		
		}
	
		DLLSplice(	SortedToDLListIter(where), 
					SortedToDLListIter(src_begin), 
					SortedToDLListIter(to));
		
		src_begin = SortedLLBegin(src_list);

	}
	
	return;
	
}






static sorted_list_iter_t DLLToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list)
{
	sorted_list_iter_t iter;
	
	assert(NULL != iter_dll);
	assert(NULL != list);
 	
	#ifdef NDEBUG
	
	(void)list;
	(void)iter;
	return ((sorted_list_iter_t)iter_dll);

	#else
	
	iter.d_iter = iter_dll;
	iter.sorted_list = list;
	return (iter);
	
	#endif
 	
}




static d_list_iter_t SortedToDLListIter(sorted_list_iter_t sort_iter)
{	
	#ifdef NDEBUG
	return ((d_list_iter_t)sort_iter);

	#else
	assert(NULL != sort_iter.d_iter);
	
	return ((d_list_iter_t)(sort_iter.d_iter));

	#endif

}

/*

static int IsMach(const void *data1,const void *data2)
{
	if (0 < (((data_and_list_t *)data2)->list->cmp_func(
									data1, (((data_and_list_t *)data2)->data))))
	{
		return !EXIT_SUCCESS; 		
	}
	
	return !EXIT_FAILURE; 		

}


*/

static int IsBiger(const void *data1,const void *data2)
{
	if (0 < (((data_and_list_t *)data2)->list->cmp_func(
									data1, (((data_and_list_t *)data2)->data))))
	{
		return !EXIT_SUCCESS; 		
	}
	
	return !EXIT_FAILURE; 		

}




static data_and_list_t StructFunc(const void *data, sorted_list_t *list)
{

	data_and_list_t data_and_list = {NULL};
		
	assert(NULL != list);
	
	data_and_list.data = (void *)data;
	data_and_list.list = list;
	
	return data_and_list; 		 		
}




