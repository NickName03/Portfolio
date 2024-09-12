#include "mSC.h"
#include "print.h"
#include <stdio.h>

void
printAccumulator ()
{
  mt_gotoXY (2, 66);
  char buf[20];
  snprintf (buf, 20, "sc: %c%04d hex: %04X",
            (accumulator & 0x4000) ? '-' : '+', accumulator, accumulator);

  write (1, buf, 20);
}