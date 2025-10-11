
// TODO: Create Data structure for grid and display grid in terminal.
// Create data structure
// Print onto screen

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 10
struct Grid {
  char grid[GRID_SIZE][GRID_SIZE];
};

// UTILITY Func
void clear_screen(void);
int rand_range(int min, int max);

// Game Func
void place_fruit(struct Grid *grid_pointer);
void init_player(struct Grid *grid_pointer);

// GRID Func
void blank_grid(struct Grid *grid_pointer);
void assign_entity_to_grid_cell(struct Grid *grid_pointer, int row, int col,
                                char entity);
void draw(struct Grid *grid_pointer);

int main(void) {
  srand(time(NULL));
  int game_loop = 1;
  struct Grid grid = {.grid = {'\0'}};
  struct Grid *grid_pointer = &grid;

  blank_grid(grid_pointer);

  init_player(grid_pointer);
  place_fruit(grid_pointer);

  draw(grid_pointer);

  while (game_loop) {
    // Continue here
  }

  return 0;
}

int rand_range(int min, int max) { return rand() % (max - min + 1) + min; }

void assign_entity_to_grid_cell(struct Grid *grid_pointer, int row, int col,
                                char entity) {
  grid_pointer->grid[row][col] = entity;
}

void place_fruit(struct Grid *grid_pointer) {
  int fruit_row = rand_range(1, GRID_SIZE - 3);
  int fruit_col = rand_range(1, GRID_SIZE - 3);

  if (fruit_row == (GRID_SIZE - 2) / 2 && fruit_col == (GRID_SIZE - 2) / 2) {
    fruit_col++;
  }
  assign_entity_to_grid_cell(grid_pointer, fruit_row, fruit_col, 'o');
}

void init_player(struct Grid *grid_pointer) {
  assign_entity_to_grid_cell(grid_pointer, (GRID_SIZE - 2) / 2,
                             (GRID_SIZE - 2) / 2, '@');
}

void blank_grid(struct Grid *grid_pointer) {
  for (int row = 0; row < GRID_SIZE - 1; row++) {
    for (int col = 0; col < GRID_SIZE - 1; col++) {
      if (row < 1 || col < 1 || row > GRID_SIZE - 3 || col > GRID_SIZE - 3) {
        grid_pointer->grid[row][col] = '#';
      } else {
        grid_pointer->grid[row][col] = '.';
      }
    }
    printf("\n");
  }
}

void clear_screen(void) {
  // ANSI encoding for clear
  printf("\033[H\033[2J");
}

void draw(struct Grid *grid_pointer) {

  clear_screen();

  for (int row = 0; row < GRID_SIZE - 1; row++) {
    for (int col = 0; col < GRID_SIZE - 1; col++) {
      printf("%2c", grid_pointer->grid[row][col]);
    }
    printf("\n");
  }
  return;
}
