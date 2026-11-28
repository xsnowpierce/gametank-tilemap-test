#include "unit_moving_to_tile.h"

#include "../gt/gfx/draw_queue.h"
#include "game_state.h"
#include "../cursor.h"
#include "../map/map_moving.h"

#include "../gt/banking.h"
#include "../gen/bank_nums.h"

#include "../gt/audio/music.h"
#include "../gen/assets/sfx.h"

void progress_to_unit_order_menu();
void increment_tile_movement();
void set_next_tile_target();
void private_init();
void private_update();
vector_u8b calculate_drawing_position();

#define TILE_SIZE 8

#define MOVEMENT_FRAMES_UNTIL_MOVE_TICK 2
unsigned char current_movement_frames_until_tick;

unsigned char current_tile_progression;

vector_u8b target_tile_position;

unsigned char current_sprite_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
unsigned char current_sprite_animation_frame = 0;

vector_s8b move_step;
vector_s8b drawing_offset;
vector_u8b animation_tile_position;

#define PLAY_FOOTSTEP_SFX_TICK_DELAY 15
signed char current_footstep_tick_value;

void initialize_state_unit_moving_to_tile(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    private_init();
    pop_rom_bank();
}

void update_state_unit_moving_to_tile(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    private_update();
    pop_rom_bank();
}

void draw_state_unit_moving_to_tile(){
    vector_u8b drawing_position;

    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    drawing_position = calculate_drawing_position();
    pop_rom_bank();
    
    direct_draw_unit_at_position(
        currentSelectedUnit,
        current_sprite_animation_frame + 3, 
        drawing_position
    );
    
    await_drawing();
}

void queue_draw_state_unit_moving_to_tile(){

}

#pragma code-name (push, "PROG1")
void private_init(){
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

    calculate_unit_path_to_tile(currentSelectedUnit, clicked_position);

    if (target_movement_path_length == 0) {
        progress_to_unit_order_menu();
        return;
    }
    set_next_tile_target();

    current_footstep_tick_value = 0;
}

void private_update(){
    --current_sprite_animation_frame_tick;

    if (current_sprite_animation_frame_tick <= 0) {
        current_sprite_animation_frame ^= 1;
        current_sprite_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
    }


    --current_movement_frames_until_tick;
    if(current_movement_frames_until_tick <= 0){
        increment_tile_movement();
        
        current_movement_frames_until_tick = MOVEMENT_FRAMES_UNTIL_MOVE_TICK;
    }

    --current_footstep_tick_value;
    if(current_footstep_tick_value <= 0){
        //push_rom_bank();
        //change_rom_bank(BANK_);
        play_sound_effect(ASSET__sfx__footstep_sound_sfx_ID, 0);
        //pop_rom_bank();
        
        current_footstep_tick_value = PLAY_FOOTSTEP_SFX_TICK_DELAY;
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

        if (current_tile_progression >= (target_movement_path_length - 1)) {
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

void progress_to_unit_order_menu(){
    temporary_unit_tile_position = animation_tile_position;
    change_game_state(UNIT_ORDER_MENU);
}

void set_next_tile_target(){
    vector_s8b difference_in_position;

    target_tile_position = target_movement_path[current_tile_progression + 1];

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
#pragma code-name (pop)