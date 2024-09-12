#include "myTerm.h"

int
mt_setdefaultcolor ()
{
  char defcol[] = "\033[0m";
  write (1, defcol, strlen (defcol));
  return 0;
}