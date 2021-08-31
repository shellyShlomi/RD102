#include <stdio.h> /*printf*/

#include "ilrd_ext2.h"

int main(int argc, char *argv[])
{
  PrintSuperblock("/dev/ram0");
  PrintGroupDescriptor("/dev/ram0");

  PrintFileContent("/dev/ram0", "root");
  return (0);
}