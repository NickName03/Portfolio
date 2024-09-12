#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_memoryInit ()
{
  for (int i = 0; i < MEM_SIZE; i++)
    {
      memory[i] = 0;
    }
  return 0;
}