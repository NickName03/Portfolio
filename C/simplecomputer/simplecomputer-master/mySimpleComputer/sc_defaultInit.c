#include "mSC.h"
#include "print.h"
#include <stdio.h>

void
sc_defaultInit ()
{
  sc_regInit ();
  sc_accumulatorInit ();
  sc_memoryInit ();
  sc_icounterInit ();
  sc_regSet (FLAG_IGNORE_CPU_CLOCKS, 1);
}