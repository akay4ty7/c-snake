#include "snake.h"
#include "grid.h"

void add_new_head(struct Snake *snake_p, int row, int col) {
  snake_p->head = (snake_p->head + 1) % (GRID_SIZE * GRID_SIZE);
  snake_p->segments[snake_p->head].row = row;
  snake_p->segments[snake_p->head].col = col;
  snake_p->length++;

  return;
}

void init_snake(struct Snake *snake_p, struct Grid *grid_p) {
  int start_row = (GRID_SIZE - 2) / 2;
  int start_col = (GRID_SIZE - 2) / 2;

  init_snake_circular(snake_p, grid_p, start_row, start_col);
}

void init_snake_circular(struct Snake *snake_p, struct Grid *grid_p,
                         int start_row, int start_col) {
  snake_p->head = 0;
  snake_p->tail = 0;
  snake_p->length = 1;

  snake_p->segments[0].row = start_row;
  snake_p->segments[0].col = start_col;

  assign_entity_to_grid_cell(grid_p, start_row, start_col, '@');

  return;
}

struct Position get_head_pos(struct Snake *snake_p) {
  return snake_p->segments[snake_p->head];
}

struct Position get_tail_pos(struct Snake *snake_p) {
  return snake_p->segments[snake_p->tail];
}

void remove_tail(struct Snake *snake_p) {
  snake_p->tail = (snake_p->tail + 1) % (GRID_SIZE * GRID_SIZE);
  snake_p->length--;
  return;
}

int move_snake(struct Grid *grid_p, struct Snake *snake_p) {
  struct Position current_head = get_head_pos(snake_p);

  int ate_fruit = 0;
  int new_row = current_head.row;
  int new_col = current_head.col;

  switch (snake_p->direction) {
  case UP:
    if (new_row > 1) {
      new_row--;
    }
    break;
  case DOWN:
    if (new_row < GRID_SIZE - 3) {
      new_row++;
    }
    break;
  case LEFT:
    if (new_col > 1) {
      new_col--;
    }
    break;
  case RIGHT:
    if (new_col < GRID_SIZE - 3) {
      new_col++;
    }
    break;
  default:
    break;
  }

  // Check if position actually changed
  if (new_row == current_head.row && new_col == current_head.col) {
    return -1;
  }

  if (grid_p->grid[new_row][new_col] == 'o') {
    ate_fruit = 1;
  }

  add_new_head(snake_p, new_row, new_col);

  if (!ate_fruit) {
    remove_tail(snake_p);
  }

  assign_entity_to_grid_cell(grid_p, new_row, new_col, '@');

  return ate_fruit;
}
