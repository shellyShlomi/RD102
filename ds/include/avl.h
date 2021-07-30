/* Version 2 - 14.06.2021 16:30 */

#ifndef _OL_102_AVL_H_
#define _OL_102_AVL_H_

#include <stddef.h>     /* size_t */

typedef struct avl avl_t;

typedef int (*cmp_func_t)(void *data1, void *data2);
typedef int (*act_func_t)(void *tree_data, void *user_param);

typedef enum order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
}order_t;

/* O(1) */
avl_t *AVLCreate(cmp_func_t func);

/* O(n) - n numbert of nodes in tree */
void AVLDestroy(avl_t *tree);

/* O(n) - n numbert of nodes in tree */
size_t AVLSize(const avl_t *tree);

/* O(1) */
int AVLIsEmpty(const avl_t *tree);

/* O(log n) */
size_t AVLHeight(const avl_t *tree);

/* O(log n) */
int AVLInsert(avl_t *tree, void *data);

/* O(log n) */
void AVLRemove(avl_t *tree, const void *data);

/* O(log n) */
void *AVLFind(const avl_t *tree, const void *data);

/* O(n) */
int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order);

#endif /* _OL_102_AVL_H_ */


