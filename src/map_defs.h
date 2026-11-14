#ifndef MAP_DEFS_H
#define MAP_DEFS_H

#include "gt/gfx/sprites.h"
#include "vector.h"

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5
};

typedef struct {
    const SpritePage *tilesetPage;
    const unsigned char MAP_WIDTH, MAP_HEIGHT;
    const unsigned char *TILE_DATA;
} MapLevel;

static unsigned char get_tile_from_point(MapLevel *level, vector_u8b point){
    
    return level->TILE_DATA[point.y * level->MAP_WIDTH + point.x];
}

static const char * get_tile_name_from_id(unsigned char id){
    switch(id){
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

#endif