#include "map_sprite_animation.h"

#define SPRITE_ANIMATION_FRAME_TIME 15
#define SPRITE_ANIMATION_MAX_FRAME 2

unsigned char current_animated_bank = 7;

static char current_frame_index = 0;
static char current_animation_counter = 0;
static char animation_ascending = 0;


void update_unit_animation(){
    ++current_animation_counter;

    if (current_animation_counter >= SPRITE_ANIMATION_FRAME_TIME) {
        current_animation_counter = 0;

        if (animation_ascending) {
            if (current_frame_index >= SPRITE_ANIMATION_MAX_FRAME) {
                animation_ascending = 0;
            } else {
                ++current_frame_index;
            }
        } else {
            if (current_frame_index <= 0) {
                animation_ascending = 1;
            } else {
                --current_frame_index;
            }
        }
    }
}

void update_map_sprite_animation(){
    update_unit_animation();
    current_animated_bank = 5 + current_frame_index;
}