#include "unit_selected_flicker.h"

#define SHOW_SPRITES_FRAME_COUNT 50
#define HIDE_SPRITES_FRAME_COUNT 15

unsigned char unit_flicker_do_draw_unit;
unsigned char current_sprite_visibility_ticks;

void update_unit_flickering(){
    ++current_sprite_visibility_ticks;
    if(unit_flicker_do_draw_unit == 1 && current_sprite_visibility_ticks >= SHOW_SPRITES_FRAME_COUNT){
        // hide sprite now
        current_sprite_visibility_ticks = 0;
        unit_flicker_do_draw_unit = 0;
    }
    else if(unit_flicker_do_draw_unit == 0 && current_sprite_visibility_ticks >= HIDE_SPRITES_FRAME_COUNT){
        // show the sprite
        current_sprite_visibility_ticks = 0;
        unit_flicker_do_draw_unit = 1;
    }
}