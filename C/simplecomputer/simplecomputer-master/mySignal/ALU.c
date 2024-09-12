#include "mSC.h"
#include "mySignal.h"
#include "print.h"
#include <stdio.h>

int
ALU (int command, int operand)
{
  int value = 0;
  sc_memoryGet (operand, &value);

  switch (command)
    {
    case 0x30: /* ADD */
      accumulator += value;
      break;
    case 0x31: /* SUB */
      accumulator -= value;
      break;
    case 0x32: /* DIVIDE */
      if (value)
        accumulator /= value;
      else
        sc_regSet (FLAG_DEL_ZERO, 1);
      break;
    case 0x33: /* MUL */
      accumulator *= value;
      break;

    default:
      return -1;
    }

  return 0;
}