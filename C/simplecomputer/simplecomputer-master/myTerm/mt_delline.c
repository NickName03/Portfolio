#include "myTerm.h"

int
mt_delline ()
{
  char del_str[] = "\033[1K";
  write (1, del_str, strlen (del_str));
  return 0;
}