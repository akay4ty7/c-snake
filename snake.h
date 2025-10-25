#include "grid.h"
#include "inptlib.h"

#ifndef SNAKE_H
#define SNAKE_H

#define SNAKE_CELL '@'

struct Position {
  int row;
  int col;
};

struct Snake {
  enum Input direction;
  struct Position segments[GRID_SIZE * GRID_SIZE];
  int head;
  int tail;
  int length;
};

void init_snake(struct Snake *snake_p, struct Grid *grid_p);
void init_snake_circular(struct Snake *snake_p, struct Grid *grid_p,
                         int start_row, int start_col);
struct Position get_head_pos(struct Snake *snake_p);
struct Position get_tail_pos(struct Snake *snake_p);
void add_new_head(struct Snake *snake_p, int row, int col);
void remove_tail(struct Snake *snake_p);
int move_snake(struct Grid *grid_p, struct Snake *snake_p);
#endif
