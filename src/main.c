#include "gen/assets/player.h"
#include "gt/gametank.h"
#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"
#include "gt/input.h"
#include "map_data.h"
#include "map_drawing.h"
#include "map_defs.h"
#include "cursor.h"
#include "ui.h"
#include "units.h"
#include "camera.h"
#include "gt/feature/text/text.h"


enum GAME_PROGRESSION_POINT {
    CURSOR_MOVEMENT, SELECTING_UNIT
};

SpriteSlot playerSpriteSlot;
enum GAME_PROGRESSION_POINT currentPoint;

Unit unit_bank[MAX_UNIT_COUNT] = {
    {SWORDSMAN, { 1, 1, 1 }, {8, 8}, 0, 1},
    {MAGE, {1,1,1}, {10, 8}, 0, 1}
};

void start(){
    init_graphics();

    playerSpriteSlot = allocate_sprite(&ASSET__player__player_bmp_load_list);

    initialize_cursor(&playerSpriteSlot);
    set_unit_spritesheet(&playerSpriteSlot);
    load_units_into_array(unit_bank);

    initialize_ui();

    load_map_into_gram(&level_01);
    currentPoint = CURSOR_MOVEMENT;
}

void update(){
    update_inputs();

    switch(currentPoint){
        case CURSOR_MOVEMENT:
            update_camera();
            update_cursor();
            update_unit_animation();
            update_unit_cache();
            update_ui();
            
            break;
    }
    
}


void draw(){

    // all things here should call await_drawing() themselves.

    draw_level_map();

    switch(currentPoint){
        case CURSOR_MOVEMENT:
            ui_draw_hovered_tile(&level_01);
            break;
    }
}

void queued_draw(){

    // NONE of these should call await_draw_queue.

    switch(currentPoint){
        case CURSOR_MOVEMENT:
            draw_cursor();
            draw_visible_units();
            draw_ui();
    }

    queue_clear_border(0);
}


int main () {
    text_init();
    text_load_font();

    start();
    
    while (1) {
        update();
        
        queue_clear_screen(3);
        await_draw_queue();

        draw();

        queued_draw();
        await_draw_queue();

        await_vsync(1);
        flip_pages(); 
    }
    return 0;
}