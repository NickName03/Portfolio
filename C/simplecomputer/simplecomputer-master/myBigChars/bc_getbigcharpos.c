#include "myBigChars.h"

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  int pos = 0;
  if ((big == NULL) || (value == NULL) || (x < 0) || (y < 0) || (x > 7)
      || (y > 7))
    return -1;

  if (x < 4)
    pos = 0;
  else
    pos = 1;

  x = x % 4;

  *value = (big[pos] >> (8 * x + y)) & 1;

  return 0;
}