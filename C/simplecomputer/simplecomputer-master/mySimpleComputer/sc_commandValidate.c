#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_commandValidate (int command)
{
  if ((command >> 14) == 0)
    return 0;

  return -1;
}