#include "unit_order_menu.h"

#include "game_state.h"
#include "../map/map_tile_helper.h"

void initialize_state_unit_order_menu(){

}

void update_state_unit_order_menu(){

}

void queue_draw_state_unit_order_menu(){

}

void draw_state_unit_order_menu(){

}

void unit_finish_turn(){
    currentSelectedUnit->has_finished_turn = 1;
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}