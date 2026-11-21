#ifndef MAP_TILE_HELPER_H
#define MAP_TILE_HELPER_H

#include "../vector.h"
#include "../units.h"

void redraw_tile_in_sram(vector_u8b tile_position, unsigned char target_quadrant);
void redraw_unit_in_sram(Unit *unit);

#endif