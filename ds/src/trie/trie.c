/*  Developer: Shelly Shlomi;									*
 *  Status:in development;                                      *
 *  Date Of Creation:27.06.21;									*
 *  Date Of Approval:--.06.21;									*
 *  Approved By:  ;	            								*
 *  Description: trie DS                                        */

#include <stdlib.h> /* malloc */
#include <stddef.h> /* size_t */
#include <string.h> /* memmove */
#include <math.h>   /* pow */
#include <assert.h>

#include "dhcp.h"
#include "trie.h"

#define BITS_IN_4BYTES (32)
#define BINARIY_BASE (2)

#define MAX(hight_l, hight_r) ((hight_l) > (hight_r) ? (hight_l) : (hight_r))

#define NEXT_NODE_BIT(bits, ip) ((ip >> ((bits)-1) & 0x1))
#define SIBLING_BIT(x, i) (((~i) >> ((x)-1)) & 0x1)

#define HAS_RIGHT_CHILD(node) ((node)->node_family[RIGHT])
#define HAS_LEFT_CHILD(node) ((node)->node_family[LEFT])

#define IS_NEXT_NODE_FULL(node, ip, bit) ((node)->node_family[(bit)]->is_full)
#define IS_NEXT_NODE_SIBLING_FULL(node, ip, bit) ((node)->node_family[SIBLING_BIT((bit), (ip))]->is_full)

#define NEXT_NODE(node, bit) ((node)->node_family[(bit)])

#define IS_RIGHT_CHILD_FULL(node) ((node)->node_family[RIGHT]->is_full)
#define IS_LEFT_CHILD_FULL(node) ((node)->node_family[LEFT]->is_full)

#define PARENT_NODE(node) ((node)->node_family[PARENT])

struct trie_node
{
    trie_node_t *node_family[FAMILY_SIZE];
    long is_full;
};

struct trie
{
    trie_node_t *root;
    size_t num_of_bits;
};

/*------------- helper funcs ------------*/
static void SetNode(trie_node_t *node, trie_node_t *left_child,
                    trie_node_t *right_child, trie_node_t *parent, long is_full);

/*------------- helper func of API wapres ------------*/

static void TrieRecDestroy(trie_node_t *node);

static size_t RecTrieSize(trie_node_t *node, size_t hight);

/*------------- Insert ------------*/

static dhcp_status_t InerInsert(trie_t *tree, unsigned long *wanted_ip, unsigned long *returned_ip);
static trie_node_t *GetIpNode(trie_node_t *node, unsigned long wanted_ip, unsigned long *bits, family_t *ip_child_side);
static dhcp_status_t RecInsert(trie_node_t *node, unsigned long bits, unsigned long *wanted_ip, unsigned long *returned_ip);

static dhcp_status_t CreatBranch(trie_node_t *node,
                                 unsigned long *wanted_ip,
                                 unsigned long bits);

static void DestroyBranch(trie_node_t *node, unsigned long wanted_ip, unsigned long bits);
static void UpDateIsFull(trie_node_t *node);
/*------------------------------ implementetion --------------------------------*/

trie_t *TrieCreate(size_t num_of_bits)
{
    trie_t *tree = (trie_t *)malloc(sizeof(trie_t));

    if (!tree)
    {
        return (NULL);
    }

    tree->root = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (!tree->root)
    {
        free(tree);
        return (NULL);
    }
    tree->root->is_full = 0;
    tree->num_of_bits = num_of_bits;

    SetNode(tree->root, NULL, NULL, NULL, 0);

    return (tree);
}

void TrieDestroy(trie_t *tree)
{
    assert(tree);

    if (!tree->root)
    {
        tree->num_of_bits = -1;

        free(tree);
        tree = NULL;

        return;
    }

    TrieRecDestroy(tree->root);
    tree->num_of_bits = -1;
    tree->root = NULL;

    free(tree);
    tree = NULL;

    return;
}

dhcp_status_t TrieInsert(trie_t *tree, unsigned long wanted_ip, unsigned long *returned_ip)
{

    unsigned long ip = wanted_ip;

    assert(tree);
    assert(returned_ip);

    *returned_ip = wanted_ip;

    if (tree->root->is_full)
    {
        return (TRIE_IS_FULL);
    }

    return (InerInsert(tree, &ip, returned_ip));
}

size_t TrieSize(trie_t *tree)
{
    return (RecTrieSize(tree->root, tree->num_of_bits));
}

void TrieRemove(trie_t *tree, unsigned long ip)
{
    assert(tree);
    DestroyBranch(tree->root, ip, tree->num_of_bits);
    return;
}

/*-----------------------------helper_function--------------------------------*/

/* generic set node */
static void SetNode(trie_node_t *node, trie_node_t *left_child,
                    trie_node_t *right_child, trie_node_t *parent, long is_full)
{
    assert(node);

    node->node_family[LEFT] = left_child;
    node->node_family[RIGHT] = right_child;
    node->node_family[PARENT] = parent;

    node->is_full = is_full;

    return;
}

/*-----------------------------Destroy helper func------------------------------*/
static void TrieRecDestroy(trie_node_t *node)
{
    if (!node)
    {
        return;
    }

    TrieRecDestroy(node->node_family[LEFT]);
    TrieRecDestroy(node->node_family[RIGHT]);

    SetNode(node, NULL, NULL, NULL, 0);

    free(node);
    node = NULL;

    return;
}

