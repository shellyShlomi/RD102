/* Version 2 - 14.06.2021 16:30 */

#ifndef _OL_102_Trie_H_
#define _OL_102_Trie_H_

#include <stddef.h>     /* size_t */
#include "dhcp.h"

typedef struct trie trie_t;
typedef enum family
{
    LEFT,
    RIGHT,
    PARENT,
    FAMILY_SIZE
}family_t;


trie_t *TrieCreate(size_t num_of_bits);

void TrieDestroy(trie_t *tree);

dhcp_status_t TrieInsert(trie_t *tree, unsigned long wanted_ip, unsigned long *returned_ip);

void TrieRemove(trie_t *tree, unsigned long ip);

size_t TrieSize(trie_t *tree);

int IsIpFree(trie_t *tree, unsigned long wanted_ip);


#endif /* _OL_102_Trie_H_ */


