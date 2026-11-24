#ifndef MAP_MOVING_H
#define MAP_MOVING_H

#include "../vector.h"

unsigned int get_unit_reachable_tiles(unsigned char map_id, vector_u8b unit_position, 
    unsigned char unit_movement_range, vector_u8b *out);

unsigned char get_unit_path_to_tile(unsigned char map_id, vector_u8b unit_position, vector_u8b destination,
    unsigned char unit_movement_range, vector_u8b *out_path);
#endif