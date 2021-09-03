#include <stdio.h> /*printf*/

#include "ilrd_ext2.h"
#define UNUSED(x) ((void)(x))

int main(int argc, char *argv[])
{
  UNUSED(argc);
  puts("");
  PrintSuperblock(argv[1]);
  puts("");
  PrintGroupDescriptor(argv[1]);
  puts("");
  PrintFileContent(argv[1], argv[2]);

  return (0);
}