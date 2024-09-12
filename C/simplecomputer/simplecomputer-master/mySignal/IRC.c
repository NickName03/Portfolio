#include "mSC.h"
#include "mySignal.h"
#include "print.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void
IRC (int signum)
{
  int interactMode = 0;
  sc_regGet (2, &interactMode);

  if (signum == SIGUSR1)
    {
      sc_regSet (2, !interactMode);
    }
  else if (signum == SIGUSR2)
    {
      CU ();
    }
  else if (signum == SIGALRM)
    {
      if (!interactMode)
        {
          CU ();
          // mt_printScreen();
        }
    }
}