#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

typedef struct d_list_node node_t;

struct d_list_node
{
	void *data;
	node_t *next;
	node_t *prev;
	
};

typedef struct d_list
{
	node_t head_dummy;
	node_t tail_dummy;
}d_list_t;

d_list_t *DLLCreate(void);
void DLLDestroy(d_list_t *list);
node_t *DLLBegin(const d_list_t *list);
node_t *DLLEnd(const d_list_t *list);
int DLLIsEmpty(const d_list_t *list);
int DLLIsSameNode(const node_t *node1, const node_t *node2);
void DLLRemove(node_t *where);
node_t *DLLInsertBefore(node_t *where, void *data);
void *DLLGetData(node_t *node);
node_t *DLLNext(const node_t *node);
node_t *DLLPrev(const node_t *node); 

void TestDLLRemoveAndInsert();

int main()
{
	TestDLLRemoveAndInsert();
	
	return (0);
}

void TestDLLRemoveAndInsert()
{
	int arr[] = {1, 2, 3, 4, 5, 6};
	size_t size = sizeof(arr) / sizeof(arr[0]);
	size_t i = 0; 
	
	d_list_t *list = NULL;
	node_t *node = NULL;
	
	list = DLLCreate();
	
	if (NULL == list)
	{
		printf("DLLCreate failed at line %d\n", __LINE__);
	}
	
	for (i = 0; i < size; ++i)
	{
		DLLInsertBefore(DLLBegin(list), (void *)(arr + i));
	} 
	
	node = DLLBegin(list);
	 
	for (i = 0; i < size; ++i)
	{
		if(arr[size - 1 - i] != *(int *)DLLGetData(node))
		{
			printf("SLLGetData test failed in line: %d at index: %ld\n" 
				   , __LINE__, i);
		}
		
		node = DLLNext(node);  		
	}
	
	for (i = 0; i < size - 1; ++i)
	{
		DLLRemove(DLLBegin(list));  		
	}
	
	node = DLLBegin(list);
	
	if (arr[0] != *(int *)DLLGetData(node))
	{
		printf("SLLGetData test failed in line: %d at index: %ld\n" 
			   , __LINE__, i);
	}
	
	DLLRemove(DLLBegin(list)); 
	
	for (i = 0; i < size; ++i)
	{
		DLLInsertBefore(DLLBegin(list), (void *)(arr + i));
	} 
	
	node = DLLBegin(list);
	 
	for (i = 0; i < size; ++i)
	{
		if(arr[size - 1 - i] != *(int *)DLLGetData(node))
		{
			printf("SLLGetData test failed in line: %d at index: %ld\n" 
				   , __LINE__, i);
		}
		
		node = DLLNext(node);  		
	}
	
	for (i = 0; i < size - 1; ++i)
	{
		DLLRemove(DLLPrev(DLLEnd(list)));  		
	}
	
	node = DLLBegin(list);
	
	if (arr[size - 1] != *(int *)DLLGetData(node))
	{
		printf("SLLGetData test failed in line: %d at index: %ld\n" 
			   , __LINE__, i);
	}
	
	DLLDestroy(list);

	return;
}

d_list_t *DLLCreate(void)
{
	d_list_t *list = (d_list_t *)malloc(sizeof(d_list_t));
		
	if (NULL == list)
	{
		return NULL;
	}
	
	list->tail_dummy.next = NULL;
	list->tail_dummy.data = NULL;
	list->tail_dummy.prev = &list->head_dummy;
	
	list->head_dummy.prev = NULL;
	list->head_dummy.data = NULL;
	list->head_dummy.next = &list->tail_dummy;
		
	return (list); 
}

void DLLDestroy(d_list_t *list)
{
	assert(NULL != list);
		
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));			
	}
	
	DLLBegin(list)->next = NULL;
	DLLEnd(list)->prev = NULL;
	
	free(list);
	
	return;
}

node_t *DLLBegin(const d_list_t *list)
{
	assert(NULL != list);

	return (list->head_dummy.next);
}           

node_t *DLLEnd(const d_list_t *list)
{
	assert(NULL != list);
		
	return ((node_t *)&list->tail_dummy);
} 

int DLLIsEmpty(const d_list_t *list)
{
	assert(NULL != list);
	
	return (DLLIsSameNode(DLLBegin(list), DLLEnd(list)));
}

int DLLIsSameNode(const node_t *node1, const node_t *node2)
{
	assert(NULL != node1);
	assert(NULL != node2);
	
	return (node1 == node2);
}     

void DLLRemove(node_t *where)
{
	assert(where);
	
	where->next->prev = where->prev;
	where->prev->next = where->next;
	
	free(where);
	
	return;
} 	

node_t *DLLInsertBefore(node_t *where, void *data) 
{
	node_t *new_node = NULL;
	
	assert(where);
	
	new_node = (node_t *)malloc(sizeof(node_t));
	
	if (NULL == new_node)
	{
		return (NULL);
	} 
	
	new_node->data = data;
	new_node->next = where;
	new_node->prev = where->prev;
	where->prev->next = new_node;
	where->prev = new_node;
	
	return (new_node);
}

void *DLLGetData(node_t *node)
{
	assert(NULL != node);
	 
	return (node->data);
}

node_t *DLLNext(const node_t *node)
{
	assert(NULL != node);
	
	return (node->next);
}

node_t *DLLPrev(const node_t *node)    
{
	assert(NULL != node);
	
	return (node->prev);
}


