#include "cursor_movement.h"
#include "../cursor.h"
#include "game_state.h"
#include "../units.h"
#include "../camera.h"
#include "../gt/input.h"
#include "unit_selected.h"

Unit clickedUnit;

void initialize_state_cursor_movement(){

}

void update_state_cursor_movement(){
    char cursorClickResult = 0;

    if(player1_buttons & INPUT_MASK_A){
        // player pressed A, check if there is a unit on this tile
        // if there is, keep track of the unit, and change current game state
        cursorClickResult = get_unit_on_tile(cursor_tile_position_x, cursor_tile_position_y, &clickedUnit);
        if(cursorClickResult){
            // we clicked on a unit!
            selectedUnit = clickedUnit;
            change_game_state(SELECTING_UNIT);
            
        }
        return;
    }
    update_camera();
    update_cursor();
    update_unit_animation();
    update_unit_cache();
}

void queue_draw_state_cursor_movement(){
    draw_cursor();
    draw_visible_units();
}


void draw_state_cursor_movement(){

}