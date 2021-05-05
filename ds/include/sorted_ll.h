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
	d_list_iter_t d_iter;
	struct sorted_list *sorted_list;
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
 *														recived from list
 *														
 *												data2 - pointer to data value
 *														from the user
 *
 *							Return Value   	:   The function return a biger 
 *												then 0 if the vaule is larger
 *												then the vlaue in the list, 
 *												return a smaller num then 0 
 *												if the vaule is smaller then
 * 												the vlaue in the list and 0 if 
 *												the data recived from the user 
 *												is equal to vlaue in the list 
 *
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
 * DESCRIPTION		:	The function Destroy the list and free the memory 
 *						the user needs to nullify the pointer on the stack
 * 
 * PARAMETERS    	:   list - pointer to list
 *
 * RETURN VALUE   	:   non 
 * 
 * COMPLEXITY   	:   Time - O(1); Space - O(1) 
 */
void 			 SortedLLDestroy    (sorted_list_t *list);                    




/*SortedLLIsEmpty
 * DESCRIPTION		:	The function return a boolian value indicet the list stat
 * 
 * PARAMETERS    	:   list - pointer to list
 *
 * RETURN VALUE   	:   boolian value : 1 is empty, 0 not empty 
 * 
 * COMPLEXITY   	:   Time - O(1)
 */
int 			 SortedLLIsEmpty     (const sorted_list_t *list);




/*SortedLLSize
 * DESCRIPTION		:	The function return number of element within a list 
 * 
 * PARAMETERS    	:   list - pointer to list
 *
 * RETURN VALUE   	:   size_t - number of element within a list
 * 
 * COMPLEXITY   	:   Time - O(n)
 */
size_t           SortedLLSize	    (const sorted_list_t *list);




/*SortedLLBegin
 * DESCRIPTION		:	The function return the first element within a list 
 *						***if the list is empty return the end - a non valid iter***
 * 
 * PARAMETERS    	:   list - pointer to list
 *
 * RETURN VALUE   	:   sorted_list_iter_t - first element within a list
 * 
 * COMPLEXITY   	:   Time - O(1)
 */
sorted_list_iter_t SortedLLBegin	    (const sorted_list_t *list);




/*SortedLLEnd
 * DESCRIPTION		:	The function return the last element within a list 
 * 
 * PARAMETERS    	:   list - pointer to list
 *
 * RETURN VALUE   	:   sorted_list_iter_t - last element within a list - a non valid iter
 * 
 * COMPLEXITY   	:   Time - O(1)
 */                     
sorted_list_iter_t SortedLLEnd	    (const sorted_list_t *list);   


/*SortedLLNext
 * DESCRIPTION		:	The function return the next element within a list 
 * 
 * PARAMETERS    	:   iter - const iter - ***can't operat on the end iter(a non valid iter)***
 *
 * RETURN VALUE   	:   sorted_list_iter_t - the next element within a list 
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
sorted_list_iter_t SortedLLNext       (const sorted_list_iter_t iter);





/*SortedLLPrev
 * DESCRIPTION		:	The function return the previous element within a list 
 * 
 * PARAMETERS    	:   iter - const iter - ***can't operat on the Begin iter (has no previous)***
 *
 * RETURN VALUE   	:   sorted_list_iter_t - the previous element within a list 
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
sorted_list_iter_t SortedLLPrev	    (const sorted_list_iter_t iter);



/*SortedLLIsSameIter
 * DESCRIPTION		:	The function compare the iters based on ther addreses 
 * 
 * PARAMETERS    	:   iter1 - const iter
 *						iter2 - const iter
 *
 * RETURN VALUE   	:   boolian value : 1 is same iter, 0 not same iter  
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
int 			 SortedLLIsSameIter (const sorted_list_iter_t iter1, const sorted_list_iter_t iter2);






/*SortedLLGetData
 * DESCRIPTION		:	The function returns the data of an iter 
 * 
 * PARAMETERS    	:   iter - sorted_list_iter_t iter
 *						
 * RETURN VALUE   	:   void * - the data from the user
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
void *           SortedLLGetData    (sorted_list_iter_t iter);




/*SortedLLRemove
 * DESCRIPTION		:	The function remove an iter from the list 
 * 
 * PARAMETERS    	:   iter - sorted_list_iter_t iter
 *						***can't operat on the end iter(a non valid iter)***
 *						
 * RETURN VALUE   	:   sorted_list_iter_t - the iter ta the removeal place removed
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
sorted_list_iter_t SortedLLRemove     (sorted_list_iter_t iter);

/* O(n) *//* if the is replection of the same data the func will insert befor the closext next elem which is biger then the data inserted */


