#include <mySignal.h>

void
step_event ()
{
  prevPos = instructionCounter;
  signal (SIGUSR2, CU);
  signal (SIGUSR1, CUerr);

  raise (SIGUSR2);
}