/*-----------------------------insert helper_function--------------------------------*/
static dhcp_status_t InerInsert(trie_t *tree, unsigned long *wanted_ip, unsigned long *returned_ip)
{
    trie_node_t *node = NULL;
    unsigned long bits = 0;

    int status = SUCCESS;

    assert(tree);
    assert(wanted_ip);
    assert(returned_ip);

    bits = tree->num_of_bits;
    node = tree->root;

    if ((status = RecInsert(node, bits, wanted_ip, returned_ip)) == MALLOC_FAILED)
    {
        TrieRemove(tree, *wanted_ip);
    }
    return (status);
}

static dhcp_status_t RecInsert(trie_node_t *node,
                               unsigned long bits,
                               unsigned long *wanted_ip,
                               unsigned long *returned_ip)
{
    family_t ip_child_side = 0;

    long status = SUCCESS;

    assert(node);
    assert(wanted_ip);
    assert(returned_ip);

    node = GetIpNode(node, *wanted_ip, &bits, &ip_child_side);
    if (!node->node_family[ip_child_side])
    {
        status = CreatBranch(node, wanted_ip, bits);
        return (status);
    }

    *wanted_ip >>= bits;
    *wanted_ip <<= bits;
    *wanted_ip |= (0x1 << (bits - 1));

    *returned_ip = *wanted_ip;

    return (RecInsert(node, bits, wanted_ip, returned_ip));
}

static trie_node_t *GetIpNode(trie_node_t *node,
                              unsigned long wanted_ip,
                              unsigned long *bits,
                              family_t *ip_child_side)
{
    assert(node);
    assert(ip_child_side);
    assert(bits);

    *ip_child_side = NEXT_NODE_BIT(*bits, wanted_ip);

    while (*bits > 0 && node->node_family[*ip_child_side] && !node->node_family[*ip_child_side]->is_full)
    {
        node = node->node_family[*ip_child_side];
        --*bits;
        *ip_child_side = NEXT_NODE_BIT(*bits, wanted_ip);
    }

    return (node);
}


static dhcp_status_t CreatBranch(trie_node_t *node,
                                 unsigned long *wanted_ip,
                                 unsigned long bits)
{
    trie_node_t *malloced_node = NULL;

    assert(wanted_ip);

    while (bits > 0)
    {
        malloced_node = (trie_node_t *)malloc(sizeof(trie_node_t));
        if (!malloced_node)
        {
            return (MALLOC_FAILED);
        }

        node->node_family[NEXT_NODE_BIT(bits, *wanted_ip)] = malloced_node;
        SetNode(malloced_node, NULL, NULL, node, 0);
        node = NEXT_NODE(node, NEXT_NODE_BIT(bits, *wanted_ip));
        --bits;
    }

    if (bits == 0)
    {
        node->is_full = 1;
    }

    UpDateIsFull(node);

    return (SUCCESS);
}

static void UpDateIsFull(trie_node_t *node)
{
    while (node)
    {
        if ((HAS_RIGHT_CHILD(node) && HAS_LEFT_CHILD(node)) &&
            IS_RIGHT_CHILD_FULL(node) &&
            IS_LEFT_CHILD_FULL(node))
        {
            node->is_full = 1;
        }

        node = PARENT_NODE(node);
    }
}

/*-----------------------------Size helper func--------------------------------*/

static size_t RecTrieSize(trie_node_t *node, size_t hight)
{
    size_t size = 0;

    if (!node)
    {
        return (0);
    }
    if (node->is_full)
    {
        return (0x1 << hight);
    }

    size += RecTrieSize(node->node_family[LEFT], hight - 1);
    size += RecTrieSize(node->node_family[RIGHT], hight - 1);

    return (size);
}

/*-----------------------------Remove helper func--------------------------------*/

static void DestroyBranch(trie_node_t *node, unsigned long wanted_ip, unsigned long bits)
{
    unsigned long bits_left = bits;

    if (!node)
    {
        return;
    }

    if (!bits_left)
    {
        return;
    }

    node->is_full = 0;

    DestroyBranch(node->node_family[NEXT_NODE_BIT(bits_left, wanted_ip)], wanted_ip, bits_left - 1);

    if (node->node_family[NEXT_NODE_BIT(bits_left, wanted_ip)] &&
        node->node_family[NEXT_NODE_BIT(bits_left, wanted_ip)]->is_full)
    {
        free(node->node_family[NEXT_NODE_BIT(bits_left, wanted_ip)]);
        node->node_family[NEXT_NODE_BIT(bits_left, wanted_ip)] = NULL;
    }

    return;
}

int IsIpFree(trie_t *tree, unsigned long wanted_ip)
{
    unsigned long bits = 0;
    family_t ip_child_side = 0;
    trie_node_t *node = NULL;

    assert(tree);

    node = tree->root;
    bits = tree->num_of_bits;
    node = GetIpNode(node, wanted_ip, &bits, &ip_child_side);

    if (node->node_family[ip_child_side] && node->node_family[ip_child_side]->is_full)
    {
        bits = 0;
    }

    return (bits);
}