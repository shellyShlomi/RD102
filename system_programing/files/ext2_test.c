#include <stdio.h>  /*printf*/
#include <assert.h> /*assert*/
#include <string.h> /*strlen*/
#include <stdlib.h> /*calloc*/

#include "ilrd_ext2.h"
#include "tools.h"
#include "print_colores.h"

#ifndef NDEBUG
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif

#define UNUSED(x) ((void)(x))
#define SIZE (100)

static void Test(char *argv1, char *argv2);
static void TestInput(char *argv1, char *argv2);
static void TestForDataInvalidtion(char *argv1, char *argv2);
/* static void TestBasedOnMakefile();
 */
int main(int argc, char *argv[])
{
  UNUSED(argc);

  Test(argv[1], argv[2]);

  return (0);
}

static void Test(char *argv1, char *argv2)
{
  TestInput(argv1, argv2);
  TestForDataInvalidtion(argv1, argv2);

  return;
}

static void TestInput(char *argv1, char *argv2)
{
  puts("");

  if (PrintSuperblock(argv1))
  {
    printf("%s", RED);
    printf("PrintSuperblock() failed at line %d\n", __LINE__);
    printf("%s", RESET);
  }
  puts("");

  if (PrintGroupDescriptor(argv1))
  {
    printf("%s", RED);
    printf("PrintGroupDescriptor() failed at line %d\n", __LINE__);
    printf("%s", RESET);
  }
  puts("");

  if (PrintFileContent(argv1, argv2))
  {
    printf("%s", RED);
    printf("PrintFileContent() failed at line %d\n", __LINE__);
    printf("%s", RESET);
  }

  return;
}

static void TestForDataInvalidtion(char *argv1, char *argv2)
{
  char *cpy_argv1 = NULL;
  char *cpy_argv2 = NULL;
  size_t argv1_len = 0;
  size_t argv2_len = 0;
  char message[SIZE] = {'\0'};

  assert(argv1);
  assert(argv2);
  
  puts("");

  argv1_len = strlen(argv1);
  argv2_len = strlen(argv2);

  cpy_argv1 = (char *)calloc(1, argv1_len + 1);
  cpy_argv2 = (char *)calloc(1, argv2_len + 1);
  if (!cpy_argv1 || !cpy_argv2)
  {
    DEBUG printf("calloc error\n");
    return;
  }

  memcpy(cpy_argv1, argv1, argv1_len + 1);
  strcpy(message, "Copy argv1 fail");
  ValidStrEqual(argv1, cpy_argv1, message, __LINE__);

  memcpy(cpy_argv2, argv2, argv2_len + 1);
  strcpy(message, "Copy argv2 fail");
  ValidStrEqual(argv2, cpy_argv2, message, __LINE__);

  PrintSuperblock(cpy_argv1);

  printf("%s", RED);
  strcpy(message, "data invalidation at PrintSuperblock() ");
  ValidStrEqual(cpy_argv1, argv1, message, __LINE__);
  printf("%s\n", RESET);

  PrintGroupDescriptor(cpy_argv1);

  printf("%s", RED);
  strcpy(message, "data invalidation at PrintGroupDescriptor() ");
  ValidStrEqual(cpy_argv1, argv1, message, __LINE__);
  printf("%s", RESET);

  puts("");

  PrintFileContent(cpy_argv1, cpy_argv2);

  printf("%s", RED);
  strcpy(message, "data invalidation at PrintFileContent() ");
  ValidStrEqual(cpy_argv1, argv1, message, __LINE__);
  ValidStrEqual(cpy_argv2, argv2, message, __LINE__);
  printf("%s", RESET);

  free(cpy_argv1);
  free(cpy_argv2);

  return;
}

void TestBasedOnMakefile()

{
  
}