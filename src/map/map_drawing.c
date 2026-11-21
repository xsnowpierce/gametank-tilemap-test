#include "map_drawing.h"
#include "../camera.h"
#include "../gen/assets/tileset.h"
#include "../gt/gametank.h"
#include "../gt/gfx/draw_direct.h"
#include "../gt/gfx/gfx_sys.h"
#include "../gt/gfx/sprites.h"
#include "../gt/gfx/draw_queue.h"
#include "map_defs.h"
#include "../gt/banking.h"
#include "../gen/bank_nums.h"
#include "map_sprite_animation.h"

int load_map_into_gram(unsigned char map_id);
void load_drawing();
void draw_tile_into_gram(unsigned char tile_x, unsigned char tile_y, unsigned char tile_id, unsigned char target_bank);
void draw();

#define TILE_SIZE 8
#define GRAM_BANK_WIDTH 128
#define TILES_PER_ROW (GRAM_BANK_WIDTH / TILE_SIZE)
#define MAP_RAM_BANK 7
#define MAP_WIDTH 32
#define MAP_HEIGHT 32

SpriteSlot currentTileset;
const unsigned char *target_map_level;

int load_map_id(unsigned char map_id){
    push_rom_bank();
    change_rom_bank(BANK_PROG0);

    load_map_into_gram(map_id);

    pop_rom_bank();
}

#pragma code-name (push, "PROG0")
int load_map_into_gram(unsigned char map_id){
    unsigned int chunk_x, chunk_y;
    unsigned int map_x, map_y;
    unsigned int source_index;
    unsigned char x, y;
    unsigned char current_quadrant = QUADRANT_3;
    
    currentTileset = allocate_sprite(&ASSET__tileset__tileset_bmp_load_list);

    // disable interrupts before we do the heavy function
    __asm__("SEI");

    target_map_level = get_map_from_id(map_id);
    // load the map now
    for (chunk_y = 0; chunk_y < MAP_HEIGHT; chunk_y += TILES_PER_ROW) {
        for (chunk_x = 0; chunk_x < MAP_WIDTH; chunk_x += TILES_PER_ROW) {

            // current_ram_bank = (chunk_y / TILES_PER_ROW) * chunks_across + (chunk_x / TILES_PER_ROW);

            for (y = 0; y < TILES_PER_ROW; ++y) {
                map_y = chunk_y + y;
                if (map_y >= MAP_HEIGHT) {
                    break;
                }

                for (x = 0; x < TILES_PER_ROW; ++x) {
                    map_x = chunk_x + x;
                    if (map_x >= MAP_WIDTH) {
                        break;
                    }

                    source_index = (map_y << 5) + map_x;

                    draw_tile_into_gram(x,y, target_map_level[source_index] ,current_quadrant);
                }
            }
            current_quadrant -= QUADRANT_1;
        }
        
    }

    __asm__("CLI"); // re-enable interrupts since we are now finished

    return 0;
}
#pragma code-name (pop)


#pragma code-name (push, "PROG0")
void draw_tile_into_gram(unsigned char tile_x, unsigned char tile_y, unsigned char tile_id, unsigned char target_quadrant) {
    static const unsigned char banks[] = { 7, 6, 5 };
    unsigned char b, i, j, tile_pixels[TILE_SIZE << 3];
    unsigned int source_x = (tile_id % TILES_PER_ROW) << 3, source_y = (tile_id >> 3) << 3;
    unsigned int target_x = tile_x << 3, target_y = tile_y << 3;

    // Grab the sprite we are targetting and store it in tile_pixels.
    // I'm nmot sure if changing the bank all the time is good so lets just grab the entire tile
    // in one go and then draw it afterwards
    //PROFILER_START(1);
    direct_prepare_sprite_ram_array_mode(currentTileset);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int source_row = ((source_y + i) << 7) + source_x;
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[tile_row + j] = vram[source_row + j];
        }
    }
    //PROFILER_END(1);
    //PROFILER_START(2);
    // Now take the pixel array of the last step and draw it at the target destination
    

    for (b = 0; b < sizeof banks; ++b) {
        direct_prepare_sprite_ram_array_mode(target_quadrant | banks[b]);

        for (i = 0; i < TILE_SIZE; ++i) {
            unsigned int target_row = ((target_y + i) << 7) + target_x;
            unsigned int tile_row = i << 3;

            for (j = 0; j < TILE_SIZE; ++j) {
                vram[target_row + j] = tile_pixels[tile_row + j];
            }
        }
    }
}
#pragma code-name (pop)

#pragma code-name(push, "PROG0")
void redraw_tile(unsigned char tile_x, unsigned char tile_y, unsigned char target_quadrant){
    draw_tile_into_gram(tile_x, tile_y, target_map_level[(tile_x << 5) + tile_y], target_quadrant);
}
#pragma code-name (pop)

void draw_level_map(){
    direct_prepare_sprite_mode(QUADRANT_0 | current_animated_bank);
    DIRECT_DRAW_SPRITE(0, 0, 127, 127, 128 + camera_x, 128 + camera_y);
    await_drawing();
}