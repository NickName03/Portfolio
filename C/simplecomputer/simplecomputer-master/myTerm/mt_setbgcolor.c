#include "myTerm.h"

int
mt_setbgcolor (enum colors color)
{
  char bg[] = "\033[4%dm";
  char out[100];
  sprintf (out, bg, color);
  write (1, out, strlen (out));
  return 0;
}