#include "grid.h"
#include "utils.h"

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

void assign_entity_to_grid_cell(struct Grid *grid_p, int row, int col,
                                char entity) {
  grid_p->grid[row][col] = entity;
}

void blank_grid(struct Grid *grid_p) {
  for (int row = 0; row < GRID_SIZE - 1; row++) {
    for (int col = 0; col < GRID_SIZE - 1; col++) {
      if (row < 1 || col < 1 || row > GRID_SIZE - 3 || col > GRID_SIZE - 3) {
        grid_p->grid[row][col] = '#';
      } else {
        grid_p->grid[row][col] = '.';
      }
    }
    printf("\n");
  }
}

void draw(struct Grid *grid_p) {
  clear_screen();
  for (int row = 0; row < GRID_SIZE - 1; row++) {
    for (int col = 0; col < GRID_SIZE - 1; col++) {
      printf("%2c", grid_p->grid[row][col]);
    }
    printf("\n");
  }
  return;
}
