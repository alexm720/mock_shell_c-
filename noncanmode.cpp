#include "main.h"

void ResetCanonicalMode(int fd, struct termios *savedattributes){
  tcsetattr(fd, TCSANOW, savedattributes);
}

void SetNonCanonicalMode(int fd, struct termios *savedattributes)
{
  struct termios TermAttributes;
  char *name;

  if(!isatty(fd))
  {
    fprintf(stderr, "Not A Terminal.\n");
    exit(0);
  }
  
  tcgetattr(fd, savedattributes);
  tcgetattr(fd, &TermAttributes);
  TermAttributes.c_lflag &= ~(ICANON | ECHO);
  TermAttributes.c_cc[VMIN] = 1;
  TermAttributes.c_cc[VTIME] = 0;
  tcsetattr(fd, TCSAFLUSH, &TermAttributes);
}
