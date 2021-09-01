#include <stdio.h> /*printf*/

#include "ilrd_ext2.h"
#define UNUSED(x) ((void)(x))

int main(int argc, char *argv[])
{
  UNUSED(argc);
/*   PrintSuperblock(argv[1]);
  PrintGroupDescriptor(argv[1]); */
  PrintFileContent(argv[1], argv[2]);
  
  return (0);
}