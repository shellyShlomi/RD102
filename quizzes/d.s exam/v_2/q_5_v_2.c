#include <stdio.h> /* printf */
#include <stdlib.h> /* exit status */
#include <assert.h>


typedef struct d_list d_list_t;
typedef struct d_node node_t;

struct d_node
{
	void *data;
	node_t *next;
	node_t *prev;
};

struct d_list
{
	node_t head_dummy;
	node_t tail_dummy;
};


/*---------d.s for the impl func-----------*/
d_list_t *DLLCreate(void);
void DLLDestroy(d_list_t *list);
int DLLIsEmpty(const d_list_t *list);
int DLLIsSameNode(const node_t *node1, const node_t *node2);
node_t *DLLEnd(const d_list_t *list);
node_t *DLLBegin(const d_list_t *list);
node_t *DLLNext(const node_t *node);
node_t *DLLPrev(const node_t *node);
void *DLLGetData(const node_t *node);
/*---------------impl func-----------------*/
int DLLInsert(node_t *node, void *data);
void DLLRemove(node_t *to_remove);


/*---------------test func-----------------*/
static void Test();

/*------------------------------test for impl---------------------------------*/

int main()
{
	
	Test();
	
	return EXIT_SUCCESS;
}



static void Test()
{
	int data = 1;
	
	int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	size_t size = sizeof(arr)/ sizeof(arr[0]);

	int i = 0;

	d_list_t *list = DLLCreate();
	node_t *node = NULL;
	
	if (NULL == list)
	{
		printf("DLLCreate error at line: %d\n", __LINE__);
		list = NULL;
		
		return; 
	}
	
	if (1 != DLLIsEmpty(list))
	{
		printf("DLLCreate error at line: %d\n", __LINE__);
		 
	}
	
	
	node = DLLEnd(list);
	
	if (DLLInsert(node, (void *)&data))
	{
		printf("DLLInsert error at line: %d\n", __LINE__);
	}
	
	if (0 != DLLIsEmpty(list))
	{
		printf("DLLInsert error at line: %d\n", __LINE__);
	}
	
	node = DLLBegin(list);
	DLLRemove(node);
	
	if (1 != DLLIsEmpty(list))
	{
		printf("DLLRemove error at line: %d\n", __LINE__);
		 
	}
	
	node = DLLEnd(list);
	if (DLLInsert(node, (void *)(arr + i)))
	{
		printf("DLLInsert error at line: %d\n", __LINE__);
	}
	
	node = DLLPrev(DLLEnd(list));
	for (i = 1; (size_t)i < size ; ++i)
	{
		if (DLLInsert(node, (void *)(arr + i)))
		{
			printf("DLLInsert error at line: %d\n", __LINE__);
		}
		node = DLLPrev(node);
	}

	node = DLLBegin(list);
	for (i = size - 1; 0 <= i ; --i)
	{
		if (*(arr + i) !=  *(int *)DLLGetData(node))
		{
			printf("DLLInsert error at line: %d\n", __LINE__);
		}
		node = DLLNext(node);
	}

	DLLDestroy(list);
	

	return; 
}



/*------------------------------implementetion--------------------------------*/
int DLLInsert(node_t *where, void *data)
{
	node_t *node = NULL;
	
	assert(where);
	
	node = (node_t *)malloc(sizeof(struct d_node));
	
	if (!node)
	{   
		return (1);
	}
	
	node->data = data;
	node->next = where;
	node->prev = where->prev;
	
	where->prev->next = node;
	where->prev = node;
	
    return (0);

}

void DLLRemove(node_t *node)
{
	assert(NULL != node->next);

	node->prev->next = node->next; 
	node->next->prev = node->prev;
	
	node->data = NULL;
	node->next = NULL;
	node->prev = NULL;

	free(node);

	return;
}
/*---------------------------d.s for the impl func----------------------------*/

d_list_t *DLLCreate(void)
{
	d_list_t *list = (d_list_t *)malloc(sizeof(d_list_t));

	if (NULL == list)
	{    
		return NULL;
	}

	list->head_dummy.data = NULL;	
	list->head_dummy.prev = NULL;
	list->tail_dummy.next = NULL;
	list->tail_dummy.data = NULL;	
	
	list->head_dummy.next = &(list->tail_dummy);
	list->tail_dummy.prev = &(list->head_dummy);

	return (list);

}


void DLLDestroy(d_list_t *list)
{
	assert(NULL != list);

	
	while (!DLLIsEmpty(list))
	{
		DLLRemove(DLLBegin(list));
	}
	
	list->head_dummy.next = NULL;
	list->tail_dummy.prev = NULL;

	free(list);
	
	return;
}

int DLLIsSameNode(const node_t *node1, const node_t *node2)
{
	assert(NULL != node1);
	assert(NULL != node2);
	
	return (node1 == node2);
}

int DLLIsEmpty(const d_list_t *list)
{
	assert(NULL != list);

	return (DLLIsSameNode(DLLBegin(list), DLLEnd(list)));
}

void *DLLGetData(const node_t *node)
{
	assert(NULL != node);
	
	return (node->data);

}

node_t *DLLPrev(const node_t *node)
{
	assert(NULL != node);

	return (node->prev);
}

node_t *DLLNext(const node_t *node)
{
	assert(NULL != node);

	return (node->next);
}


node_t *DLLBegin(const d_list_t *list)
{
	assert(NULL != list);

	return (list->head_dummy.next);
}

node_t *DLLEnd(const d_list_t *list)
{
	assert(NULL != list);

	return (node_t *)&(list->tail_dummy);
}

