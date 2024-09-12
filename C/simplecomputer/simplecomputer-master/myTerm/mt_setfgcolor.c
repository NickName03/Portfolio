#include "myTerm.h"

int
mt_setfgcolor (enum colors color)
{
  char bg[] = "\033[3%dm";
  char out[100];
  sprintf (out, bg, color);
  write (1, out, strlen (out));
  return 0;
}