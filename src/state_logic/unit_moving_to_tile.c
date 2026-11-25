#include "unit_moving_to_tile.h"

#include "../gt/gfx/draw_queue.h"
#include "game_state.h"
#include "../cursor.h"
#include "../map/map_moving.h"

void progress_to_unit_order_menu();
void increment_tile_movement();

#define TILE_SIZE 8

#define MOVEMENT_FRAMES_UNTIL_MOVE_TICK 3
static unsigned char current_movement_frames_until_tick;

static vector_u8b *unit_movement_path_to_selected_tile;

static unsigned char tiles_to_reach_destination;
static unsigned char current_tile_progression;

static vector_u8b target_tile_position;

static unsigned char current_sprite_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
static unsigned char current_sprite_animation_frame = 0;

static vector_s8b move_step;
static vector_s8b drawing_offset;
static vector_u8b animation_tile_position;

static void set_next_tile_target(){
    vector_s8b difference_in_position;

    target_tile_position = unit_movement_path_to_selected_tile[current_tile_progression + 1];

    difference_in_position.x = (signed char) target_tile_position.x - (signed char) animation_tile_position.x;
    difference_in_position.y = (signed char) target_tile_position.y - (signed char) animation_tile_position.y;

    move_step.x = 0;
    move_step.y = 0;

    drawing_offset.x = 0;
    drawing_offset.y = 0;

    if (difference_in_position.x < 0) {
        move_step.x = -1;
    }
    else if (difference_in_position.x > 0) {
        move_step.x =  1;
    }

    if (difference_in_position.y < 0) {
        move_step.y = -1;
    }

    else if (difference_in_position.y > 0) {
        move_step.y =  1;
    }
}


void initialize_state_unit_moving_to_tile(){
    vector_u8b clicked_position;

    clicked_position.x = cursor_tile_position_x;
    clicked_position.y = cursor_tile_position_y;

    animation_tile_position = currentSelectedUnit->tile_position;
    current_sprite_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;

    drawing_offset.x = 0;
    drawing_offset.y = 0;
    current_tile_progression = 0;
    current_sprite_animation_frame = 0;
    current_movement_frames_until_tick = MOVEMENT_FRAMES_UNTIL_MOVE_TICK;

    tiles_to_reach_destination = get_unit_path_to_tile(
        current_map_id,
        currentSelectedUnit->tile_position,
        clicked_position,
        currentSelectedUnit->unitStats.movementRange,
        unit_movement_path_to_selected_tile
    );

    if (tiles_to_reach_destination == 0) {
        progress_to_unit_order_menu();
        return;
    }

    set_next_tile_target();
}

void update_state_unit_moving_to_tile(){
    --current_sprite_animation_frame_tick;

    if (current_sprite_animation_frame_tick == 0) {
        current_sprite_animation_frame ^= 1;
        current_sprite_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
    }


    --current_movement_frames_until_tick;
    if(current_movement_frames_until_tick == 0){
        increment_tile_movement();
        current_movement_frames_until_tick = MOVEMENT_FRAMES_UNTIL_MOVE_TICK;
    }
}

void increment_tile_movement(){
    if (move_step.x != 0) {
        drawing_offset.x += move_step.x;
    }
    else if (move_step.y != 0) {
        drawing_offset.y += move_step.y;
    }

    if ((move_step.x > 0 && drawing_offset.x >= TILE_SIZE)
        || (move_step.x < 0 && drawing_offset.x <= -TILE_SIZE)
        || (move_step.y > 0 && drawing_offset.y >= TILE_SIZE)
        || (move_step.y < 0 && drawing_offset.y <= -TILE_SIZE))
    {
        // we have reached the next tile, reset values and progress
        animation_tile_position = target_tile_position;
        drawing_offset.x = 0;
        drawing_offset.y = 0;

        ++current_tile_progression;

        if (current_tile_progression >= (tiles_to_reach_destination - 1)) {
            // we have reached the end of the animation, progress to the
            // next part of the program.
            progress_to_unit_order_menu();
            return;
        }

        set_next_tile_target();
    }
}

vector_u8b calculate_drawing_position(){
    vector_u8b pixel_position;

    pixel_position.x = animation_tile_position.x << 3;
    pixel_position.y = animation_tile_position.y << 3;

    pixel_position.x += drawing_offset.x;
    pixel_position.y += drawing_offset.y;

    return pixel_position;
}

void draw_state_unit_moving_to_tile(){
    vector_u8b drawing_position;
    drawing_position = calculate_drawing_position();

    direct_draw_unit_at_position(
        currentSelectedUnit,
        current_sprite_animation_frame + 3, 
        drawing_position
    );
    
    await_drawing();
}

void queue_draw_state_unit_moving_to_tile(){

}

void progress_to_unit_order_menu(){
    //currentSelectedUnit->temp_tile_position = animation_tile_position;
    change_game_state(UNIT_ORDER_MENU);
}