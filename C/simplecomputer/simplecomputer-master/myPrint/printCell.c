#include "mSC.h"
#include "myTerm.h"
#include "print.h"
#include <stdio.h>

void
printCell (int address, enum colors fg, enum colors bg)
{
  int value, row, col, command, operand;
  char buf[6];

  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value, &command, &operand) < 0)
    return;

  row = address / 10;
  col = address % 10;
  if (cur == address)
    {
      mt_setbgcolor (fg);
      mt_setfgcolor (bg);
    }

  snprintf (buf, 6, "%c%02d%02d", (value & 0x4000) ? '-' : '+', command,
            operand);

  mt_gotoXY (2 + row, 2 + col * 6);

  write (1, buf, 5);
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);
  return;
}