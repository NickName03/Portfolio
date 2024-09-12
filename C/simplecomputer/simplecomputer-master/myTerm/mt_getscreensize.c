#include "myTerm.h"

int
mt_getscreensize (int *rows, int *cols)
{
  if (rows == NULL || cols == NULL)
    {
      return -1;
    }
  struct winsize ws;
  if (ioctl (1, TIOCGWINSZ, &ws))
    return -1;
  *cols = ws.ws_col;
  *rows = ws.ws_row;
  return 0;
}