#include "mSC.h"
#include "myBigChars.h"
#include "myTerm.h"
#include <stdlib.h>
#include <time.h>

extern int instruction_counter;

int bigChars[18][2] = {
  { 1717976064, 3958374 }, { 1010315264, 3158064 }, { 1010842624, 8258050 },
  { 2120252928, 8282238 }, { 2120640000, 6316158 }, { 1040350720, 4079680 },
  { 35789824, 1974814 },   { 811630080, 396312 },   { 1013332992, 3958374 },
  { 2087074816, 3956832 }, { 2118269952, 4342338 }, { 1044528640, 4080194 },
  { 37895168, 3949058 },   { 1111637504, 4080194 }, { 2114092544, 8258050 },
  { 33717760, 131646 },    { 2115508224, 1579134 }, { 2113929216, 0 }
};

int
main ()
{
  int fd = 0;
  fd = open ("big_chars.fon", O_CREAT | O_WRONLY | O_TRUNC, 0666);
  if (fd == -1)
    {
      write (2, "write err\n", 11);
      exit (0);
    }
  bc_bigcharwrite (fd, (int *)bigChars, (int)sizeof (bigChars) / 8);
  close (fd);
}
