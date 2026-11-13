#include "drawing.h"
#include "gen/assets/tileset.h"
#include "gt/banking.h"
#include "gt/gametank.h"
#include "gt/gfx/draw_direct.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"
#include "gt/gfx/draw_queue.h"
#include "map.h"

int load_map_into_gram(MapLevel *maplevel);
void load_drawing();
void draw_tile_into_gram(unsigned char tile_x, unsigned char tile_y, SpriteSlot source_sprite_slot, unsigned char tile_id, unsigned char target_bank);
void draw();

#define TILE_SIZE 8
#define GRAM_BANK_WIDTH 128
#define TILES_PER_ROW (GRAM_BANK_WIDTH / TILE_SIZE)

int load_map_into_gram(MapLevel *maplevel){
    unsigned int chunk_x, chunk_y;
    unsigned int map_x, map_y;
    unsigned int source_index;
    unsigned int chunks_across;
    unsigned char x, y;
    unsigned char current_rom_bank;
    
    SpriteSlot currentTileset = allocate_sprite(maplevel->tilesetPage);

    chunks_across = (maplevel->MAP_WIDTH + TILES_PER_ROW - 1) / TILES_PER_ROW;

    // disable interrupts before we do the heavy function
    __asm__("SEI");

    // load the map now
    for (chunk_y = 0; chunk_y < maplevel->MAP_HEIGHT; chunk_y += TILES_PER_ROW) {
        for (chunk_x = 0; chunk_x < maplevel->MAP_WIDTH; chunk_x += TILES_PER_ROW) {

            current_rom_bank = (chunk_y / TILES_PER_ROW) * chunks_across + (chunk_x / TILES_PER_ROW);

            for (y = 0; y < TILES_PER_ROW; ++y) {
                map_y = chunk_y + y;
                if (map_y >= maplevel->MAP_HEIGHT) {
                    break;
                }

                for (x = 0; x < TILES_PER_ROW; ++x) {
                    map_x = chunk_x + x;
                    if (map_x >= maplevel->MAP_WIDTH) {
                        break;
                    }

                    source_index = map_y * maplevel->MAP_WIDTH + map_x;

                    draw_tile_into_gram(x,y,currentTileset,maplevel->TILE_DATA[source_index] - 1,QUADRANT_3 | current_rom_bank);
                }
            }
        }
    }

    __asm__("CLI"); // re-enable interrupts since we are now finished


    return 0;
}

void draw_tile_into_gram(unsigned char tile_x, unsigned char tile_y, SpriteSlot source_sprite_slot, unsigned char tile_id, unsigned char target_bank) {
    unsigned char i, j, tile_pixels[TILE_SIZE * TILE_SIZE];
    unsigned int source_x = (tile_id % TILES_PER_ROW) * TILE_SIZE, source_y = (tile_id / TILES_PER_ROW) * TILE_SIZE;
    unsigned int target_x = tile_x * TILE_SIZE, target_y = tile_y * TILE_SIZE;

    // Grab the sprite we are targetting and store it in tile_pixels.
    // I'm nmot sure if changing the bank all the time is good so lets just grab the entire tile
    // in one go and then draw it afterwards

    direct_prepare_sprite_ram_array_mode(source_sprite_slot);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int source_row = ((source_y + i) << 7) + source_x;
        unsigned int tile_row = i * TILE_SIZE;

        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[tile_row + j] = vram[source_row + j];
        }
    }

    // Now take the pixel array of the last step and draw it at the target destination
    direct_prepare_sprite_ram_array_mode(target_bank);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int target_row = ((target_y + i) << 7) + target_x;
        unsigned int tile_row = i * TILE_SIZE;

        for (j = 0; j < TILE_SIZE; ++j) {
            vram[target_row + j] = tile_pixels[tile_row + j];
        }
    }
}



void draw(){
}