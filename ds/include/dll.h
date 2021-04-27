#ifndef __OL102_D_LINKED_LIST_H__
#define __OL102_D_LINKED_LIST_H__

#include <stddef.h> /*size_t*/

/* version 1.0 26.04.21 APPROVED*/

typedef struct d_list d_list_t;
typedef struct d_list_node *d_list_iter_t;


/*

struct d_list_node
{
	void *data;
	d_list_node *next;
	d_list_node *prev;
	
};

struct d_list
{
	d_list_node head_dummy;
	d_list_node tail_dummy;
};


*/



/* complexity time O(1) */
d_list_t *DLLCreate(void);

/* complexity time O(n) */                       
void DLLDestroy(d_list_t *list);                    

/* complexity time O(1) */  
int DLLIsEmpty (const d_list_t *list);

/* complexity time O(n) */              
size_t DLLSize(const d_list_t *list);                              

/* complexity time O(1); on failure return end_dummy*/    
d_list_iter_t DLLBegin(const d_list_t *list);

/* complexity time O(1) */                               
d_list_iter_t DLLEnd(const d_list_t *list);   

/* complexity time O(1) */                        
d_list_iter_t DLLNext(const d_list_iter_t iter); 
   
/* complexity time O(1) */     
d_list_iter_t DLLPrev(const d_list_iter_t iter);    
                
/* complexity time O(1) */ 
int DLLIsSameIter(const d_list_iter_t iter1, const d_list_iter_t iter2); 

/* complexity time O(1) */     
void *DLLGetData(d_list_iter_t iter);  

       
/* complexity time O(1) */     
d_list_iter_t DLLRemove(d_list_iter_t iter); 

/* on success: O(1); */
d_list_iter_t DLLInsert(d_list_iter_t where, void *data);  

/* on success: O(1); */
d_list_iter_t DLLPushFront(d_list_t *list, void *data);                              
 
/* on success: O(1) */
d_list_iter_t DLLPushBack(d_list_t *list, void *data); 

/* on success: O(1); */
void *DLLPopFront(d_list_t *list);                              

/* on success: O(1) */
void *DLLPopBack(d_list_t *list); 

/* complexity time O(n) */
d_list_iter_t DLLFind(d_list_iter_t from, 
                      d_list_iter_t to,
                      int (*match_func)(const void *data, const void *param),    
                      const void *param);

/* complexity time O(n) */                        
int DLLForEach	(d_list_iter_t from, 
              	 d_list_iter_t to,
              	 int (*action_func)(void *data,void *param),
              	 void *param);


/* return 0 on success and non zero value on failure */
/* space O(n) time O(n) */
int DLLMultiFind(d_list_iter_t from, 
                 d_list_iter_t to,
                 int (*match_func)(const void *data,const void *param),    
                 const void *param,
                 d_list_t *dest_list);
                 
                 
/*return to -  the lest elem that was insert to the new list*/
d_list_iter_t DLLSplice(d_list_iter_t where, 
              			d_list_iter_t from,
         	  			d_list_iter_t to);
         	  

#endif /* __OL102_D_LINKED_LIST_H__ */



