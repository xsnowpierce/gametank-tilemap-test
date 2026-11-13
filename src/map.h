#ifndef MAP_H
#define MAP_H

#include "gt/gfx/sprites.h"

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5
};

typedef struct {
    const SpritePage *tilesetPage;
    const unsigned char MAP_WIDTH, MAP_HEIGHT;
    const unsigned char *TILE_DATA;
} MapLevel;

extern MapLevel level_01;

#endif