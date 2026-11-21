#ifndef MAP_MOVING_H
#define MAP_MOVING_H

#include "../vector.h"

unsigned char get_unit_reachable_tiles(unsigned char map_id, vector_u8b unit_position, 
    unsigned char unit_movement_range, vector_u8b *out);
    
#endif