#ifndef MAP_DEFS_H
#define MAP_DEFS_H

#include "../gt/gfx/sprites.h"
#include "../vector.h"

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5,
    TILE_TALL_GRASS = 6, TILE_FLOWER_GRASS = 7
};

const unsigned char* get_map_from_id(unsigned char map_id);

enum TILE get_tile_from_point(unsigned char map_id, vector_u8b point);

static const char * get_tile_name_from_id(enum TILE tile_id){
    switch(tile_id){
        case TILE_BLACK:
            return "VOID";
        case TILE_GRASS:
            return "GRASS";
        case TILE_DIRT:
            return "DIRT";
        case TILE_BUSH:
            return "BUSH";
        case TILE_TREE:
            return "TREE";
        case TILE_WATER:
            return "WATER";
        case TILE_TALL_GRASS:
            return "GRASS";
        case TILE_FLOWER_GRASS:
            return "GRASS";
        default:
            return "NULL";
    }
}

static const unsigned char get_tile_is_passable(enum TILE tile_id){
    switch(tile_id){
        case TILE_BLACK:
            return 0;
        case TILE_TREE:
            return 0;
        default:
            return 1;
    }
}



#endif