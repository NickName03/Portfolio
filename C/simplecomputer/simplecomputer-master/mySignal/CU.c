#include "mSC.h"
#include "mySignal.h"
#include "print.h"
#include <stdio.h>

#include <signal.h>
typedef void (*sighandler_t) (int);
sighandler_t signal (int signum, sighandler_t handler);

void
CU ()
{
  int value, command, operand;
  if (sc_memoryGet (instructionCounter, &value) != 0
      || sc_commandDecode (value, &command, &operand) != 0
      || !(operand >= 0
           && (((command >= 0x10) && (command <= 0x11))
               || ((command >= 0x20) && (command <= 0x21))
               || ((command >= 0x30) && (command <= 0x33))
               || ((command >= 0x40) && (command <= 0x43))
               || ((command >= 0x51) && (command <= 0x76)))))
    {
      raise (SIGUSR1);
      return;
    }
  if (instructionCounter + 1 == 100)
    {
      instructionCounter++;
      raise (SIGUSR1);
      return;
    }

  instructionCounter++;
  cur = instructionCounter;
  if (ALU (command, operand) == -1)
    {
      other_operations (command, operand);
    }
}