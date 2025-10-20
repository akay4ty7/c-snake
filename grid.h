#ifndef GRID_H
#define GRID_H

#define GRID_SIZE 20

struct Grid {
  char grid[GRID_SIZE][GRID_SIZE];
};

void blank_grid(struct Grid *grid_p);
void assign_entity_to_grid_cell(struct Grid *grid_p, int row, int col,
                                char entity);
void draw_grid(struct Grid *grid_p);
#endif
