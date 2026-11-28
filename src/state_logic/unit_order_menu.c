#include "unit_order_menu.h"

#include "game_state.h"
#include "../map/map_tile_helper.h"
#include "unit_selected_flicker.h"
#include "../map/map_sprite_animation.h"
#include "../gt/gfx/gfx_sys.h"
#include "../gt/input.h"
#include "../map/map_tile_helper.h"
#include "../gt/feature/bittext/bittext.h"
#include "../gt/gfx/draw_direct.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

#define TEXT_BANK QUADRANT_3 | 4

// pixel width of font, really
#define PIXELS_PER_TEXT_CHARACTER 4

void cancel_order_menu();
void preload_menu_into_vram();

void initialize_state_unit_order_menu(){
    // need to detect whether enemies are within our attacking range
    // if so, add attack to the list

    // have item and wait always

    // item will allow for changing the current weapon

    // wait will set them to have their turn over.

    // order menu should have a display of the current weapon selected.
    preload_menu_into_vram();
}

void preload_menu_into_vram(){
    direct_prepare_sprite_ram_array_mode(TEXT_BANK);
    // bittext_set_x(0);
    // bittext_set_y(0);
    // bittext_write_str("      ");
    bittext_set_x(0);
    bittext_set_y(0);
    bittext_write_str("ATTACK");
    bittext_set_x(0);
    bittext_set_y(8);
    bittext_write_str("ITEM");
    bittext_set_y(16);
    bittext_write_str("WAIT");
    bittext_set_y(24);
    bittext_write_str("WEAPON_NAME");
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