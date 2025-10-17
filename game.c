#include "snake.h"

#include "inptlib.h"
#include "utils.h"
#include <stdio.h>

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

int main(void) {
  srand(time(NULL));
  enable_raw_mode();

  struct Grid grid = {.grid = {{'\0'}}};
  struct Grid *grid_p = &grid;

  struct Snake snake = {.direction = LEFT, .head = 0, .tail = 0, .length = 0};
  struct Snake *snake_p = &snake;

  clear_screen();
  blank_grid(grid_p);
  init_snake(snake_p, grid_p);

  char user_input;

  draw(grid_p);
  place_fruit(grid_p);
  hide_cursor();

  while (1) {
    user_input = get_input();

    struct Position old_tail = get_tail_pos(snake_p);

    if (snake_p->direction != UP && user_input == 's') {
      snake_p->direction = DOWN;
    }

    if (snake_p->direction != DOWN && user_input == 'w') {
      snake_p->direction = UP;
    }

    if (snake_p->direction != RIGHT && user_input == 'a') {
      snake_p->direction = LEFT;
    }

    if (snake_p->direction != LEFT && user_input == 'd') {
      snake_p->direction = RIGHT;
    }

    int move_result = move_snake(grid_p, snake_p);

    if (move_result == 1) {
      place_fruit(grid_p);
    }

    struct Position new_head = get_head_pos(snake_p);

    if (move_result == 0) {
      move_cursor(old_tail.row + 1, (old_tail.col * 2) + 2);
      printf(".");
    }
    move_cursor(new_head.row + 1, (new_head.col * 2) + 2);
    printf("@");
    fflush(stdout);

    delay(150);
  }

  show_cursor();
  disable_raw_mode();

  return 0;
}

void place_fruit(struct Grid *grid_p) {
  int fruit_row = rand_range(1, GRID_SIZE - 3);
  int fruit_col = rand_range(1, GRID_SIZE - 3);

  if (fruit_row == (GRID_SIZE - 2) / 2 && fruit_col == (GRID_SIZE - 2) / 2) {
    fruit_col++;
  }

  assign_entity_to_grid_cell(grid_p, fruit_row, fruit_col, 'o');

  move_cursor(fruit_row + 1, (fruit_col * 2) + 2);
  printf("o");
  fflush(stdout);

  return;
}
