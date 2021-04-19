/*19.4.20 11:20 version_5*/

#ifndef __OL102_LINKED_LIST_H__
#define __OL102_LINKED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct s_list s_list_t;
typedef struct s_list_node *s_list_iter_t;


s_list_t *SLLCreate(void);  /*O(1)*/
void SLLDestroy(s_list_t *list); /*O(n)*/

int SLLIsEmpty (const s_list_t *list); /*O(1)*/
size_t SLLCount(const s_list_t *list); /*O(n)*/

s_list_iter_t SLLBegin(const s_list_t *list);/*O(1)*/
s_list_iter_t SLLEnd(const s_list_t *list);/*O(1)*/
s_list_iter_t SLLNext(const s_list_iter_t iter);/*O(1)*/

int SLLIsSameIter(const s_list_iter_t iter1, const s_list_iter_t iter2); /*O(1)*/

void SLLSetData(s_list_iter_t iter, void *data); /*O(1)*/
void *SLLGetData(const s_list_iter_t iter); /*O(1)*/


int SLLInsert(s_list_iter_t where, void *data); /*O(1)*/

s_list_iter_t SLLFind(s_list_iter_t from, /*O(n)*/
			s_list_iter_t to,
		    	int (*match_func)(const void * data,void *param),void *param);
int SLLForEach(s_list_iter_t from, /*O(n)*/
		s_list_iter_t to,
		int (*action_func)(void * data,void *param),void *param);


#endif /* __OL102_LINKED_LIST_H__ */

