#include <stdio.h>

typedef struct Person Person_t;

typedef struct List List_t;

struct List
{
    char *b;
    int a;
    Person_t *person;
};

struct Person
{
    char *str;
    int age;
};

void *ll_find(List_t *ll, int key)
{
    return NULL;
}

void foo(List_t *ll, int key, int age)
{
    void *vv = ll_find(ll, key);
    int *v;
    char *k;

    Person_t *p = NULL;
    /*     p = static_cast<Person_t *>(ll);
    v = static_cast<int *>(k); */
    /*     printf("%d\n", p->age);
    p->age = age;
    printf("%d\n", p->age); */
}

int main(void)
{
    int b1 = 2;
    float b2 = 9.9;
    char b3 = 'b';
/*     Person_t i = {&b3, 4};
    List_t ll = {&b2, 1, &i}; */
    b1 = static_cast<int>(b2);
    printf("%d\n", b1);
    return (0);
}