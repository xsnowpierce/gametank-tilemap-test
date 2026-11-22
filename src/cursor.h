#ifndef CURSOR_H
#define CURSOR_H

#include "vector.h"

extern unsigned char cursor_tile_position_x, cursor_tile_position_y;

void update_cursor();
void update_cursor_animation();
void cursor_update_free_movement();
void cursor_update_locked_movement(vector_u8b *moveable_tiles, unsigned char moveable_tile_count, vector_u8b unit_position);
void draw_cursor();
void draw_cursor_selecting();


#endif