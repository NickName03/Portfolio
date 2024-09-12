#pragma once

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define MEM_SIZE 128

enum FLAGS
{
  FLAG_OVERFLOW = 0b00000000,
  FLAG_DEL_ZERO = 0b00000001,
  FLAG_OUT_OF_BOUNDS = 0b00000010,
  FLAG_IGNORE_CPU_CLOCKS = 0b00000011,
  FLAG_UNDEFINED_COMMAND = 0b00000100,
};

extern int memory[128];
extern int registr;
extern int accumulator;
extern int instructionCounter;

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit ();
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_accumulatorInit ();
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit ();
int sc_icounterSet (int value);
int sc_icounterGet (int *value);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
int sc_commandValidate (int command);
void sc_defaultInit ();