#include "myBigChars.h"

int
bc_printA (char *str)
{
  if (str == NULL)
    return -1;
  char command[] = "\033(0%s\033(B";
  char out[100];
  sprintf (out, command, str);
  write (1, out, strlen (out));

  return 0;
}