#ifndef MAP_H
#define MAP_H

#include "gt/gfx/sprites.h"
#include <unistd.h>

enum TILE {
    TILE_BLACK = 0, TILE_GRASS = 1, TILE_DIRT = 2, TILE_BUSH = 3, TILE_TREE = 4, TILE_WATER = 5
};

typedef struct {
    const SpritePage *tilesetPage;
    const unsigned char MAP_WIDTH, MAP_HEIGHT;
    const unsigned char *TILE_DATA;
} MapLevel;

MapLevel get_map_level(char map_id);

static int map_is_legal(MapLevel level);

#endif