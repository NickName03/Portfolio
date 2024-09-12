#include <mySignal.h>

int
other_operations (int command, int operand)
{
  int cell1 = 0, cell2 = 0, com = 0, op = 0, value = 0;
  switch (command)
    {
    case 0x10:
      // ui_enter (operand);
      break;
    case 0x11:
      sc_memoryGet (operand, &value);
      /*char *buf = itoa (value, 16);

    if (strlen (buf) == 0)
      {
        write (1, "0", 2);
      }
    mt_gotoXY (history++, 1);
    char bababui[50];
    snprintf (bababui, 50, "Memory value from ceil %d: %s", operand, buf);
    int i;
    write (1, bababui, strlen (bababui));
    */
      break;
    case 0x20:
      sc_memoryGet (operand, &value);
      accumulator = value;
      break;
    case 0x21:
      sc_memorySet (operand, accumulator);
      break;
    case 0x40:
      instructionCounter = operand;
      cur = instructionCounter;
      break;
    case 0x41:
      if (accumulator & 0x4000)
        {
          instructionCounter = operand;
          cur = instructionCounter;
        }
      break;
    case 0x42:
      if ((accumulator & 0x7fff) == 0)
        {
          instructionCounter = operand;
          cur = instructionCounter;
        }
      break;
    case 0x43:
      sc_regSet (FLAG_IGNORE_CPU_CLOCKS, 1);
      raise (SIGUSR1);
      break;
    case 0x66:
      sc_memoryGet (operand, &cell1);
      sc_memoryGet (accumulator % 100, &cell2);
      accumulator = cell1 - cell2;
      break;
    case 0x69:
      sc_memoryGet (operand, &value);
      for (int i = 0; i < accumulator; i++)
        {
          value <<= 1;
          value |= (value & 0x8000) ? 1 : 0;
        }
      accumulator = value;
      break;
    case 0x73:
      sc_memoryGet (operand, &cell1);
      sc_commandDecode (accumulator, &com, &op);
      sc_memorySet (op, cell1);
      break;
    case 0x76:
      sc_memoryGet (operand, &cell1);
      sc_commandDecode (accumulator, &com, &op);
      sc_memoryGet (op, &cell2);
      accumulator = cell1 - cell2;
      break;

    default:
      break;
    }
  return 0;
}
