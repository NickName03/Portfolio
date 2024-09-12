#pragma once

#include <mSC.h>
#include <myReadKey.h>
#include <print.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

extern int prevPos;
extern int isOn;

int ALU (int command, int operand);
void CU ();
void CUerr ();
void IRC (int signum);
int other_operations (int command, int operand);
void run_event ();
void step_event ();
