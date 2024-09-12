#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_commandDecode (int value, int *command, int *operand)
{
  if (command == NULL || operand == NULL)
    return -1;

  *command = (value >> 7) & 0x7f;
  *operand = value & 0x7f;

  if ((value >> 14) == 0)
    return 0;

  return -1;
}