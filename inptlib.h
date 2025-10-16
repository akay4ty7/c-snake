#ifndef INPTLIB_H
#define INPTLIB_H

enum Input { UP, DOWN, LEFT, RIGHT };

void enable_raw_mode(void);
void disable_raw_mode(void);

char get_input(void);

#endif