/*SortedLLInsert
 * DESCRIPTION		:	The function insert an iter to the list with the data was given
 * 						****if there is a replication of the same data the
 * 							function will insert before the next bigeer element 
 *							(which is bigeer then the data inserted)   ****
 *
 * PARAMETERS    	:   data - to stor in the iter
 *						list - pointer to the destenation list
 *						
 * RETURN VALUE   	:   sorted_list_iter_t - the iter that was inserted
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
sorted_list_iter_t SortedLLInsert     (sorted_list_t *list, void *data);





/*SortedLLPopFront
 * DESCRIPTION		:	The function remove an iter from the front of the list 
 *
 * PARAMETERS    	:    iter - sorted_list_iter_t iter
 *						***can't operat on a empty list***
 *						
 * RETURN VALUE   	:   void * - the data of iter that was removeed
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
void *		     SortedLLPopFront   (sorted_list_t *list);                              






/*SortedLLPopBack
 * DESCRIPTION		:	The function remove an iter from the back of the list 
 *
 * PARAMETERS    	:    iter - sorted_list_iter_t iter
 *						***can't operat on a empty list***
 *						
 * RETURN VALUE   	:   void * - the data of iter that was removeed
 * 
 * COMPLEXITY   	:   Time - O(1)
 */ 
void *           SortedLLPopBack    (sorted_list_t *list); 




/*SortedLLFind
 * DESCRIPTION		:	the function find the first iter in the list with
 *						data value wich is equal to the data recived 
 *
 * PARAMETERS    	:   from - 	the iter in the list where the serch start from
 *
 *						to - 	the iter in the list where the serch end with the iter 
 *								befor it
 *						***	the from and the to HAVE to be from the same list ***
 *						
 *						list -	the list where the from and the to are part of
 *								gives the cmp_func for the comparison 
 *						
 *						***	the list HAVE to the same list of from and to - 
 *							for the same cmp_func whit the smae logic for order ***
 *
 * RETURN VALUE   	:   sorted_list_iter_t - the iter with a data value wich
 *						is equal to the data recived
 * 
 * COMPLEXITY   	:   Time - O(n)
 */
 
sorted_list_iter_t SortedLLFind     (sorted_list_iter_t from, 
									sorted_list_iter_t to, 
									const void *data, sorted_list_t *list);





/*SortedLLFindIf
 * DESCRIPTION		:	the function find the first iter in the list with
 *						data value wich is looked for with the  match_func 
 *
 * PARAMETERS    	:   int (*match_func)(const void *data, const void *param)
 *						
 *							Description		:	a function wich compar to data 
 *												values of the same type
 *												
 *							Parameters		:	const data -	the list iter data  
 *																compard with parta   
 *
 *												const param -	the data looked
 *			 													for within the list
 *
 *							Return Value   	:    boolian value : 1 same data, 0 not same data
 *
 *							Complexity		: 	Time - O(n) 
 *
 *						from - 	the iter in the list where the serch start from
 *
 *						to - 	the iter in the list where the serch end with the iter 
 *								befor it
 *						***	the from and the to HAVE to be from the same list ***
 *						
 *						param -	the data looked for within the list
 *			 													
 *						
 * RETURN VALUE   	:   sorted_list_iter_t - the first iter in the list with
 *						data value wich is equal than the data recived 
 * 
 * COMPLEXITY   	:   Time - O(n)
 */
sorted_list_iter_t SortedLLFindIf    (sorted_list_iter_t from, 
				                      sorted_list_iter_t to,
				                      int (*match_func)(const void *data, const void *param),    
				                      const void *param);




/*SortedLLForEach
 * DESCRIPTION		:	the function makes an oparetion on each iter with in the list 
 *
 * PARAMETERS    	:   int (*action_func)(void *data, void *param)
 *						
 *							Description		:	the function with the oparetion 
 *												wanted to be dane on the list
 *												
 *							Parameters		:	data - data from the list to manipulat on 
 *														
 *												param - an extra param to to manipulation with
 *
 *							Return Value   	:   the func returns a ststus of the oparetion
 *
 *							Complexity		: 	Time - O(1) 
 *
 *						
 * RETURN VALUE   	:   the func returns a ststus of the oparetion func to the user
 * 
 * COMPLEXITY   	:   Time - O(n)
 */
int                SortedLLForEach   (sorted_list_iter_t from, 
				      	              sorted_list_iter_t to,
				                      int (*action_func)(void *data,void *param),
				      	  		      void *param);

/*SortedLLMerge
 * DESCRIPTION		:	the function takes two lists and merge them together,
 *						increase the size of dest and src become an empty list
 *
 * PARAMETERS    	:   dest	- 	the destination list for the merge
 *
 *						src		- 	the source list for the merge will be 
 *									left empty after the merge
 *						
 * RETURN VALUE   	:   non
 * 
 * COMPLEXITY   	:   Time - O(n + m)
 */				           
void 			 SortedLLMerge	    (sorted_list_t *dest_list, sorted_list_t *src_list);

#endif /* __OL102_SORTED_LINKED_LIST_H__ */



