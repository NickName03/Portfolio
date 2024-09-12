#include "mSC.h"
#include "print.h"
#include <stdio.h>

void
printDecodeOperations ()
{
  char operat[9];
  int value, command, operand;
  sc_memoryGet (instructionCounter, &value);
  sc_commandDecode (value, &command, &operand);
  mt_gotoXY (5, 96);
  if (value & 0x4000)
    {
      write (1, "+00 : 00", 9);
      return;
    }
  else
    {
      snprintf (operat, 9, "%c%02X : %02X", (value & 0x4000) ? '-' : '+',
                command, operand);
      write (1, operat, 9);
    }
}