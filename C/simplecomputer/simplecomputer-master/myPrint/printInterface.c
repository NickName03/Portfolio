#include <mSC.h>
#include <myBigChars.h>
#include <myTerm.h>
#include <print.h>

void
printInterface ()
{
  char keys[5][28]
      = { "l - load s - save i - reset", "r - run t - step", "ESC - exit",
          "F5 - accumulator", "F6 - instruction counter" };

  mt_clrscr ();
  bc_box (1, 1, 15, 62, WHITE, BLACK, "Оперативная память", RED, BLACK);
  printAllCells ();

  bc_box (1, 64, 3, 86, WHITE, BLACK, "Аккумулятор", RED, BLACK);
  printAccumulator ();

  bc_box (1, 90, 3, 110, WHITE, BLACK, "Регистр флагов", RED, BLACK);
  printFlags ();

  bc_box (4, 64, 6, 86, WHITE, BLACK, "Счетчик команд", RED, BLACK);
  printCounter ();

  bc_box (4, 90, 6, 110, WHITE, BLACK, "Команда", RED, BLACK);
  printDecodeOperations ();

  bc_box (19, 1, 25, 70, WHITE, BLACK, "Кеш процессора", GREEN, WHITE);

  bc_box (19, 71, 25, 81, WHITE, BLACK, "IN--OUT", GREEN, WHITE);
  printTerm ();

  bc_box (19, 82, 25, 110, WHITE, BLACK, "Клавиши", GREEN, WHITE);
  for (int i = 0; i < 5; i++)
    {
      mt_gotoXY (20 + i, 83);
      write (1, keys[i], strlen (keys[i]));
    }

  bc_box (16, 1, 18, 62, WHITE, BLACK, "Редактируемая ячейка (формат)", RED,
          WHITE);
  printEditCell ();

  bc_box (7, 64, 18, 110, WHITE, BLACK, "Редактируемая ячейка (увеличенно)",
          RED, WHITE);
  printBigCell ();
}