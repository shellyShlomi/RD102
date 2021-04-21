
/*  Developer: Shelly Shlomi;									*
 *  Status:Approved;											*
 *  Date Of Creation:19.04.21;									*
 *  Date Of Approval:20.04.21;									*
 *  Approved By: final approved by NIR;							*
 *  Description: singly link list data structure;				*/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "sll_ex.h"

#define SUCCESS_BOL 1

static void Offset(node_t **head,size_t head_offset);
size_t CountElemInList(node_t *head);





/*flip , go , temp <<
->	go	temp			
->			temp->next */
/* Time complexity:O(n) Space:O(1)	*/
/* approved by nir 					*/
node_t *Flip(node_t *head)
{
	node_t *flip = head;
	node_t *go = NULL;
	node_t *temp = NULL;

	assert(NULL != head);
	
	go = head->next;
	head->next = NULL;

	if (NULL == go)
	{
		return (head);
	}
	
	while(NULL != go->next)
	{
		temp = go->next;
		go->next = flip;
		flip = go;
		go = temp; 
	}
	
	go->next = flip;
	
	return (go);

}

/* approved by nir					*/
/* Time complexity:O(n) Space:O(1)	*/
int HasLoop(const node_t *head)
{

	const node_t *jump1 = head;
	const node_t *jump2 = jump1;

	assert(NULL != head);

	while(NULL != jump2->next && NULL != jump2->next->next)
	{
		jump1 = jump1->next;
		jump2 = jump2->next->next;
		
		if (jump2 == jump1)
		{
			return (SUCCESS_BOL);			
		}
	}
	
	return (!SUCCESS_BOL);
}
/* approved by anna					*/
/* Time complexity:O(n) Space:O(1)	*/
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	size_t counter_1 = 0;
	size_t counter_2 = 0;

	assert(NULL != head_1);
	assert(NULL != head_2);

	counter_1 = CountElemInList(head_1);
	counter_2 = CountElemInList(head_2);

	if (counter_1 < counter_2)
	{
		Offset(&head_2, counter_2 - counter_1);
	}
	else
	{
		Offset(&head_1, counter_1 - counter_2);
	}
	
	
	while(NULL != head_1)
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		head_1 = head_1->next;
		head_2 = head_2->next;		
	}
	
	return NULL;
}

size_t CountElemInList(node_t *head)
{
	size_t counter = 1;
	
	while(NULL != head->next)
	{
		head = head->next;
		++counter;
	}
	return (counter);
}

static void Offset(node_t **head, size_t head_offset)
{
	
	while(0 < head_offset && NULL != (*head)->next)
	{
		*head = (*head)->next;
		--head_offset;
	}
	return ;
}







