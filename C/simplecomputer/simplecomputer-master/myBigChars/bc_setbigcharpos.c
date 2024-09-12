#include "myBigChars.h"

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  int pos = 0;

  if ((big == NULL) || (x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0)
      || (value > 1))
    return -1;

  if (x < 4)
    pos = 0;
  else
    pos = 1;

  x = x % 4;

  if (value == 0)
    big[pos] &= ~(1 << (8 * x + y));
  else
    big[pos] |= 1 << (8 * x + y);

  return 0;
}