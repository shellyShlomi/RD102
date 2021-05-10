/*	Group: OL102												*
 *  Developer: Shelly Shlomi;									*
 *  Status:Approved by nir;										*
 *  Date Of Creation:28.04.21;									*
 *  Date Of Approval:02.05.21;									*
 *  Approved By:nir; Last Reviewer tests - Anna Pest;			*
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

/* iner struct for findif - comperator 										*
 * use for the use the findif that accept boolian func and not cmp funcs  	*/
typedef struct data_and_list_encp
{
	const void *data;
	sorted_list_t *list;

}data_and_list_t;

/**************************helper_decleration***********************************/	


static sorted_list_iter_t DLLToSortedIter(d_list_iter_t iter_dll, sorted_list_t *list);
static d_list_iter_t SortedToDLListIter(sorted_list_iter_t sort_iter);

static int IsBigger(const void *user_data,const void *struct_d_and_l);
static int IsBiggerOrEqual(const void *user_data,const void *struct_d_and_l);




/**************************impl_functions***********************************/	
sorted_list_t *SortedLLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	sorted_list_t *sorted = NULL;
	
	assert(NULL != cmp_func);	
	
	sorted = (sorted_list_t *)malloc(sizeof(sorted_list_t));

	if (NULL == sorted)
	{    
		return (NULL);
	}
	
	sorted->sorted_list = DLLCreate();
	
	if (NULL == sorted->sorted_list)
	{    
		free(sorted);
		
		return (NULL);
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
	
	sorted_list_iter_t iter_temp = {NULL};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	iter_temp = iter;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLNext(SortedToDLListIter(iter))); 
	
	return (iter_temp);
}




sorted_list_iter_t SortedLLPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t iter_temp = {NULL};
	
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	iter_temp = iter;

	*((d_list_iter_t *)(&iter_temp)) = (DLLPrev(SortedToDLListIter(iter))); 

	return (iter_temp);
}




int SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2)
{
		
	assert(NULL != iter1.d_iter);
	assert(NULL != iter2.d_iter);
	assert(NULL != iter1.sorted_list);
	assert(NULL != iter2.sorted_list);
	
	return (DLLIsSameIter(SortedToDLListIter(iter1), SortedToDLListIter(iter2)));
}



sorted_list_iter_t SortedLLFindIf(sorted_list_iter_t from, 
			                      sorted_list_iter_t to,
			                      int (*match_func)(const void *data, const void *param),    
			                      const void *param)
{
	
	sorted_list_iter_t iter_temp = {NULL};
	
	assert(NULL != match_func);
	assert(NULL != from.d_iter);	
	assert(NULL != to.d_iter);
	assert(NULL != from.sorted_list);
	assert(NULL != to.sorted_list);
	assert(from.sorted_list == to.sorted_list);
	
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
	sorted_list_iter_t iter_temp = {NULL};
	data_and_list_t cmp_struct = {NULL};

	assert(NULL != list);
	assert(NULL != list->sorted_list);
	assert(NULL != from.d_iter);	
	assert(NULL != to.d_iter);
	assert(NULL != from.sorted_list);
	assert(NULL != to.sorted_list);
	assert(from.sorted_list == to.sorted_list);
	assert(from.sorted_list == list);

	
	iter_temp = from;
	cmp_struct.data = data;
	cmp_struct.list = list;
	
	*((d_list_iter_t *)(&iter_temp)) = (DLLFind(SortedToDLListIter(from), 
												SortedToDLListIter(to), 
												IsBiggerOrEqual, 
												(void *)(&cmp_struct)));
	
	if	((!SortedLLIsSameIter(iter_temp, to)) && 
		(0 == list->cmp_func(SortedLLGetData(iter_temp), data)))
	{
		
			return (iter_temp); 
		
		
	}
	
	return (to);							


}




void *SortedLLGetData(sorted_list_iter_t iter)
{
	assert(NULL != iter.d_iter);
	assert(NULL != iter.sorted_list);
	
	return (DLLGetData(SortedToDLListIter(iter)));
}




