/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:15.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By:  ;	            								*
 *  Description: slef balancing tree with based on the height   * 
 *             with a limit of abs 2 diff beetwin child nodes   */

#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <string.h> /* memmove */
#include <assert.h>

#include "avl.h"

#define MAX(hight_l, hight_r) ((hight_l) > (hight_r) ? (hight_l) : (hight_r))
#define HAS_RIGHT_CHILD(node) ((node)->children[RIGHT])
#define HAS_LEFT_CHILD(node) ((node)->children[LEFT])

typedef enum childrens
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
} childrens_t;

typedef struct avl_node avl_node_t;
typedef int (*for_each_t)(avl_node_t *node, act_func_t func, void *param);

struct avl_node
{
    void *data;
    avl_node_t *children[NUM_OF_CHILDREN];
    size_t height;
};

struct avl
{
    cmp_func_t func;
    avl_node_t *root;
};

/*------------- helper funcs ------------*/
static int Count(void *unuesed, void *param);

/* static int AVLPostOrderForPrintHeight(avl_node_t *node, act_func_t func, void *param);*/

static void SetNode(avl_node_t *node, avl_node_t *left_child,
                    avl_node_t *right_child, size_t higth, void *data);

/*------------- AVLForEach order funcs ------------*/
static int AVLPreOrder(avl_node_t *node, act_func_t func, void *param);
static int AVLInOrder(avl_node_t *node, act_func_t func, void *param);
static int AVLPostOrder(avl_node_t *node, act_func_t func, void *param);

/*------------- helper func of API wapres ------------*/

static avl_node_t *AVLRecRemove(avl_node_t *node, void *data, cmp_func_t func);

static avl_node_t *HandlerRemoveMatch(avl_node_t *node, cmp_func_t func);

static avl_node_t *GetMinNode(avl_node_t *node);

static int AVLBalancedDiff(avl_node_t *node);

static avl_node_t *AVLRecInsert(avl_node_t *node, avl_node_t *node_malloc,
                                cmp_func_t func);
static avl_node_t *AVLRecFind(avl_node_t *node, void *data, cmp_func_t func);

static void UpDateHeight(avl_node_t *node);

static void BalanceTree(avl_node_t *node);

static void AVLRecDestroy(avl_node_t *node);

/*------------- helper lut for ForEach ------------*/

for_each_t order_for_for_each[] = {AVLPreOrder,
                                   AVLInOrder,
                                   AVLPostOrder/*,
                                   AVLPostOrderForPrintHeight*/};

/*------------------------------ implementetion --------------------------------*/

avl_t *AVLCreate(cmp_func_t func)
{
    avl_t *tree = (avl_t *)malloc(sizeof(avl_t));

    if (!tree)
    {
        return (NULL);
    }

    tree->func = func;
    tree->root = NULL;

    return (tree);
}

void AVLDestroy(avl_t *tree)
{
    assert(tree);
    assert(tree->func);

    if (!tree->root)
    {
        tree->func = NULL;

        free(tree);
        tree = NULL;

        return;
    }

    AVLRecDestroy(tree->root);
    tree->func = NULL;
    tree->root = NULL;

    free(tree);
    tree = NULL;

    return;
}

size_t AVLSize(const avl_t *tree)
{
    size_t counter = 0;

    assert(tree);

    AVLForEach(((avl_t *)tree), Count, (void *)&counter, PRE_ORDER);

    return (counter);
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (!(((avl_t *)tree)->root));
}

/*O(1) */
size_t AVLHeight(const avl_t *tree)
{
    if (AVLIsEmpty(tree))
    {
        return (0);
    }
    return (((avl_t *)tree)->root->height);
}

/* O(log n) */
int AVLInsert(avl_t *tree, void *data)
{
    int balanced_diff = 0;
    avl_node_t *node_malloc = NULL;

    assert(tree);
    assert(tree->func);

    node_malloc = (avl_node_t *)malloc(sizeof(avl_node_t));

    if (!node_malloc)
    {
        return (1);
    }

    SetNode(node_malloc, NULL, NULL, 0, data);

    if (AVLIsEmpty(tree))
    {
        tree->root = node_malloc;
        return (0);
    }

    AVLRecInsert(tree->root, node_malloc, tree->func);

    balanced_diff = AVLBalancedDiff(tree->root);

    if (balanced_diff > 1 || balanced_diff < -1)
    {
        BalanceTree(tree->root);
    }

    return (0);
}

