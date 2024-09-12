#include "mSC.h"
#include "myTerm.h"
#include "print.h"
#include <stdio.h>

void
printEditCell ()
{
  int value = 0;
  char red_cur[58], binary[16];
  mt_gotoXY (17, 2);
  sc_memoryGet (cur, &value);
  for (int i = 15, j = 0; i >= 0 && j < 16; --i, j++)
    {
      binary[j] = ((value & (1 << (i - 1))) ? 1 : 0) + '0';
    }
  sprintf (red_cur, "dec: %05d | oct: %05o | hex: %04X    bin: ", value, value,
           value);
  write (1, red_cur, sizeof (red_cur) - 1);
  mt_gotoXY (17, 46);
  write (1, binary, sizeof (binary) - 1);
}