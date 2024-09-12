#pragma once

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
  ESC_KEY = 300,
  L_KEY,
  S_KEY,
  R_KEY,
  T_KEY,
  I_KEY,
  F1_KEY,
  F5_KEY,
  F6_KEY,
  UP_KEY,
  DOWN_KEY,
  LEFT_KEY,
  RIGHT_KEY,
  BACKSPACE,
  ENTER_KEY,
  UNDEF_KEY,
  PLUS_KEY = 43,
  MINUS_KEY = 45,
  zero = 48,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  A = 65,
  B,
  C,
  D,
  E,
  F
};

int rk_readKey (enum keys *key);
int rk_myTermSave ();
int rk_myTermRestore ();
int rk_myTermRegime (int regime, int vtime, int vmin, int echo, int sigit);
int rk_readvalue (int *value, int code);
