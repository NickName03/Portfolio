#pragma once

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum colors
{
  BLACK,
  RED,
  GREEN,
  ORANGE,
  BLUE,
  PURPLE,
  CYAN,
  WHITE
};

int mt_clrscr ();
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);
int mt_setdefaultcolor ();
int mt_setcursorvisible (int value);
int mt_delline ();
int mt_printScreen ();