#include "grid.h"
#include "inptlib.h"

#ifndef SNAKE_H
#define SNAKE_H

struct Snake {
  enum Input direction;
  int segment[2][GRID_SIZE * GRID_SIZE];
};

void move_snake(struct Grid *grid_p, int (*s_segment_p)[GRID_SIZE * GRID_SIZE],
                enum Input *s_direction_p);
void move_snake_up(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]);
void move_snake_down(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]);
void move_snake_left(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]);
void move_snake_right(int (*s_segment_p)[GRID_SIZE * GRID_SIZE]);

#endif
