#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_memorySet (int address, int value)
{
  if (address >= MEM_SIZE || address < 0)
    {
      return -1;
    }
  memory[address] = value;
  return 0;
}