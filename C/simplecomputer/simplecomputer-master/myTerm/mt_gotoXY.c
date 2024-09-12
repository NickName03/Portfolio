#include "myTerm.h"

int
mt_gotoXY (int x, int y)
{
  char command[] = "\033[%d;%dH";
  char out[100];
  sprintf (out, command, x, y);
  write (1, out, strlen (out));
  return 0;
}