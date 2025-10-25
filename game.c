#include "grid.h"
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

struct Program_State {
  int run_process;
  int menu_active;
  int game_loop;
  int retry_active;
};

struct Game_Variables {
  int speed;
  int score;
};

void place_fruit(struct Grid *grid_p);
void menu_screen(char *user_input_p, struct Program_State *state_p);
void retry_screen(char *user_input_p, int score, struct Program_State *state_p);

int main(void) {
  struct Program_State state = {
      .run_process = 1, .menu_active = 1, .game_loop = 0, .retry_active = 0};

  char user_input;

  while (state.run_process) {
    menu_screen(&user_input, &state);

    srand(time(NULL));

    struct Game_Variables game_variables = {.speed = 250, .score = 0};

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

    while (state.game_loop) {
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
      new_head = get_head_pos(snake_p);

      if (move_result == 0) {
        if (grid_p->grid[old_tail.row][old_tail.col] != FRUIT_CELL) {
          move_cursor(old_tail.row + 1, (old_tail.col * 2) + 2);
          printf("%c", FLOOR_CELL);
        }
      }

      if (grid_p->grid[new_head.row][new_head.col] != FRUIT_CELL) {
        move_cursor(new_head.row + 1, (new_head.col * 2) + 2);
        printf("%c", SNAKE_CELL);
      }

      if (move_result == 1) {
        game_variables.score++;
        if (game_variables.speed >= 150) {
          game_variables.speed -= 5;
        }
        place_fruit(grid_p);
      }

      if (move_result == -1) {
        state.game_loop = 0;
        state.retry_active = 1;
      }

      fflush(stdout);
      delay(game_variables.speed);
    }

    clear_screen();
    show_cursor();
    disable_raw_mode();

    retry_screen(&user_input, game_variables.score, &state);

    clear_screen();
  }
  return 0;
}

void retry_screen(char *user_input_p, int score,
                  struct Program_State *state_p) {
  while (state_p->retry_active) {
    printf("Game Over\nYour Score was %d\n", score);
    printf("Retry?(y/n)\n\nChoice? ");

    *user_input_p = getchar();
    clear_input_buffer();

    if (*user_input_p == 'y') {
      state_p->game_loop = 1;
      state_p->retry_active = 0;

    } else if (*user_input_p == 'n') {
      state_p->menu_active = 1;
      state_p->game_loop = 0;
      state_p->retry_active = 0;

    } else {
      printf("\n\nInvalid input. Try again...\n\n");
    }
  }

  return;
}

void menu_screen(char *user_input_p, struct Program_State *state_p) {
  while (state_p->menu_active) {
    printf("Welcome to Snake\n(1)Start\n(2)Exit\n\nChoice? ");

    *user_input_p = getchar();
    clear_input_buffer();

    if (*user_input_p == '1') {
      state_p->menu_active = 0;
      state_p->game_loop = 1;

    } else if (*user_input_p == '2') {
      state_p->run_process = 0;
      state_p->menu_active = 0;
      state_p->game_loop = 0;

    } else {
      printf("\n\nInvalid input. Try again...\n\n");
    }
  }

  return;
}

void place_fruit(struct Grid *grid_p) {
  int fruit_row = rand_range(1, GRID_SIZE - 3);
  int fruit_col = rand_range(1, GRID_SIZE - 3);

  if (fruit_row == (GRID_SIZE - 2) / 2 && fruit_col == (GRID_SIZE - 2) / 2) {
    fruit_col++;
  }

  assign_entity_to_grid_cell(grid_p, fruit_row, fruit_col, FRUIT_CELL);
  move_cursor(fruit_row + 1, (fruit_col * 2) + 2);
  printf("%c", FRUIT_CELL);

  return;
}
