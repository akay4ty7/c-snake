#include "inptlib.h"

#ifndef TERMIOS_H
#define TERMIOS_H
#include <termios.h>
#endif

#ifndef UNISTD_H
#define UNISTD_H
#include <unistd.h>
#endif

static struct termios og_settings;

void enable_raw_mode(void) {
  // saving current terminal settings to og
  tcgetattr(STDIN_FILENO, &og_settings);

  // copy og settings for manipulation purpose
  struct termios raw = og_settings;

  // disable canon mode and echo
  raw.c_lflag &= ~(ICANON | ECHO);

  // set vmin and vtime to 0
  // read returns imediately if no bytes avail
  // no timeout
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;

  // apply the settings
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode(void) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &og_settings);
}

char get_input(void) {
  char c = 0;
  read(STDIN_FILENO, &c, 1);
  return c;
}
