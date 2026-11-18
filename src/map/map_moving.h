#ifndef MAP_MOVING_H
#define MAP_MOVING_H

#include "../vector.h"

void find_reachable_tiles(unsigned char map_id, vector_u8b start, unsigned char max_steps);
unsigned int get_reachable_tiles(vector_u8b *out_tiles);

#endif