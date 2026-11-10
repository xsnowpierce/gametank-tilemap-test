#include "map_drawing.h"
#include "MAP GENERATED_1.h"
#include "gen/assets/map.h"
#include "gt/gametank.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"
#include "gt/banking.h"
#include "gt/gfx/draw_direct.h"
#include "camera.h"


#define TILE_SIZE 8
#define TILES_PER_TILESET_ROW 16

SpriteSlot mapTileset;


void load_map(){
    mapTileset = allocate_sprite(&ASSET__map__maptileset_bmp_load_list);
}

void draw_map(unsigned char draw_tiles_x, unsigned char draw_tiles_y, unsigned char drawing_offset_x, unsigned char drawing_offset_y) {
    unsigned char row = 0, col, tile_id, tile;
    unsigned char x, y, source_x, source_y;
    unsigned char start_x, start_y;
    const unsigned char *map_row, *map_tile;

    start_x = (camera_x / TILE_SIZE) + drawing_offset_x;
    start_y = (camera_y / TILE_SIZE) + drawing_offset_y;

    map_row = layer_0_data + ((unsigned int)start_y * MAP_WIDTH) + start_x;

    x = (unsigned char)(drawing_offset_x * TILE_SIZE - (camera_x % TILE_SIZE));
    y = (unsigned char)(drawing_offset_y * TILE_SIZE - (camera_y % TILE_SIZE));

    direct_prepare_sprite_mode(mapTileset);
    direct_transparent_mode(0);

    push_rom_bank();
    change_rom_bank(ASSET__map__maptileset_bmp_bank);

    DIRECT_SET_WIDTH(TILE_SIZE);
    DIRECT_SET_HEIGHT(TILE_SIZE);

    while(row < draw_tiles_y){
        map_tile = map_row;
        col = 0;
        x = (unsigned char)(drawing_offset_x * TILE_SIZE
                  - (camera_x % TILE_SIZE));

        while(col < draw_tiles_x){
            tile_id = *map_tile++;

            if(tile_id != 0){
                tile = tile_id - 1;
                source_x = (tile % TILES_PER_TILESET_ROW) * TILE_SIZE;
                source_y = (tile / TILES_PER_TILESET_ROW) * TILE_SIZE;

                //await_drawing();

                DIRECT_SET_DEST_X(x);
                DIRECT_SET_DEST_Y(y);
                DIRECT_SET_SOURCE_X(source_x);
                DIRECT_SET_SOURCE_Y(source_y);
                DIRECT_DRAW_START();
            }

            ++col;
            x += TILE_SIZE;
        }

        ++row;
        y += TILE_SIZE;
        map_row += MAP_WIDTH;
    }

    await_drawing();
    pop_rom_bank();
}
