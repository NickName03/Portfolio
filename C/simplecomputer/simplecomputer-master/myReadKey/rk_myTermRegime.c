#include <myReadKey.h>

int
rk_myTermRegime (int regime, int vtime, int vmin, int echo, int sigint)
{
  int tty = open ("/dev/tty", O_RDWR);

  if (tty == -1)
    return -1;

  struct termios *termios = malloc (sizeof (struct termios));
  tcgetattr (tty, termios);

  if (regime != 1)
    {
      termios->c_lflag &= ~ICANON;

      if (echo == 1)
        termios->c_lflag |= ECHO;
      else
        termios->c_lflag &= ~ECHO;

      if (sigint == 1)
        termios->c_lflag |= ISIG;
      else
        termios->c_lflag &= ~ISIG;

      termios->c_cc[VMIN] = vmin;
      termios->c_cc[VTIME] = vtime;
    }
  else
    {
      termios->c_lflag |= ICANON;
      termios->c_lflag |= ECHO;
      termios->c_lflag |= ISIG;
      termios->c_cc[VMIN] = 0;
      termios->c_cc[VTIME] = 0;
    }
  tcsetattr (tty, TCSANOW, termios);
  close (tty);
  free (termios);
  return 0;
}