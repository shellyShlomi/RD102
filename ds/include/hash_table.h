/* VERSION: 1.10 */
#ifndef _OL_HASH_TABLE_H_
#define _OL_HASH_TABLE_H_

#include <stddef.h> /* size_t */

typedef struct hash hash_t;
typedef size_t (*hash_func_t)(const void *key);
typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(const void *data, const void *param);


/* Place in test file:
 * int SpellCheck(char *str); */

hash_t *HashCreate(size_t size, hash_func_t func, match_func_t match);
void HashDestroy(hash_t *hash);

int HashInsert(hash_t *hash, void *key);
void HashRemove(hash_t *hash, const void *key);

void *HashSearch(const hash_t *hash, const void *key);

int HashIsEmpty(const hash_t *hash);
size_t HashSize(const hash_t *hash);

/* DO NOT change the data!!! */
int HashForEach(const hash_t *hash, action_func_t func, void *param);

#endif /* _OL_HASH_TABLE_H_ */
