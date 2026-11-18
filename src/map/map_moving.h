#ifndef MAP_MOVING_H
#define MAP_MOVING_H

#include "../vector.h"

vector_u8b get_unit_reachable_tiles(unsigned char map_id, vector_u8b unit_position, unsigned char unit_movement_range);

#endif