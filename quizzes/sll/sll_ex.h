
#ifndef __OL102_LINKED_LIST_H__
#define __OL102_LINKED_LIST_H__

typedef struct node node_t;

struct node
{
	void *data;
	node_t *next;
	
};

node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif /* __OL102_LINKED_LIST_H__ */


