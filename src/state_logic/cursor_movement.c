#include "cursor_movement.h"

#include "../cursor.h"
#include "game_state.h"
#include "../units.h"
#include "../camera.h"
#include "../gt/input.h"
#include "../map/map_sprite_animation.h"

void initialize_state_cursor_movement(){

}

void update_state_cursor_movement(){
    unsigned char i;

    if(player1_buttons & INPUT_MASK_A){
        // player pressed A, check if there is a unit on this tile
        // if there is, keep track of the unit, and change current game state

        for(i = 0; i < MAX_UNIT_COUNT; ++i){
            if(unit_array[i].tile_position.x == cursor_tile_position_x && unit_array[i].tile_position.y == cursor_tile_position_y){
                if(unit_array[i].unitJob != NULL && unit_array[i].has_finished_turn == 0){
                    currentSelectedUnit = &unit_array[i];
                    change_game_state(UNIT_SUMMARY_MENU);
                    return; 
                }
            }
        }
    }
    update_camera();
    
    update_cursor();
    cursor_update_free_movement();
    update_map_sprite_animation();
}

void queue_draw_state_cursor_movement(){
    draw_cursor();
}


void draw_state_cursor_movement(){

}