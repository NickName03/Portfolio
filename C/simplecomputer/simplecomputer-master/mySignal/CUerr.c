#include <mySignal.h>

void
CUerr ()
{
  sc_regSet (FLAG_IGNORE_CPU_CLOCKS, 1);
  isOn = 0;
  int value, command, operand;
  if (sc_memoryGet (instructionCounter, &value) != 0)
    {
      sc_regSet (FLAG_OUT_OF_BOUNDS, 1);
    }
  if (sc_commandDecode (value, &command, &operand) != 0
      || (!(operand >= 0
            && (((command >= 0x10) && (command <= 0x11))
                || ((command >= 0x20) && (command <= 0x21))
                || ((command >= 0x30) && (command <= 0x33))
                || ((command >= 0x40) && (command <= 0x43))
                || ((command >= 0x51) && (command <= 0x76))))
          && instructionCounter != 100))
    sc_regSet (FLAG_UNDEFINED_COMMAND, 1);

  instructionCounter = prevPos;
  cur = prevPos;

  alarm (0);
}
