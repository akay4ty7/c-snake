#include "snake.h"

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

void move_snake_right(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]) {
  if (s_segment_p[1][0] < GRID_SIZE - 3) {
    s_segment_p[1][0]++;
  }
}

void move_snake_left(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]) {
  if (s_segment_p[1][0] > 1) {
    s_segment_p[1][0]--;
  }
}

void move_snake_up(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]) {
  if (s_segment_p[0][0] > 1) {
    s_segment_p[0][0]--;
  }
}

void move_snake_down(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]) {
  if (s_segment_p[0][0] < GRID_SIZE - 3) {
    s_segment_p[0][0]++;
  }
}

void move_snake(struct Grid *grid_p, int (*s_segment_p)[GRID_SIZE * GRID_SIZE],
                enum Input *s_direction_p) {
  grid_p->grid[s_segment_p[0][0]][s_segment_p[1][0]] = '.';
  switch (*s_direction_p) {
  case UP:
    move_snake_up(s_segment_p);
    break;
  case DOWN:
    move_snake_down(s_segment_p);
    break;
  case LEFT:
    move_snake_left(s_segment_p);
    break;
  case RIGHT:
    move_snake_right(s_segment_p);
    break;
  default:
    printf("Invalid\n");
    break;
  }
  assign_entity_to_grid_cell(grid_p, s_segment_p[0][0], s_segment_p[1][0], '@');
}
