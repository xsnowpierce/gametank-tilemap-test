#include "unit_order_menu.h"

#include "game_state.h"
#include "../map/map_tile_helper.h"
#include "unit_selected_flicker.h"
#include "../map/map_sprite_animation.h"
#include "../gt/gfx/gfx_sys.h"

void initialize_state_unit_order_menu(){

}

void update_state_unit_order_menu(){
    update_unit_flickering();
    update_map_sprite_animation();
}

void queue_draw_state_unit_order_menu(){

}

void draw_state_unit_order_menu(){
    vector_u8b draw_position;

    draw_position.x = currentSelectedUnit->tile_position.x << 3;
    draw_position.y = currentSelectedUnit->tile_position.y << 3;
    
    if(unit_flicker_do_draw_unit){
        direct_draw_unit_at_position(currentSelectedUnit, 
            0, draw_position);
        await_drawing();
    }
}

void unit_finish_turn(){
    currentSelectedUnit->has_finished_turn = 1;
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}