#ifndef __OL102_SORTED_LINKED_LIST_H__
#define __OL102_SORTED_LINKED_LIST_H__

#include <stddef.h> /*size_t*/
#include "dll.h" /* sorted_list_iter_t */

typedef struct sorted_list sorted_list_t;

#ifdef NDEBUG

typedef d_list_iter_t sorted_list_iter_t;

#else
typedef struct sorted_list_iter sorted_list_iter_t;

struct sorted_list_iter
{
	d_list_iter_t node;
	struct sorted_list *list;
};

#endif


/*SortedLLCreate
 * DESCRIPTION		:	The function return a pointer to list 
 *						(Sorted DLL #include "dll.h")
 * 
 * PARAMETERS    	:   int (*cmp_func)(const void *data1, const void *data2)
 *						
 *							Description		:	the func is compering data 
 *				 								from the user with the data 
 *												saved in each iter, ues for 
 *												locating the rigth place to 
 *												inserting a new element to 
 *								 				the list it is the user 
 *											 	responsebility to do The rigth
 *												adjusmet for the system to 
 *												proccse the data corectly
 *												
 *							Parameters		:	data1 - pointer to data value
 *														recived from the user
 *														
 *												data2 - pointer to data value
 *														from the user
 *
 *							Return Value   	:   IThe function return a boolean 
 *												int, 1 - success, 0 - failure
 *							Complexity		: 	Time - O(n) 
 *
 *
 * RETURN VALUE   	:   return a pointer to list 
 *                  	If malloc failed - a NULL value is returned 
 * 
 * COMPLEXITY   	:   Time - O(1); Space - O(1) 
 */
sorted_list_t *    SortedLLCreate		(int (*cmp_func)(const void *data1, const void *data2));





/*SortedLLDestroy
 * DESCRIPTION		:	The function return a pointer to list 
 *						(Sorted DLL #include "dll.h")
 * 
 * PARAMETERS    	:   int (*cmp_func)(const void *data1, const void *data2)
 *						
 *							Description		:	the func is compering data 
 *				 								from the user with the data 
 *												saved in each iter, ues for 
 *												locating the rigth place to 
 *												inserting a new element to 
 *								 				the list it is the user 
 *											 	responsebility to do The rigth
 *												adjusmet for the system to 
 *												proccse the data corectly
 *												
 *							Parameters		:	data1 - pointer to data value
 *														recived from the user
 *														
 *												data2 - pointer to data value
 *														from the user
 *
 *							Return Value   	:   IThe function return a boolean 
 *												int, 1 - success, 0 - failure
 *							Complexity		: 	Time - O(n) 
 *
 *
 * RETURN VALUE   	:   return a pointer to list 
 *                  	If malloc failed - a NULL value is returned 
 * 
 * COMPLEXITY   	:   Time - O(1); Space - O(1) 
 */
/* O(n) */
void 			 SortedLLDestroy    (sorted_list_t *list);                    

/* O(1) */
int 			 SotedLLIsEmpty     (const sorted_list_t *list);

/* O(n) */        
size_t           SortedLLSize	    (const sorted_list_t *list);

/* O(1) */
sorted_list_iter_t SortedLLBegin	    (const sorted_list_t *list);

/* O(1) */                        
sorted_list_iter_t SortedLLEnd	    (const sorted_list_t *list);   

/* O(1) */               
sorted_list_iter_t SortedLLNext       (const sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLPrev	    (const sorted_list_iter_t iter);

/* O(1) */
int 			 SortedLLIsSameIter (const sorted_list_iter_t iter1, const sorted_list_iter_t iter2);

/* O(1) */
void *           SortedLLGetData    (sorted_list_iter_t iter);

/* O(1) */
sorted_list_iter_t SortedLLRemove     (sorted_list_iter_t iter);

/* O(n) *//* if the is replection of the same data the func will insert befor the closext next elem which is biger then the data inserted */
sorted_list_iter_t SortedLLInsert     (sorted_list_t *list, void *data);

/* O(1) */				                   		                   
void *		     SortedLLPopFront   (sorted_list_t *list);                              

/* O(1) */
void *           SortedLLPopBack    (sorted_list_t *list); 

/* O(n) */
sorted_list_iter_t SortedLLFind       (sorted_list_iter_t from, sorted_list_iter_t to, const void *data);

/* O(n) */
sorted_list_iter_t SortedLLFindIf     (sorted_list_iter_t from, 
				                     sorted_list_iter_t to,
				                     int (*match_func)(const void *data, const void *param),    
				                     const void *param);
				                   		                   
/* O(n) */
int              SortedLLForEach    (sorted_list_iter_t from, 
				      	             sorted_list_iter_t to,
				                     int (*action_func)(void *data,void *param),
				      	  		     void *param);

/* O(n + m) */				           
void 			 SortedLLMerge	    (sorted_list_t *dest_list, sorted_list_t *src_list);

#endif /* __OL102_SORTED_LINKED_LIST_H__ */



/* template - small
 * DESCRIPTION    :    The function return the first node of the list
 * 
 * PARAMETERS    :    list - pointer to list
 * 
 * RETURN VALUE    :    Iterator to first node
 *                    If the list is empty the end of the list will be returned 
 * 
 * COMPLEXITY    :    Time - O(1) 
 */

