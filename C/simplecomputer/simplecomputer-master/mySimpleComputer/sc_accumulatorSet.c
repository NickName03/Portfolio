#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_accumulatorSet (int value)
{
  if (value < 0 || value > 32768)
    return -1;

  accumulator = value;
  return 0;
}