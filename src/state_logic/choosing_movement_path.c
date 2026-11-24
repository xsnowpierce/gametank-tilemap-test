#include "choosing_movement_path.h"

#include "../gt/gfx/draw_queue.h"
#include "../map/map_moving.h"
#include "../camera.h"
#include "../cursor.h"
#include "../gt/feature/bittext/bittext.h"
#include "../map/map_sprite_animation.h"
#include "../gt/input.h"
#include "../gt/gfx/draw_queue.h"
#include "game_state.h"
#include "unit_selected_flicker.h"

void cancel_selecting_unit();
void clicked_with_unit();

vector_u8b *unit_movement_path_to_selected_tile;

vector_u8b unit_reachable_tiles;
unsigned char unit_reachable_tiles_count;

void initialize_state_choosing_movement_path(){
    unit_reachable_tiles_count = get_unit_reachable_tiles(current_map_id, currentSelectedUnit->tile_position, currentSelectedUnit->unitStats.movementRange, &unit_reachable_tiles);
}

void update_state_choosing_movement_path(){
    update_cursor();
    update_cursor_animation();

    update_map_sprite_animation();
    update_camera();
    cursor_update_locked_movement(&unit_reachable_tiles, 
        unit_reachable_tiles_count, 
        currentSelectedUnit->tile_position
    );

    if(player1_new_buttons & INPUT_MASK_A){
        // try to do unit action
        clicked_with_unit();
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
        direct_draw_unit(currentSelectedUnit, 3);
        await_drawing();
    }
}

void clicked_with_unit(){
    vector_u8b cursor_clicked_position;
    vector_u8b *unit_movement_path;

    cursor_clicked_position.x = cursor_tile_position_x;
    cursor_tile_position_y = cursor_tile_position_y;

    // move unit visually, not functionally, to the new position, using their walking
    // animation and using the most efficient path as per the algorithm
    
    get_unit_path_to_tile(0, currentSelectedUnit->tile_position, 
        cursor_clicked_position, 
        currentSelectedUnit->unitStats.movementRange, 
        unit_movement_path_to_selected_tile
    );

    change_game_state(UNIT_MOVING_TO_TILE);
}