/* O(log n) */
void AVLRemove(avl_t *tree, const void *data)
{
    assert(tree);
    assert(tree->func);

    if (AVLIsEmpty(tree))
    {
        return;
    }
    tree->root = AVLRecRemove(tree->root, (void *)data, tree->func);

    return;
}

/* O(log n) */
void *AVLFind(const avl_t *tree, const void *data)
{
    avl_node_t *node = NULL;

    assert(tree);
    assert(tree->func);

    node = ((avl_t *)tree)->root;

    if (!(node = AVLRecFind(node, (void *)data, ((avl_t *)tree)->func)))
    {
        return (node);
    }

    return (node->data);
}

int AVLForEach(avl_t *tree, act_func_t func, void *param, order_t order)
{
    avl_node_t *node = NULL;

    assert(tree);
    assert(func);

    if (AVLIsEmpty(tree))
    {
        return (0);
    }

    node = tree->root;

    return (order_for_for_each[order](node, func, param));
}
/*------------------------------AVLForEach_orders_function---------------------------------*/

static int AVLPreOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    assert(func);

    if (!node)
    {
        return (status);
    }

    if ((status = func(node->data, param)))
    {
        return (status);
    }

    if ((status = AVLPreOrder(node->children[LEFT], func, param)))
    {
        return (status);
    }

    return (AVLPreOrder(node->children[RIGHT], func, param));
}

static int AVLInOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    assert(func);

    if (!node)
    {
        return (status);
    }

    if ((status = AVLInOrder(node->children[LEFT], func, param)))
    {
        return (status);
    }

    if ((status = func(node->data, param)))
    {
        return (status);
    }

    return (AVLInOrder(node->children[RIGHT], func, param));
}

static int AVLPostOrder(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    assert(func);

    if (!node)
    {
        return (status);
    }

    if ((status = AVLPostOrder(node->children[LEFT], func, param)))
    {
        return (status);
    }
    if ((status = AVLPostOrder(node->children[RIGHT], func, param)))
    {
        return (status);
    }

    return (func(node->data, param));
}

/*-----------------------------helper_function--------------------------------*/

/* generic set node */
static void SetNode(avl_node_t *node, avl_node_t *left_child,
                    avl_node_t *right_child, size_t higth, void *data)
{
    assert(node);

    node->data = data;
    node->children[LEFT] = left_child;
    node->children[RIGHT] = right_child;
    node->height = higth;

    return;
}

/* distroy helper */
static void AVLRecDestroy(avl_node_t *node)
{
    if (!node)
    {
        return;
    }

    AVLRecDestroy(node->children[LEFT]);
    AVLRecDestroy(node->children[RIGHT]);

    SetNode(node, NULL, NULL, 0, NULL);

    free(node);
    node = NULL;

    return;
}

/* helper for size */
static int Count(void *unuesed, void *param)
{
    (void)unuesed;
    assert(param);

    *(size_t *)param = *(size_t *)param + 1;

    return (0);
}

/* insert helper */
static avl_node_t *AVLRecInsert(avl_node_t *node, avl_node_t *node_malloc,
                                cmp_func_t func)
{
    assert(func);
    assert(node_malloc);

    if (!node)
    {
        return (node_malloc);
    }

    if (func(node->data, node_malloc->data) > 0)
    {
        node->children[LEFT] =
            AVLRecInsert(node->children[LEFT], node_malloc, func);
    }
    else
    {
        node->children[RIGHT] =
            AVLRecInsert(node->children[RIGHT], node_malloc, func);
    }

    UpDateHeight(node);

    return (node);
}

/* update the height for a specific node */
static void UpDateHeight(avl_node_t *node)
{

    if (!HAS_RIGHT_CHILD(node) && !HAS_LEFT_CHILD(node))
    {
        node->height = 0;
    }
    else if (HAS_RIGHT_CHILD(node))
    {
        node->height = node->children[RIGHT]->height + 1;
    }
    else
    {
        node->height = node->children[LEFT]->height + 1;
    }

    if (HAS_RIGHT_CHILD(node) && HAS_LEFT_CHILD(node))
    {
        node->height = 1 +
                MAX(node->children[RIGHT]->height, node->children[LEFT]->height);
    }

    return;
}

