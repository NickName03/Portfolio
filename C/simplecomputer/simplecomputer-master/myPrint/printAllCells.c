#include "mSC.h"
#include "myTerm.h"
#include "print.h"
#include <stdio.h>

void
printAllCells ()
{
  for (int i = 0; i < 128; i++)
    {
      printCell (i, WHITE, BLACK);
    }
}