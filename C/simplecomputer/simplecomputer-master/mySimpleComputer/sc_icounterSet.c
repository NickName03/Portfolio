#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_icounterSet (int value)
{
  if (value < 0 || value > 128)
    return -1;

  instructionCounter = value;
  return 0;
}