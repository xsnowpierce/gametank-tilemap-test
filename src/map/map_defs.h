#ifndef MAP_DEFS_H
#define MAP_DEFS_H

#include "../gt/gfx/sprites.h"
#include "../vector.h"

#define MAP_MAX_TILE_SIZE 1024
#define MAP_WIDTH 32
#define MAP_HEIGHT 32

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5,
    TILE_TALL_GRASS = 6, TILE_FLOWER_GRASS = 7, TILE_MOUNTAIN = 8
};

const unsigned char* get_map_from_id(unsigned char map_id);

enum TILE get_tile_from_point(unsigned char map_id, vector_u8b point);

const char * get_tile_name_from_id(enum TILE tile_id);

unsigned char get_tile_is_passable(enum TILE tile_id);

#endif