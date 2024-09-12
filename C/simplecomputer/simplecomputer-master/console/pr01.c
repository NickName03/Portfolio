#include "../include/mSC.h"
#include "../include/print.h"
#include <stdio.h>
#include <time.h>

int
main ()
{
  srand (time (NULL));
  int value = 1, value2 = 1;
  int com = 0, op = 0;
  int resultfunc = 0;

  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_icounterInit ();
  sc_regInit ();

  for (int i = 0; i < 128; i++)
    {
      sc_memorySet (i, rand () % 100);
    }
  printf ("\nthe contents of RAM:\n");
  for (int i = 0; i < 128; i++)
    {
      sc_memoryGet (i, &value);
      printf ("%d ", value);
      if ((i + 1) % 10 == 0)
        printf ("\n");
    }
  printf ("\n---------------------------\n");

  resultfunc = sc_memorySet (777, 125);
  printf ("\nan attempt to place a memory cell at an invalid address: %d",
          resultfunc);

  value = 1;
  sc_regSet (1, value);
  sc_regSet (3, value);
  sc_regSet (4, value);
  printf ("\nregistr after regSet[1, 3, 4]:\n");
  printFlags ();

  resultfunc = sc_regSet (10, 5);
  printf ("\nan attempt to set an invalid value to a registr: %d", resultfunc);

  sc_accumulatorSet (534);
  sc_accumulatorGet (&value);
  printf ("\naccumulator Get: %d\n", value);
  printAccumulator ();

  resultfunc = sc_accumulatorSet (-534);
  printf ("\nan attempt to set an invalid value to an accumulator: %d",
          resultfunc);

  sc_icounterSet (14);
  sc_icounterGet (&value);
  printf ("\ninstructionCounter Get: %d\n", value);
  printCounter ();

  resultfunc = sc_icounterSet (-43);
  printf ("\nan attempt to set an invalid value to an instructionCounter: %d",
          resultfunc);

  sc_memoryGet (14, &value2);
  sc_commandDecode (value2, &com, &op);
  printf ("\nmemory:\nencoded: %d\ndecoded command: %d\ndecoded operand: %d\n",
          value2, com, op);
  sc_accumulatorGet (&value2);
  sc_commandDecode (value2, &com, &op);
  printf ("\naccumulator:\nencoded: %d\ndecoded command: %d\ndecoded operand: "
          "%d\n",
          value2, com, op);

  sc_commandEncode (76, 78, &value2);
  printf ("\nencode: %d\n", value2);

  return 0;
}