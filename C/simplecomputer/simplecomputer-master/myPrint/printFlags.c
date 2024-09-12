#include "mSC.h"
#include "print.h"
#include <myTerm.h>
#include <stdio.h>

void
printFlags ()
{
  mt_gotoXY (2, 96);
  char flags[] = "P0MTE";
  char buf[2];
  buf[1] = ' ';
  int a = 0;
  for (int i = 0; i < 5; i++)
    {
      sc_regGet (i, &a);
      if (a)
        {
          buf[0] = flags[i];
        }
      else
        {
          buf[0] = '_';
        }
      write (1, buf, 2);
    }
}