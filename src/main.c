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

SpriteSlot playerSpriteSlot;

Unit unit_bank[MAX_UNIT_COUNT] = {
    {SWORDSMAN, {8, 8}, 0, 1},
    {MAGE, {10, 8}, 0, 1}
};

void start(){
    init_graphics();

    playerSpriteSlot = allocate_sprite(&ASSET__player__player_bmp_load_list);

    initialize_cursor(&playerSpriteSlot);
    set_unit_spritesheet(&playerSpriteSlot);
    load_units_into_array(unit_bank);

    initialize_ui();

    load_map_into_gram(&level_01);
}

void update(){
    update_inputs();

    update_camera();
    update_cursor();

    update_unit_animation();
    update_unit_cache();

    update_ui();
}


void draw(){
    draw_level_map();
    draw_cursor();
    draw_visible_units();
    draw_ui();
    //ui_draw_hovered_tile(&level_01);
    //draw_camera_and_cursor_position();
}


int main () {
    start();
    
    while (1) {
        queue_clear_screen(3);
        
        update();

        draw();
        
        queue_clear_border(0);
        await_draw_queue();
        await_vsync(1);
        flip_pages(); 
    }
    return 0;
}