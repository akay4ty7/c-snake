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
void game_over();

int main(void) {
  int run_process = 1;
  int menu_active = 1;
  int game_loop = 0;
  int retry_active = 0;

  char user_input;

  while (run_process) {
    while (menu_active) {
      printf("Welcome to Snake\n(1)Start\n(2)Exit\n");

      user_input = getchar();
      while (getchar() != '\n') {
      }

      if (user_input == '1') {
        menu_active = 0;
        game_loop = 1;

      } else if (user_input == '2') {
        run_process = 0;
        menu_active = 0;
        game_loop = 0;

      } else {
        printf("Invalid Input\nTry Again\n\n");
      }
    }
    clear_screen();

    // game start
    srand(time(NULL));

    struct Grid grid = {.grid = {{'\0'}}};
    struct Grid *grid_p = &grid;

    struct Snake snake = {.direction = LEFT, .head = 0, .tail = 0, .length = 0};
    struct Snake *snake_p = &snake;

    struct Position old_tail = {.row = 0, .col = 0};
    struct Position new_head = {.row = 0, .col = 0};

    int move_result = 0;

    enable_raw_mode();

    clear_screen();
    blank_grid(grid_p);
    init_snake(snake_p, grid_p);

    draw_grid(grid_p);
    place_fruit(grid_p);
    hide_cursor();

    while (game_loop) {
      user_input = get_input();
      old_tail = get_tail_pos(snake_p);

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

      move_result = move_snake(grid_p, snake_p);

      if (move_result == 1) {
        place_fruit(grid_p);
      }

      if (move_result == 0) {
        move_cursor(old_tail.row + 1, (old_tail.col * 2) + 2);
        printf(".");
      }

      new_head = get_head_pos(snake_p);
      move_cursor(new_head.row + 1, (new_head.col * 2) + 2);
      printf("@");

      if (move_result == -1) {
        game_loop = 0;
        retry_active = 1;
      }

      fflush(stdout);
      delay(150);
    }
    clear_screen();

    fflush(stdout);
    show_cursor();
    disable_raw_mode();

    while (retry_active) {

      game_over();
      printf("Retry?(y/n)\n");

      user_input = getchar();
      while (getchar() != '\n') {
      }

      if (user_input == 'y') {
        game_loop = 1;
        retry_active = 0;

      } else if (user_input == 'n') {
        menu_active = 1;
        game_loop = 0;
        retry_active = 0;

      } else {
        printf("Invalid input\nPlease enter a valid input\n");
      }
    }
  }
  return 0;
}

void game_over() {
  printf("Game Over\n");
  return;
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
