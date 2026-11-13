#include "cursor.h"
#include "camera.h"
#include "gt/gfx/sprites.h"
#include "gt/input.h"
#include "gen/assets/player.h"
#include "gt/gfx/draw_queue.h"

#define TILE_SIZE 8

signed int cursor_position_x = TILE_SIZE * 2, cursor_position_y = TILE_SIZE * 2;
SpriteSlot cursorSpritePage;

const unsigned char INPUT_FRAMES_DELAY = 7;
unsigned char current_input_frame_delay = 0;

const unsigned char SPRITE_ANIMATION_TICK_FRAMES = 3;
unsigned char current_sprite_frame_tick = 0;
unsigned char spriteUse = 0;


void initialize_cursor(){
    cursorSpritePage = allocate_sprite(&ASSET__player__player_bmp_load_list);
}

void update_cursor(){
    char input_x = 0, input_y = 0;

    if(current_input_frame_delay > 0){
        --current_input_frame_delay;
        return;
    }

    if(player1_buttons & INPUT_MASK_LEFT) {
        --input_x;
    }
    if(player1_buttons & INPUT_MASK_RIGHT){
        ++input_x;
    }
    if(player1_buttons & INPUT_MASK_UP){
        --input_y;
    }
    if(player1_buttons & INPUT_MASK_DOWN){
        ++input_y;
    }

    cursor_position_x += (input_x * TILE_SIZE); 
    cursor_position_y += (input_y * TILE_SIZE);


    current_input_frame_delay = INPUT_FRAMES_DELAY;

    ++current_sprite_frame_tick;

    if(current_sprite_frame_tick == SPRITE_ANIMATION_TICK_FRAMES){
        if(spriteUse == 0){
            spriteUse = 1;
        }
        else{
            spriteUse = 0;
        }

        current_sprite_frame_tick = 0;
    }
}

void draw_cursor(){
    if(spriteUse == 0){
        queue_draw_sprite(cursor_position_x - camera_x, cursor_position_y - camera_y, 8, 8, 8, 0, cursorSpritePage);
    }
    else{
        queue_draw_sprite(cursor_position_x - camera_x, cursor_position_y - camera_y, 8, 8, 16, 0, cursorSpritePage);
    }
}

vector_u8b get_cursor_point(){
    vector_u8b return_point = {0, 0};

    return_point.x = cursor_position_x << 7;
    return_point.y = cursor_position_y << 7;

    return return_point;
}