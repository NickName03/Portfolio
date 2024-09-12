#include <myReadKey.h>

int
rk_myTermRestore ()
{
  int file = open ("term.bin", O_RDONLY);
  int tty = open ("/dev/tty", O_RDWR);
  if (file == -1 || tty == -1)
    {
      close (file);
      close (tty);
      return -1;
    }

  struct termios *buffer = malloc (sizeof (struct termios));

  if (read (file, buffer, sizeof (struct termios)) == -1)
    {
      free (buffer);
      close (file);
      close (tty);
      return -1;
    }

  tcsetattr (tty, TCSANOW, buffer);
  free (buffer);
  close (file);
  close (tty);
  return 0;
}