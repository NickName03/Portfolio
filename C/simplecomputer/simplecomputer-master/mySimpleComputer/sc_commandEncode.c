#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  if (value == NULL)
    return -1;
  *value = ((((1 & sign) << 7) | command) << 7) | operand;
  return 0;
}