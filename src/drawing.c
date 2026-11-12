#include "drawing.h"
#include "gen/assets/map.h"
#include "gt/banking.h"
#include "gt/gametank.h"
#include "gt/gfx/draw_direct.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"

SpriteSlot tilesetSlot;

#define TILE_SIZE 8
#define GRAM_BANK_WIDTH 128
#define TILES_PER_ROW (GRAM_BANK_WIDTH / TILE_SIZE)

unsigned char screen_tile_count;

enum TILE {
    GRASS = 0, DIRT = 1, BUSH = 2, TREE = 3
};

// TODO add a proper doc header to this so I remember hwo to use it
void draw_tile_into_gram(unsigned char tile_x, unsigned char tile_y, SpriteSlot source_sprite_slot, unsigned char tile_id, unsigned char target_bank) {
    unsigned char i, j, tile_pixels[TILE_SIZE * TILE_SIZE];

    unsigned int source_x = (tile_id % TILES_PER_ROW) * TILE_SIZE, source_y = (tile_id / TILES_PER_ROW) * TILE_SIZE;
    unsigned int target_x = tile_x * TILE_SIZE, target_y = tile_y * TILE_SIZE;

    // Grab the sprite we are targetting and store it in tile_pixels. 
    // I'm nmot sure if changing the bank all the time is good so lets just grab the entire tile
    // in one go and then draw it afterwards
    direct_prepare_sprite_ram_array_mode(source_sprite_slot);
    for (i = 0; i < TILE_SIZE; ++i) {
        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[(i * TILE_SIZE) + j] = vram[((source_y + i) << 7) + (source_x + j)];
        }
    }

    // Now take the pixel array of the last step and draw it at the target destination
    direct_prepare_sprite_ram_array_mode(target_bank);
    for (i = 0; i < TILE_SIZE; ++i) {
        for (j = 0; j < TILE_SIZE; ++j) {
            vram[((target_y + i) << 7) + (target_x + j)] = tile_pixels[(i * TILE_SIZE) + j];
        }
    }
}

void load_drawing(){
    unsigned char i, j, t = 0;

    tilesetSlot = allocate_sprite(&ASSET__map__maptileset_bmp_load_list);
    
    for (i = 0; i < 16; ++i) {
        for (j = 0; j < 16; ++j) {
            draw_tile_into_gram(j, i, tilesetSlot, GRASS, QUADRANT_3 | 0);
        }
    }
    
    free_sprite(tilesetSlot);
    //clear_spritebank(tilemapSpriteRamBank);
}


void draw(){
}