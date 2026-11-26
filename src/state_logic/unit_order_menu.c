#include "unit_order_menu.h"

#include "game_state.h"
#include "../map/map_tile_helper.h"
#include "unit_selected_flicker.h"
#include "../map/map_sprite_animation.h"
#include "../gt/gfx/gfx_sys.h"
#include "../gt/input.h"
#include "../map/map_tile_helper.h"


void cancel_order_menu();

void initialize_state_unit_order_menu(){

}

void update_state_unit_order_menu(){
    update_unit_flickering();
    update_map_sprite_animation();

    if(player1_new_buttons & INPUT_MASK_B){
        // cancel
        cancel_order_menu();
        return;
    }
}

void queue_draw_state_unit_order_menu(){

}

void draw_state_unit_order_menu(){
    vector_u8b draw_position;

    draw_position.x = temporary_unit_tile_position.x << 3;
    draw_position.y = temporary_unit_tile_position.y << 3;
    
    if(unit_flicker_do_draw_unit){
        direct_draw_unit_at_position(currentSelectedUnit, 
            get_current_map_frame_index(), draw_position);
        await_drawing();
    }
}

void unit_finish_turn(){
    currentSelectedUnit->has_finished_turn = 1;
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}

void cancel_order_menu(){
    revert_cursor_position_to_starting_position();
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}