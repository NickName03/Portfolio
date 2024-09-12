#include "myBigChars.h"
#include "myTerm.h"
#include "print.h"
#include <mSC.h>
#include <myReadKey.h>
#include <stdio.h>
#include <string.h>

int
rk_readvalue (int *value, int code)
{
  char buf[6];
  int operand = 0, command = 0;
  char com_buf[3];
  char op_buf[3];
  int fd = open ("/dev/tty", O_RDWR);
  read (fd, buf, 6);
  if (code == 3)
    {
      buf[3] = '\0';
      *value = atoi (buf);
      return -1;
    }
  strncpy (com_buf, buf + 1, 2);
  strncpy (op_buf, buf + 3, 2);
  com_buf[2] = '\0';
  op_buf[2] = '\0';
  if (code == 2)
    {
      command = atoi (com_buf);
      operand = atoi (op_buf);
      *value = ((command)*100) + operand;
    }
  else
    {
      command = strtoul (com_buf, NULL, 16);
      operand = strtoul (op_buf, NULL, 16);
      *value = 0;
      /* Операнд */
      for (int i = 0; i < 7; i++)
        {
          int bit = (operand >> i) & 1;
          *value |= (bit << i);
        }
      /* Команда */
      for (int i = 0; i < 7; i++)
        {
          int8_t bit = (command >> i) & 1;
          *value |= (bit << (i + 7));
        }
    }
  if (buf[0] == '-')
    *value |= 1 << 14;
  if (*value >= 0)
    return 0;

  return -1;
}