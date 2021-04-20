#ifndef __OL102_LINKED_LIST_H__
#define __OL102_LINKED_LIST_H__

#include <stddef.h> /*size_t*/


typedef struct s_list s_list_t;
typedef struct s_list_node *s_list_iter_t;

/* complexity time O(1) */
s_list_t *SLLCreate(void);

/* complexity time O(n) */                       
void SLLDestroy(s_list_t *list);                    

/* complexity time O(1) */  
int SLLIsEmpty (const s_list_t *list);

/* complexity time O(n) */              
size_t SLLCount(const s_list_t *list);                              

/* complexity time O(1) */    
s_list_iter_t SLLBegin  (const s_list_t *list);

/* complexity time O(1) */                               
s_list_iter_t SLLEnd    (const s_list_t *list);   

/* complexity time O(1) */                        
s_list_iter_t SLLNext   (const s_list_iter_t iter);    

                   
/* complexity time O(1) */  
int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2); 

/* complexity time O(1) */  
void SLLSetData(s_list_iter_t iter, void *data);  

/* complexity time O(1) */     
void *SLLGetData(const s_list_iter_t iter);         

/* complexity time O(1) */     
s_list_iter_t SLLRemove(s_list_iter_t iter); 

/* on success: O(1); amortize on failure O(n) */
s_list_iter_t SLLInsert(s_list_iter_t where, void *data);   

/* complexity time O(n) */
s_list_iter_t SLLFind(s_list_iter_t from, 
                        s_list_iter_t to,
                        int (*match_func)(const void * data,void *param),    
                        void *param);

/* complexity time O(n) */                        
int SLLForEach(s_list_iter_t from, 
              s_list_iter_t to,
              int (*action_func)(void * data,void *param),void *param);


#endif /* __OL102_LINKED_LIST_H__ */



