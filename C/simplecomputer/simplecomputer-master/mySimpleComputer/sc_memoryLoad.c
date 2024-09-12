#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    return -1;
  char buf[128];
  sprintf (buf, "%s", filename);
  FILE *file = fopen (buf, "rb");
  if (file == NULL)
    return -1;
  if (fread (memory, sizeof (int), MEM_SIZE, file) < MEM_SIZE)
    {
      return -2;
    }
  fclose (file);
  return 0;
}