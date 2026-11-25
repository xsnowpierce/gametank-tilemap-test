#include "unit_selected_flicker.h"

#define SHOW_SPRITES_FRAME_COUNT 40
#define HIDE_SPRITES_FRAME_COUNT 8

unsigned char unit_flicker_do_draw_unit = 0;
unsigned char current_sprite_visibility_ticks = HIDE_SPRITES_FRAME_COUNT;

void update_unit_flickering(){
    if (current_sprite_visibility_ticks > 1){
        --current_sprite_visibility_ticks;
    }
    else{
        unit_flicker_do_draw_unit ^= 1;

        if (unit_flicker_do_draw_unit){
            current_sprite_visibility_ticks = SHOW_SPRITES_FRAME_COUNT;
        } 

        else{
            current_sprite_visibility_ticks = HIDE_SPRITES_FRAME_COUNT;
        }
    }
}
