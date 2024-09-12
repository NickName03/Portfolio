#include "mSC.h"
#include "print.h"
#include <stdio.h>

void
printCounter ()
{
  char iCounter[16];
  mt_gotoXY (5, 68);
  snprintf (iCounter, 16, "T: 00 IC: +%04d", instructionCounter);
  write (1, iCounter, 15);
}