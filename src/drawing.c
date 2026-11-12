#include "drawing.h"
#include "gen/assets/map.h"
#include "gt/banking.h"
#include "gt/gametank.h"
#include "gt/gfx/draw_direct.h"
#include "gt/gfx/sprites.h"

SpriteSlot tilesetSlot;

#define TILE_SIZE 9
#define WINDOW_SIZE_MAX_X 128
#define WINDOW_SIZE_MAX_Y 100
#define DRAWING_START_X 9
#define DRAWING_START_Y 16

unsigned char screen_tile_count;

void load_drawing(){
    tilesetSlot = allocate_sprite(&ASSET__map__maptileset_bmp_load_list);
    screen_tile_count = (WINDOW_SIZE_MAX_X / TILE_SIZE) * (WINDOW_SIZE_MAX_Y / TILE_SIZE);
}

void draw(){
    static unsigned char x, y, i, t;
    direct_prepare_sprite_mode(tilesetSlot);
    direct_transparent_mode(false);
    push_rom_bank();
    change_rom_bank(ASSET__map__maptileset_bmp_bank);
 
    x = DRAWING_START_X;
    y = DRAWING_START_Y;
    i = 0;
    t = 0;
    DIRECT_SET_DEST_Y(0);
    DIRECT_SET_WIDTH(TILE_SIZE);
    DIRECT_SET_HEIGHT(TILE_SIZE);
    while(i < screen_tile_count) {
        if(i & 1){
            t = 0;
        }else{
            t = 1;
        }
        await_drawing();
        DIRECT_SET_DEST_X(x);
        DIRECT_SET_SOURCE_X(t * TILE_SIZE);
        DIRECT_SET_SOURCE_Y(0);
        DIRECT_DRAW_START();
        ++i;
        x += TILE_SIZE;
        if(x >= WINDOW_SIZE_MAX_X) {
            x = DRAWING_START_X;
            y += TILE_SIZE;
            DIRECT_SET_DEST_Y(y); //Incidentally, VY, GY, and Height are safe to set while a blit is still running.
        }
    }
    await_drawing();
 
    pop_rom_bank();
}