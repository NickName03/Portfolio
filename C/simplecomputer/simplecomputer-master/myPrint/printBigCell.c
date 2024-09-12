#include <mSC.h>
#include <myBigChars.h>
#include <myTerm.h>
#include <print.h>

void
printBigCell ()
{
  int value = 0;
  char split_digit[6];
  int command = 0, operand = 0;
  char red_cur[56];
  sc_memoryGet (cur, &value);
  sc_commandDecode (value & 0x3FFF, &command, &operand);
  snprintf (split_digit, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+',
            command, operand);
  if (split_digit[0] == '+')
    bc_printbigchar (bigChars[16], 8, 68, BLACK, WHITE);
  else
    bc_printbigchar (bigChars[17], 8, 68, BLACK, WHITE);
  for (int i = 1; i < 5; i++)
    {
      value = split_digit[i] - '0';
      if (value > 16)
        value -= 7;
      bc_printbigchar (bigChars[value], 8, 68 + (i * 8), BLACK, WHITE);
    }
  mt_gotoXY (17, 65);
  sprintf (red_cur, "Номер редактируемой ячейки %04d", cur);
  mt_setfgcolor (BLUE);
  write (1, red_cur, strlen (red_cur));
  mt_setfgcolor (WHITE);
}