#ifndef __SLL_EX_H__ 
#define __SLL_EX_H__

typedef struct node 
{
	void *data;
	struct node *next;
}node_t;

node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1, node_t *head_2);

#endif /* __SLL_EX_H__ */
