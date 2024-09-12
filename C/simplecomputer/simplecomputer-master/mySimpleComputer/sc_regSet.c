#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_regSet (int reg, int value)
{
  if (reg < 0 || reg > 5)
    return -1;

  if (value)
    registr = registr | (1 << (reg - 1));
  else
    {
      if (!value)
        registr = registr & (~(1 << (reg - 1)));
      else
        return -1;
    }
  return 0;
}