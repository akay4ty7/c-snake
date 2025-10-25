#include "utils.h"

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

void move_cursor(int row, int col) { printf("\033[%d;%dH", row, col); }

void delay(int ms) {
  clock_t start_time = clock();
  while (clock() < start_time + ms * CLOCKS_PER_SEC / 1000) {
  }
  return;
}

void clear_screen(void) {
  printf("\033[H\033[2J");
  return;
}

void clear_input_buffer(void) {
  while (getchar() != '\n') {
  }
  return;
}

void hide_cursor(void) {
  printf("\033[?25l");
  return;
}

void show_cursor(void) {
  printf("\033[?25h");
  return;
}

int rand_range(int min, int max) { return rand() % (max - min + 1) + min; }
