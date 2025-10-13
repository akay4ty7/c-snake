#include "snake.h"

#include "utils.h"

#ifndef BOOL_H
#define BOOL_H
#include <stdbool.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

// Game Func
void place_fruit(struct Grid *grid_p);
void init_snake(struct Grid *grid_p, int (*s_segment_p)[GRID_SIZE * GRID_SIZE]);

int main(void) {
  srand(time(NULL));

  struct Grid grid = {.grid = {{'\0'}}};
  struct Grid *grid_p = &grid;

  struct Snake snake = {.segment = {{0}}, .direction = LEFT};
  int (*s_segment_p)[GRID_SIZE * GRID_SIZE] = snake.segment;
  enum Input *s_direction_p = &snake.direction;

  blank_grid(grid_p);
  init_snake(grid_p, s_segment_p);
  place_fruit(grid_p);
  draw(grid_p);

  while (true) {
    delay(150);
    move_snake(grid_p, s_segment_p, s_direction_p);
    draw(grid_p);
  }

  return 0;
}

void place_fruit(struct Grid *grid_p) {
  int fruit_row = rand_range(1, GRID_SIZE - 3);
  int fruit_col = rand_range(1, GRID_SIZE - 3);

  if (fruit_row == (GRID_SIZE - 2) / 2 && fruit_col == (GRID_SIZE - 2) / 2) {
    fruit_col++;
  }

  assign_entity_to_grid_cell(grid_p, fruit_row, fruit_col, 'o');
}

void init_snake(struct Grid *grid_p,
                int (*s_segment_p)[GRID_SIZE * GRID_SIZE]) {
  s_segment_p[0][0] = (GRID_SIZE - 2) / 2;
  s_segment_p[1][0] = (GRID_SIZE - 2) / 2;

  assign_entity_to_grid_cell(grid_p, s_segment_p[0][0], s_segment_p[1][0], '@');
}
