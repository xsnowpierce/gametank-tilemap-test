#include "cursor.h"
#include "gen/assets/player.h"
#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/gfx/sprites.h"

#include "map/map_drawing.h"
#include "gt/input.h"
#include "units.h"

#include "state_logic/game_state.h"

SpriteSlot playerSpriteSlot;

#define SPRITE_BANK_POSITION QUADRANT_0 | 0

void start_game(){
    init_graphics();
    
    playerSpriteSlot = allocate_sprite(&ASSET__player__player_bmp_load_list);

    // hard coding the bank position so no weird stuff happens
    initialize_cursor(SPRITE_BANK_POSITION);
    set_unit_spriteBank(SPRITE_BANK_POSITION);
    
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