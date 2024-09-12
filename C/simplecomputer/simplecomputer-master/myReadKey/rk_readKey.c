#include <myReadKey.h>
#include <myTerm.h>

int
rk_readKey (enum keys *key)
{
  char buf[10];
  int fd = open ("/dev/tty", O_RDWR);
  if (fd == -1)
    {
      *key = ESC_KEY;
      return -1;
    }
  int num_read = read (fd, buf, 10);
  if (num_read < 0)
    return -1;
  buf[num_read] = '\0';
  if (strcmp (buf, "l") == 0)
    *key = L_KEY;
  else if (strcmp (buf, "s") == 0)
    *key = S_KEY;
  else if (strcmp (buf, "r") == 0)
    *key = R_KEY;
  else if (strcmp (buf, "t") == 0)
    *key = T_KEY;
  else if (strcmp (buf, "i") == 0)
    *key = I_KEY;
  else if (buf[0] == 127)
    *key = BACKSPACE;
  else if (strcmp (buf, "\n") == 0)
    *key = ENTER_KEY;
  else if (strcmp (buf, "c") == 0)
    *key = F1_KEY;
  else if (strcmp (buf, "\033[15~") == 0)
    *key = F5_KEY;
  else if (strcmp (buf, "\033[17~") == 0)
    *key = F6_KEY;
  else if (strcmp (buf, "\033") == 0)
    *key = ESC_KEY;
  else if (strcmp (buf, "\033[A") == 0)
    *key = UP_KEY;
  else if (strcmp (buf, "\033[B") == 0)
    *key = DOWN_KEY;
  else if (strcmp (buf, "\033[C") == 0)
    *key = RIGHT_KEY;
  else if (strcmp (buf, "\033[D") == 0)
    *key = LEFT_KEY;
  else if (strcmp (buf, "+") == 0)
    *key = PLUS_KEY;
  else if (strcmp (buf, "-") == 0)
    *key = MINUS_KEY;
  else if ((buf[0] >= 48 && buf[0] <= 57) || (buf[0] >= 65 && buf[0] <= 70))
    *key = buf[0] - '\0';
  else
    *key = UNDEF_KEY;
  return 0;
}