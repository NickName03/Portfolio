#include <mySignal.h>

void
run_event ()
{
  sc_regSet (FLAG_IGNORE_CPU_CLOCKS, 0);
  printFlags ();
  prevPos = instructionCounter;
  struct itimerval nval, oval;
  int ignore;
  isOn = 1;

  cur = instructionCounter;
  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 60000;
  nval.it_value.tv_sec = 0;
  nval.it_value.tv_usec = 60000;

  sc_regGet (FLAG_IGNORE_CPU_CLOCKS, &ignore);
  if (ignore == 1)
    return;
  signal (SIGALRM, CU);
  signal (SIGUSR1, CUerr);
  setitimer (ITIMER_REAL, &nval, &oval);
  struct termios orig_options;
  if (tcgetattr (STDIN_FILENO, &orig_options) != 0)
    return;
  if (rk_myTermRegime (0, 0, 1, 0, 1) != 0)
    return;
  while (isOn)
    {
      pause ();
    }
  if (tcsetattr (STDIN_FILENO, TCSAFLUSH, &orig_options) != 0)
    return;
}
