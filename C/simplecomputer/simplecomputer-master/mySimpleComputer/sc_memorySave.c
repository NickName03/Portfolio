#include "mSC.h"
#include "print.h"
#include <stdio.h>

int
sc_memorySave (char *filename)
{
  if (filename == NULL)
    return -1;
  char buf[128];
  sprintf (buf, "%s", filename);
  FILE *file = fopen (buf, "wb");
  if (file == NULL)
    return -1;
  if (fwrite (memory, sizeof (int), MEM_SIZE, file) < MEM_SIZE)
    {
      fclose (file);
      return -2;
    }
  fclose (file);
  return 0;
}