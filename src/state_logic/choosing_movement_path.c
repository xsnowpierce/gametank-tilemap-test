#include "choosing_movement_path.h"

#include "../map/map_moving.h"
#include "../camera.h"
#include "../cursor.h"
#include "../gt/feature/bittext/bittext.h"
#include "../map/map_sprite_animation.h"
#include "../gt/input.h"
#include "../gt/gfx/draw_queue.h"
#include "game_state.h"
#include "../map/map_tile_helper.h"
#include "unit_selected_flicker.h"

#include "../gt/banking.h"
#include "../gen/bank_nums.h"

static void cancel_selecting_unit();
static void clicked_with_unit();

static unsigned char current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
static unsigned char current_animation_frame = 0;

void initialize_state_choosing_movement_path(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);

    calculate_reachable_tiles(current_map_id, currentSelectedUnit->tile_position, currentSelectedUnit->unitStats.movementRange);
    //unit_reachable_tiles_count = get_unit_reachable_tiles(current_map_id, currentSelectedUnit->tile_position, currentSelectedUnit->unitStats.movementRange, &unit_reachable_tiles);
    
    pop_rom_bank();
}

void update_state_choosing_movement_path(){
    --current_unit_animation_frame_tick;
    if(current_unit_animation_frame_tick <= 0){
        current_animation_frame ^= 1;
        current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
    }

    update_cursor();
    update_cursor_animation();

    update_map_sprite_animation();
    update_camera();
    cursor_update_locked_movement(&current_reachable_tiles, 
        current_reachable_tiles_count, 
        currentSelectedUnit->tile_position
    );

    if(player1_new_buttons & INPUT_MASK_A){
        // try to do unit action
        clicked_with_unit();
        return;
    }
    else if(player1_new_buttons & INPUT_MASK_B){
        // cancel out of menu
        cancel_selecting_unit();
        return;
    }
}

void queue_draw_state_choosing_movement_path(){
    if(unit_flicker_do_draw_unit){
        draw_cursor_selecting();
    }
}

void draw_state_choosing_movement_path(){
    if(unit_flicker_do_draw_unit){
        direct_draw_unit(currentSelectedUnit, current_animation_frame + 3);
        await_drawing();
    }
}

static void clicked_with_unit(){
    // check if unit is on this tile. if so, ignore the attempt
    vector_u8b cursor_position;
    unsigned char i = 0, unit_on_tile = 0;
    
    cursor_position.x = cursor_tile_position_x;
    cursor_position.y = cursor_tile_position_y;

    unit_on_tile = is_unit_on_tile(cursor_position, unit_array);

    if(unit_on_tile > 0){
        return;
    }else{
        change_game_state(UNIT_MOVING_TO_TILE);
    }
}

static void cancel_selecting_unit(){
    revert_cursor_position_to_starting_position();
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}