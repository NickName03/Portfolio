#include "mSC.h"
#include "myTerm.h"
#include "print.h"
#include <myReadKey.h>
#include <stdio.h>

void
printTerm ()
{
  int X = 20;
  int Y = 72;
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (X + i, Y);
      write (1, _SCROLL_BUFFER[i], strlen (_SCROLL_BUFFER[i]));
    }
}