/* remove helper */
static avl_node_t *AVLRecRemove(avl_node_t *node, void *data,
                                cmp_func_t func)
{
    int balanced_diff = 0;
    int cmp_val = 0;

    assert(func);

    if (!node)
    {
        return (NULL);
    }

    cmp_val = func(node->data, data);

    if (cmp_val == 0)
    {
        return (HandlerRemoveMatch(node, func));
    }

    if (cmp_val > 0)
    {
        node->children[LEFT] =
            AVLRecRemove(node->children[LEFT], data, func);
    }
    else
    {
        node->children[RIGHT] =
            AVLRecRemove(node->children[RIGHT], data, func);
    }

    UpDateHeight(node);
    balanced_diff = AVLBalancedDiff(node);

    if (balanced_diff > 1 || balanced_diff < -1)
    {
        BalanceTree(node);
    }

    return (node);
}
/* Handles the case where the node to remove was founed  */
static avl_node_t *HandlerRemoveMatch(avl_node_t *node, cmp_func_t func)
{
    avl_node_t *child_node = NULL;
    avl_node_t *node_min = NULL;

    assert(node);

    if (HAS_RIGHT_CHILD(node))
    {

        node_min = GetMinNode(node->children[RIGHT]);
        node->data = node_min->data;
        node->children[RIGHT] =
            AVLRecRemove(node->children[RIGHT], node->data, func);

        return (node);
    }
    else
    {

        child_node = node->children[LEFT];

        SetNode(node, NULL, NULL, 0, NULL);

        free(node);

        return (child_node);
    }
}

/* gat the min val node of the cur node */
static avl_node_t *GetMinNode(avl_node_t *node)
{
    assert(node);

    if (HAS_LEFT_CHILD(node))
    {
        return (GetMinNode(node->children[LEFT]));
    }

    return (node);
}

/* find helper */
static avl_node_t *AVLRecFind(avl_node_t *node, void *data,
                              cmp_func_t func)
{
    assert(func);

    if (!node)
    {
        return (NULL);
    }

    if (func(node->data, (void *)data) == 0)
    {
        return (node);
    }

    else if (func(node->data, (void *)data) > 0)
    {
        return (AVLRecFind(node->children[LEFT], (void *)data, func));
    }

    return (AVLRecFind(node->children[RIGHT], (void *)data, func));
}

/* to test the height of each node */
/*static int AVLPostOrderForPrintHeight(avl_node_t *node, act_func_t func, void *param)
{
    int status = 0;

    assert(func);

    if (!node)
    {
        return (status);
    }

    if ((AVLPostOrderForPrintHeight(node->children[LEFT], func, param)))
    {
        return (status);
    }

    if ((AVLPostOrderForPrintHeight(node->children[RIGHT], func, param)))
    {
        return (status);
    }

    return (func((void *)node->height, (void *)node->data));
}*/

/* stub */
static void BalanceTree(avl_node_t *node)
{
    (void)node;

    return;
}

/* for pash 2 */
static int AVLBalancedDiff(avl_node_t *node)
{
    size_t left_child_height = 0;
    size_t right_child_height = 0;

    assert(node);

    if (HAS_RIGHT_CHILD(node))
    {
        right_child_height = node->children[RIGHT]->height;
    }
    if (HAS_LEFT_CHILD(node))
    {
        left_child_height = node->children[LEFT]->height;
    }

    return ((right_child_height - left_child_height));
}

/*

static size_t AVLHeightHelp(avl_node_t *node);

static size_t AVLHeightHelp(avl_node_t *node)
{
    size_t left_child_height = 0;
    size_t right_child_height = 0;

    if (!node->children[LEFT] && !node->children[RIGHT])
    {
        return (0);
    }

    if (HAS_RIGHT_CHILD(node))
    {
        right_child_height += AVLHeightHelp(node->children[RIGHT]);
    }
    if (HAS_LEFT_CHILD(node))
    {
        left_child_height += AVLHeightHelp(node->children[LEFT]);
    }

    return (MAX(left_child_height, right_child_height) + 1);
}*/