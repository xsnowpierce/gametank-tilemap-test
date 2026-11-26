#ifndef MAP_MOVING_H
#define MAP_MOVING_H

#include "../units.h"
#include "../vector.h"

#define MAP_WIDTH 32
#define MAP_HEIGHT 32
#define NODE_COUNT (MOVE_WINDOW_WIDTH * MOVE_WINDOW_HEIGHT)

// choosing 17 here because 8x8, but have to add one cause of
// the centre that the unit starts from
#define MOVE_WINDOW_WIDTH 17
#define MOVE_WINDOW_HEIGHT 17

// we can technically have 255 tiles, but its unlikely.
// so we will set the max value to be the dummy value
#define UNVISITED_TILE_ID 255
// same with this
#define NO_PARENT 0xFFFFu

#define UNIT_MOVE_LIMIT 8

void calculate_reachable_tiles(unsigned char map_id, vector_u8b unit_start_position, 
    unsigned char movement_range);

unsigned char get_unit_path_to_tile(unsigned char map_id, vector_u8b unit_position, vector_u8b destination,
    unsigned char unit_movement_range, vector_u8b *out_path);

// checks whether a unit is on the given tile.
// Returns with 0 if there are none. Returns with 1 or 2 if there is, and the given team ID
// of the unit.
unsigned char is_unit_on_tile(vector_u8b tile_position, Unit *unit_array);

extern vector_u8b current_reachable_tiles[NODE_COUNT];
extern unsigned char current_reachable_tiles_count;

#endif