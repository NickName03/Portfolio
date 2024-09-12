#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_regGet (int reg, int *value)
{
  if (reg < 0 || reg > 5 || value == NULL)
    return -1;

  *value = (registr >> (reg - 1)) & 0x1;
  return 0;
}