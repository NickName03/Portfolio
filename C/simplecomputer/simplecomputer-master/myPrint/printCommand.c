#include "mSC.h"
#include "myTerm.h"
#include "print.h"
#include <stdio.h>

void
printCommand ()
{
  int value = 0, pos = 0;
  int sign = 0, command, operand, returncode;
  sc_icounterGet (&pos);
  sc_memoryGet (pos, &value);
  sc_commandDecode (value, &command, &operand);
  returncode = sc_commandValidate (command);
  if (returncode != 0 || sign != 0)
    {
      printf ("  !  + FF : FF\n");
    }
  else
    {
      printf ("    + %d : %d\n", command, operand);
    }
}