/* Version 3 - 30.05.2021 17:35 */

#ifndef _OL_102_BST_H_
#define _OL_102_BST_H_

#include <stddef.h>     /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t; 

typedef int (*cmp_func_t)(void *, void *, void *);
typedef int (*act_func_t)(void *, void *);

/* O(1) */
bst_t *BstCreate(cmp_func_t func, void *param);

/* O(n) - n numbert of nodes in tree */
void BstDestroy(bst_t *tree);

/* O(n log n) - n numbert of nodes in tree  ? */
size_t BstSize(const bst_t *tree);

/* O(1) */
int BstIsEmpty(const bst_t *tree);

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstInsert(bst_t *tree, void *data);

/* Avg - O(log n), worst - O(n) */
void BstRemove(bst_iter_t iter);

/* O(1) */
bst_iter_t BstBegin(bst_t *tree);

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstEnd(bst_t *tree);

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstPrev(bst_iter_t iter);

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstNext(bst_iter_t iter);

/* O(1) */
int BstIterIsEqual(const bst_iter_t iter1, const bst_iter_t iter2);

/* O(1) */
void *BstGetData(bst_iter_t iter);

/* Avg - O(log n), worst - O(n) */
bst_iter_t BstFind(bst_t *tree, void *data);

/* O(n log n) */
int BstForEach(bst_iter_t from, bst_iter_t to, act_func_t func, void *param);

#endif /* _OL_102_BST_H_ */

