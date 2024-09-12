#include "myTerm.h"

int
mt_setcursorvisible (int value)
{
  char unvis[] = "\033[?25l";
  char vis[] = "\033[?12l\033[?25h";
  if (value != 1 || value != 0)
    return -1;
  if (value)
    write (1, unvis, strlen (unvis));
  else
    write (1, vis, strlen (vis));
  return 0;
}