void *SortedLLPopFront(sorted_list_t *list)                         
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);

	return (DLLPopFront(list->sorted_list));

}




void *SortedLLPopBack(sorted_list_t *list)                         
{
	assert(NULL != list);
	assert(NULL != list->sorted_list);

	return (DLLPopBack(list->sorted_list));

}




int SortedLLForEach(sorted_list_iter_t from, 
  	             	sorted_list_iter_t to,
                 	int (*action_func)(void *data,void *param),
  	  		     	void *param)
{
	assert(NULL != action_func);
	assert(NULL != from.d_iter);	
	assert(NULL != to.d_iter);
	assert(NULL != from.sorted_list);
	assert(NULL != to.sorted_list);
	assert(from.sorted_list == to.sorted_list);
		
	return (DLLForEach(SortedToDLListIter(from), SortedToDLListIter(to), action_func, param));
	
}

sorted_list_iter_t SortedLLInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t insert_iter = {NULL};
	data_and_list_t cmp_struct = {NULL};
	
	assert(NULL != list);
	assert(NULL != list->sorted_list);
	
	cmp_struct.data = data;
	cmp_struct.list = list;
	
	insert_iter = SortedLLFindIf(SortedLLBegin(list), 
								SortedLLEnd(list),  
								IsBigger,
								(void *)&cmp_struct);
									
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
	data_and_list_t cmp_struct = {NULL};
	
	sorted_list_iter_t to = {NULL};	
	sorted_list_iter_t where = {NULL};
	sorted_list_iter_t dest_end = {NULL};
	sorted_list_iter_t src_end = {NULL};
	sorted_list_iter_t src_begin = {NULL};
		
	assert(NULL != src_list);
	assert(NULL != dest_list);
	assert(dest_list != src_list); 
	assert(NULL != src_list->cmp_func); 
	assert(NULL != dest_list->cmp_func); 
	assert(src_list->cmp_func == dest_list->cmp_func); 	
	
	where = SortedLLBegin(dest_list);/* take the data for find */
	
	dest_end = SortedLLEnd(dest_list);
	src_end = SortedLLEnd(src_list);
	
	src_begin = SortedLLBegin(src_list);
						 
	while (!SortedLLIsEmpty(src_list)) 
	{
	/* 	if the begining of dest is smallr then the beginig of src - 
		look for the new where in dest wich is larger then the src beging    */
		
		cmp_struct.data = SortedLLGetData(src_begin);
		cmp_struct.list = src_list;
		
		where = SortedLLFindIf(where, dest_end, IsBigger, (void *)&cmp_struct);
		
		if (SortedLLIsSameIter(dest_end, where))
		{
			DLLSplice(SortedToDLListIter(where), 
					  SortedToDLListIter(src_begin),
					  SortedToDLListIter(src_end)
					  );
			return;
		}
		
	/* look for the TO in src wich is larger then the WHERE in dest - SortedToDLListIter(to) */		
		cmp_struct.list = src_list;
		cmp_struct.data = SortedLLGetData(where);
		
		to = SortedLLFindIf(src_begin, src_end, IsBiggerOrEqual, (void *)&cmp_struct);
	
		DLLSplice(	SortedToDLListIter(where), 
					SortedToDLListIter(src_begin), 
					SortedToDLListIter(to));
		
		src_begin = SortedLLBegin(src_list);

	}
	
	return;
	
}

/**************************helper_function***********************************/	




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


static int IsBiggerOrEqual(const void *user_data,const void *struct_d_and_l)
{
	assert(NULL != struct_d_and_l);
		

	return (0 <= (((data_and_list_t *)struct_d_and_l)->list->cmp_func(
					user_data, (((data_and_list_t *)struct_d_and_l)->data))));
}




static int IsBigger(const void *user_data,const void *struct_d_and_l)
{
	
	assert(NULL != struct_d_and_l);
		
	return (0 < (((data_and_list_t *)struct_d_and_l)->list->cmp_func(
					user_data, (((data_and_list_t *)struct_d_and_l)->data)))); 		

}



