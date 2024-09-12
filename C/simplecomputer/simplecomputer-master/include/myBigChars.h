#pragma once

#include "myTerm.h"
#include <errno.h>
#include <mSC.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BOXCHAR_TR "k"
#define BOXCHAR_HOR "q"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_REC 'a'

extern int bigChars[18][2];

int bc_strlen (char *str);
int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2, enum colors box_fg,
            enum colors box_bg, char *header, enum colors header_fg,
            enum colors header_bg);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_printbigchar (int *big, int x, int y, enum colors fg, enum colors bg);
int bc_bigcharwrite (int fd, int *big, int count);
int bc_bigcharread (int fd, int *big, int need_count, int *count);