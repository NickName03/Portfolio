#include <mSC.h>
#include <myTerm.h>
#include <stdio.h>
#include <stdlib.h>

extern int cur;
extern char _SCROLL_BUFFER[6][10];

void printCell (int address, enum colors fg, enum colors bg);
void printFlags ();
void printCounter ();
void printAccumulator ();
void printDecodeOperations ();
void printCommand ();
void printTerm ();
void printEditCell ();
void printAllCells ();
void printInterface ();
void printBigCell ();
void scrollBuf ();