/*  Developer: Shelly Shlomi;									*
 *  Status: Approved;        									*
 *  Date Of Creation:09.06.21;									*
 *  Date Of Approval:10.06.21;									*
 *  Approved By: ohad                                      		*
 *  Description: Recurtion;			                    		*/

#include <stddef.h> /* size_t */
#include <assert.h>

#include "recursion.h"

static void StackInsert(stack_t *stack, int *num);

struct node
{
    void *data;
    struct node *next;
};



int RecursiveFibonacci(int element_index)
{
    assert(element_index >= 0);

    if (element_index < 2)
    {
        return (element_index);
    }
    
    return (RecursiveFibonacci(element_index - 2) + RecursiveFibonacci(element_index - 1));
}


int IterativeFibonacci(int element_index)
{
    int res = 1;   
    int prev = 0;   
    
    assert(element_index >= 0);
    
    if (0 == element_index)
    {
        return element_index;
    }

    while (1 < element_index)
    {
        res = res + prev;
        prev = res - prev;
        --element_index;
    }

    return (res);
}

node_t *FlipList(node_t *node)
{
    node_t *to_be_head = NULL;

    assert(node);

    if (!(node->next))
    {
        return (node);
    }

    to_be_head = FlipList(node->next);
    
    node->next->next = node;
    node->next = NULL;

    return (to_be_head);
}



size_t StrLen(const char *s)
{
    assert(s);

    if (*s == '\0')
    {
        return (0);
    }

    return (StrLen(s + 1) + 1);
}


int StrCmp(const char *s1, const char *s2)
{
    assert(s1);
    assert(s2);

    if ((*s2 != *s1) || (*s2 == '\0'))
    {
        return (*s1 - *s2);
    }
    return (StrCmp(s1 + 1, s2 + 1));
}


char *StrCpy(char *dest, const char *src)
{
    assert(src);
    assert(dest);
    
    *dest = *src;

    if (*src == '\0')
    {
        return (dest);
    }

    StrCpy((dest + 1), (src + 1));

    return (dest);
}

char *StrCat(char *dest, const char *src)
{
    assert(src);
    assert(dest);
    
    if (*dest != '\0')
    {
        StrCat((dest + 1), src);
        return (dest);
    }

    if (*src == '\0')
    {   
        return (dest);
    }

    *dest = *src;
    *(dest + 1) = '\0';

    StrCat((dest + 1), (src + 1));
    return (dest);

}

char *StrStr(const char *haystack, const char *needle)
{
    assert(haystack);
    assert(needle);
    
    if ('\0' == *needle)
    {
        return ((char *)haystack);
    }

    if ('\0' == *haystack)
    {
        return (NULL);
    }

    if ((*haystack == *needle) && (haystack + 1) == (StrStr(haystack + 1, needle + 1)))
    {
        return ((char *)haystack);
    }

    return (StrStr(haystack + 1, needle));
}


void StackSort(stack_t *stack)
{
    int *num = NULL;
   
    assert(stack);

    if (1 == StackSize(stack))
    {          
        return ;
    }
    
    num  = (int *)StackPeek(stack);
    StackPop(stack);
   
    StackSort(stack);
    StackInsert(stack, num);

    return;
}

static void StackInsert(stack_t *stack, int *num)
{
    int *peek = NULL;

    assert(stack);

    if (StackIsEmpty(stack) || (*num > *(int *)StackPeek(stack)))
    {
        StackPush(stack, (void *)num);
        return;
    }

    peek = (int *)StackPeek(stack);

    StackPop(stack);

    StackInsert(stack, num);
    StackPush(stack, (void *)peek);

    return;

}