#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_memoryGet (int address, int *value)
{
  if (address >= MEM_SIZE || address < 0 || value == NULL)
    {
      return -1;
    }
  *value = memory[address];
  return 0;
}