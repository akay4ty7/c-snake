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

void delay(int ms) {
  clock_t start_time = clock();
  while (clock() < start_time + ms * CLOCKS_PER_SEC / 1000) {
  }
}

int rand_range(int min, int max) { return rand() % (max - min + 1) + min; }

void clear_screen(void) { printf("\033[H\033[2J"); }
