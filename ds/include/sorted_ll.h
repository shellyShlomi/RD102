#ifndef __OL102_SORTED_LINKED_LIST_H__
#define __OL102_SORTED_LINKED_LIST_H__

#include <stddef.h> /*size_t*/

#include "dll.h"

/*
in c file:

struct sorted_list
{
	d_list_t *list;
	int (*cmp_func)(const void *data, const void *param);
};
*/

typedef struct sorted_list sorted_list_t;

#ifdef NDEBUG

typedef d_list_iter_t sorted_list_iter_t;

#else

typedef struct sorted_list_iter
{
	d_list_iter_t node;
	struct sorted_list *list;
}sorted_list_iter_t;

#endif /* NDEBUG */

/* O(1) */
sorted_list_t *    SortedLLCreate    (int (*cmp_func)(const void *data1, const void *data2));

/* O(n) */
void 			 SortedLLDestroy     (sorted_list_t *list);                    

/* O(1) */
int 			 SotedLLIsEmpty      (const sorted_list_t *list);

/* O(n) */        
size_t           SortedLLSize	     (const sorted_list_t *list);

/* O(1) */
sorted_list_iter_t SortedLLBegin     (const sorted_list_t *list);

/* O(1) */                        
sorted_list_iter_t SortedLLEnd	     (const sorted_list_t *list);   

/* O(1) */               
sorted_list_iter_t SortedLLNext      (const sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLPrev	     (const sorted_list_iter_t iter);

/* O(1) */
int 			   SortedLLIsSameIter(const sorted_list_iter_t iter1, const sorted_list_iter_t iter2);

/* O(1) */
void *             SortedLLGetData   (sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLRemove    (sorted_list_iter_t iter);

/* O(n) */
sorted_list_iter_t SortedLLInsert    (sorted_list_t *list, void *data);

/* O(1) */				                   		                   
void *		       SortedLLPopFront  (sorted_list_t *list);                              

/* O(1) */
void *             SortedLLPopBack   (sorted_list_t *list); 

/* O(n) */
sorted_list_iter_t SortedLLFind      (sorted_list_iter_t from, sorted_list_iter_t to, const void *data);

/* O(n) */
sorted_list_iter_t SortedLLFindIf    (sorted_list_iter_t from, 
				                      sorted_list_iter_t to,
				                      int (*match_func)(const void *data, const void *param),    
				                      const void *param);
				                   		                   
/* O(n) */
int                SortedLLForEach   (sorted_list_iter_t from, 
				      	              sorted_list_iter_t to,
				                      int (*action_func)(void *data,void *param),
				      	  		      void *param);

/* O(n + m) */				           
void 			   SortedLLMerge	 (sorted_list_t *dest_list, sorted_list_t *src_list);

#endif /* __OL102_SORTED_LINKED_LIST_H__ */



