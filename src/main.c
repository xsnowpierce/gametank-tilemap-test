#include "cursor.h"
#include "gen/assets/player.h"
#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"

#include "map/map_drawing.h"
#include "gt/input.h"
#include "units.h"

#include "state_logic/game_state.h"

Unit unit_bank[MAX_UNIT_COUNT] = {
    {SWORDSMAN, "JAMERO", { 1, 1, 1 }, {8, 8}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {10, 8}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {11, 8}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {10, 9}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {10, 10}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {10, 12}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {15, 8}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {14, 10}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {17, 17}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {16, 17}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {18, 19}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {19, 20}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {16, 20}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {11, 11}, 0, 1},
    {MAGE, "CRAS", {1,1,1}, {12, 12}, 0, 1}
};

void start_game(){
    SpriteSlot playerSpriteSlot;

    init_graphics();

    playerSpriteSlot = allocate_sprite(&ASSET__player__player_bmp_load_list);

    initialize_cursor(&playerSpriteSlot);
    set_unit_spritesheet(&playerSpriteSlot);
    load_units_into_array(unit_bank);

    do_ram_loading();
    game_load_map(0);

    change_game_state(CURSOR_MOVEMENT);
}

void start(){
    start_game();
}

void update(){
    update_inputs();
    update_game_state(currentGameState);
}


void draw(){
    // all things here should call await_drawing() themselves.
    draw_level_map();
    draw_game_state(currentGameState);
}

void queued_draw(){
    queue_draw_game_state(currentGameState);
    queue_clear_border(0);
}


int main () {
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