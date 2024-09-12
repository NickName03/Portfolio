#include "myBigChars.h"

int
bc_strlen (char *str)
{
  if (str == NULL)
    return 0;
  int i = 0, j = 0;
  while (str[i])
    {
      if ((str[i] & 0xc0) != 0x80)
        j++;
      i++;
    }
  return j;
}