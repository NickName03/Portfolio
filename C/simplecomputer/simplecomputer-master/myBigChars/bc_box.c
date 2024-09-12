#include "myBigChars.h"
#include "myTerm.h"

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        char *header, enum colors header_fg, enum colors header_bg)
{
  int header_len = -1;
  int tab = 0;

  if (header != NULL)
    {
      header_len = bc_strlen (header);
      tab = ((y2 - y1 - header_len) / 2);
      mt_gotoXY (x1, y1 + tab);
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      write (1, header, strlen (header));
    }
  mt_setfgcolor (box_fg);
  mt_setbgcolor (box_bg);
  mt_gotoXY (x1, y1);
  bc_printA (BOXCHAR_TL);
  for (int i = y1 + 1; i < y2; i++)
    {
      if (header_len != -1)
        {
          if (i == y1 + tab)
            {
              mt_gotoXY (x1, y2 - tab);
              i = y2 - tab - 1;
              continue;
            }
        }
      bc_printA (BOXCHAR_HOR);
    }
  bc_printA (BOXCHAR_TR);

  for (int i = x1 + 1; i < x2; i++)
    {
      mt_gotoXY (i, y1);
      bc_printA (BOXCHAR_VERT);
      mt_gotoXY (i, y2);
      bc_printA (BOXCHAR_VERT);
    }

  mt_gotoXY (x2, y1);
  bc_printA (BOXCHAR_BL);
  for (int i = y1 + 1; i < y2; i++)
    bc_printA (BOXCHAR_HOR);
  bc_printA (BOXCHAR_BR);

  return 0;
}