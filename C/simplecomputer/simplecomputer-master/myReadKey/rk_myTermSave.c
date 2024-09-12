#include <myReadKey.h>

int
rk_myTermSave ()
{
  int fd = open ("term.bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
  int tty = open ("/dev/tty", O_RDWR); // Our terminal
  struct termios *buffer = malloc (sizeof (struct termios));

  if (tcgetattr (tty, buffer) != 0) // Получаем текущие настройки терминала
    {
      free (buffer);
      close (fd);
      close (tty);
      return -1;
    }

  if (write (fd, buffer, sizeof (struct termios))
      == -1) // Сохраняем в бинарный файл
    {
      free (buffer);
      close (fd);
      close (tty);
      return -1;
    }

  free (buffer);
  close (fd);
  close (tty);
  return 0;
}