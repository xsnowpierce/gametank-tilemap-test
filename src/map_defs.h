#ifndef MAP_DEFS_H
#define MAP_DEFS_H

#include "gt/gfx/sprites.h"
#include "vector.h"

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5
};

static unsigned char get_tile_from_point(unsigned char map_id, vector_u8b point);

static const char * get_tile_name_from_id(unsigned char map_id){
    switch(map_id){
        case 0:
            return "VOID";
        case 1:
            return "GRASS";
        case 2:
            return "DIRT";
        case 3:
            return "BUSH";
        case 4:
            return "TREE";
        case 5:
            return "WATER";
        default:
            return "NULL";
    }
}

const unsigned char* get_map_from_id(char map_id);

#endif