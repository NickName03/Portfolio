#include "myTerm.h"

int
mt_clrscr ()
{
  char clearscr[] = "\033[H\033[2J";
  write (1, clearscr, strlen (clearscr));
  return 0;
}