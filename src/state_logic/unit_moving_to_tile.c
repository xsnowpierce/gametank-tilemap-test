#include "unit_moving_to_tile.h"

#include "../gt/gfx/draw_queue.h"
#include "game_state.h"

static unsigned char current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
static unsigned char current_animation_frame = 0;

void initialize_state_unit_moving_to_tile(){

}

void update_state_unit_moving_to_tile(){
    --current_unit_animation_frame_tick;
    if(current_unit_animation_frame_tick <= 0){
        current_animation_frame ^= 1;
        current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
    }
}

void queue_draw_state_unit_moving_to_tile(){

}

void draw_state_unit_moving_to_tile(){
    direct_draw_unit(currentSelectedUnit, 3 + current_animation_frame);
    await_drawing();
}