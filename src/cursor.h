#ifndef CURSOR_H
#define CURSOR_H

#include "vector.h"


extern unsigned char cursor_tile_position_x, cursor_tile_position_y;

void initialize_cursor();
void update_cursor();
void draw_cursor();


#endif