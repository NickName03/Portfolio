#include "myBigChars.h"
#include "myReadKey.h"
#include "mySignal.h"
#include "myTerm.h"
#include "print.h"
#include <mSC.h>
#include <stdio.h>
#include <string.h>

int
main (void)
{
  int addres, value = 1, command, operand;
  int rows = 0, cols = 0;
  enum keys key = UNDEF_KEY;
  cur = 0;
  char filename[50];

  mt_getscreensize (&rows, &cols);
  if (rows < 26 || cols < 78)
    {
      char err[] = "Terminal size is too small\n";
      write (2, err, sizeof (err) - 1);
      exit (0);
    }

  sc_defaultInit ();

  printInterface ();
  mt_gotoXY (26, 1);
  while (key != ESC_KEY)
    {
      rk_myTermRegime (0, 1, 1, 0, 0);
      printInterface ();
      mt_gotoXY (26, 1);
      rk_readKey (&key);
      value = 0;
      switch (key)
        {
        case L_KEY:
          write (1, "Введите название файла, который нужно загрузить: ", 91);
          rk_myTermRegime (1, 1, 1, 1, 1);
          value = read (STDIN_FILENO, filename, 50);
          filename[value - 1] = '\0';
          sc_memoryLoad (filename);
          break;

        case S_KEY:
          write (1, "Введите название файла, который будет сохранен: ", 89);
          rk_myTermRegime (1, 1, 1, 1, 1);
          value = read (STDIN_FILENO, filename, 50);
          filename[value - 1] = '\0';
          sc_memorySave (filename);
          break;

        case I_KEY:
          cur = 0;
          sc_defaultInit ();
          break;

        case R_KEY:
          run_event ();
          break;

        case T_KEY:
          step_event ();
          break;

        case F5_KEY:
          rk_myTermRegime (0, 0, 5, 1, 1);
          mt_gotoXY (2, 70);
          if (!rk_readvalue (&value, 2))
            sc_accumulatorSet (value);
          break;

        case F6_KEY:
          rk_myTermRegime (0, 0, 5, 1, 1);
          mt_gotoXY (5, 78);
          if (!rk_readvalue (&value, 2))
            sc_icounterSet (value);
          break;

        case F1_KEY:
          scrollBuf ();
          printTerm ();
          rk_myTermRegime (0, 0, 3, 1, 1);
          mt_gotoXY (20, 72);
          addres = 0;
          rk_readvalue (&addres, 2);
          write (1, "<", 2);
          rk_myTermRegime (0, 0, 5, 1, 1);
          rk_readvalue (&value, 1);
          sc_memorySet (addres, value);
          sc_commandDecode (value, &command, &operand);
          sprintf (_SCROLL_BUFFER[0], "%03d<%c%02X%02X", addres,
                   (value & 0x4000) ? '-' : '+', command, operand);
          break;

        case LEFT_KEY:
          if (cur == 0)
            cur = 127;
          else
            cur--;
          break;

        case RIGHT_KEY:
          if (cur == 127)
            cur = 0;
          else
            cur++;
          break;

        case UP_KEY:
          if (cur <= 9)
            {
              if (cur == 9 || cur == 8)
                cur = 7;
              cur += 120;
            }
          else
            cur -= 10;
          break;

        case DOWN_KEY:
          if (cur <= 127 && cur >= 120)
            cur -= 120;
          else
            {
              if (cur == 118 || cur == 119)
                cur -= 120;
              cur += 10;
            }
          break;

        case ENTER_KEY:
          rk_myTermRegime (0, 0, 5, 1, 0);
          mt_gotoXY (2 + cur / 10, 2 + cur % 10 * 6);
          if (!rk_readvalue (&value, 1))
            {
              sc_memorySet (cur, value);
              scrollBuf ();
              sc_commandDecode (value, &command, &operand);
              sprintf (_SCROLL_BUFFER[0], "%03d>%c%02X%02X", cur,
                       (value & 0x4000) ? '-' : '+', command, operand);
            }
          break;

        default:
          break;
        }
    }
  rk_myTermRegime (1, 1, 1, 1, 1);
  mt_gotoXY (26, 1);
  return 0;
}