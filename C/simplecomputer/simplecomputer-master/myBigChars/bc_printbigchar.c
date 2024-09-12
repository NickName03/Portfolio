#include "myBigChars.h"
#include "myTerm.h"

int
bc_printbigchar (int *big, int x, int y, enum colors bg, enum colors fg)
{
  int maxx = 0, maxy = 0;
  int i = 0, j = 0;
  char row[9];

  mt_getscreensize (&maxx, &maxy);

  if ((big == NULL) || (x < 0) || (y < 0) || (x + 8 > maxx) || (y + 8 > maxy))
    return -1;

  row[8] = '\0';
  mt_setfgcolor (fg);
  mt_setbgcolor (bg);
  for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
        {
          int value = 0;
          bc_getbigcharpos (big, i, j, &value);
          if (!value)
            row[j] = ' ';
          else
            row[j] = BOXCHAR_REC;
        }
      mt_gotoXY (x + i, y);
      bc_printA (row);
    }

  return 0;
}