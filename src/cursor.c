#include "cursor.h"
#include "camera.h"
#include "gt/gametank.h"
#include "gt/gfx/sprites.h"
#include "gt/input.h"
#include "gen/assets/player.h"
#include "gt/gfx/draw_queue.h"
#include "vector.h"


void on_cursor_move();
void query_cursor_move();

#define TILE_SIZE 8

#define SPRITE_ANIMATION_TICK_FRAMES 30

#define CURSOR_MAXIMUM_TILE_X 30
#define CURSOR_MAXIMUM_TILE_Y 29
#define CURSOR_MINIMUM_TILE_X 1
#define CURSOR_MINIMUM_TILE_Y 2

#define INPUT_FRAMES_DELAY 4
#define CAMERA_MOVE_TIME 7

unsigned char cursor_tile_position_x = CURSOR_MINIMUM_TILE_X, cursor_tile_position_y = CURSOR_MINIMUM_TILE_Y;
SpriteSlot *cursorSpritePage;

unsigned char current_input_frame_delay = 0;
unsigned char current_sprite_frame_tick = 0;
unsigned char spriteUse = 0;


void initialize_cursor(SpriteSlot *slot){
    cursorSpritePage = slot;
}

static signed char move_axis(signed char position, signed char input, unsigned char minimum, unsigned char maximum){
    if (input > 0) {
        if ((unsigned char)input > maximum - position)
            return maximum;
    } else if (input < 0) {
        if ((unsigned char)(-input) > position - minimum)
            return minimum;
    }

    position += input;
    return position;
}


void update_cursor(){
    
    if(camera_is_moving == 0){
        query_cursor_move();
    }

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


void query_cursor_move(){
    signed char input_x = 0, input_y = 0;
    signed char cursor_old_x = cursor_tile_position_x;
    signed char cursor_old_y = cursor_tile_position_y;
    
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

    cursor_tile_position_x = move_axis(cursor_tile_position_x, input_x, CURSOR_MINIMUM_TILE_X, CURSOR_MAXIMUM_TILE_X);
    cursor_tile_position_y = move_axis(cursor_tile_position_y, input_y, CURSOR_MINIMUM_TILE_Y, CURSOR_MAXIMUM_TILE_Y);

    if (cursor_tile_position_x != cursor_old_x || cursor_tile_position_y != cursor_old_y){
        on_cursor_move();
        current_input_frame_delay = INPUT_FRAMES_DELAY;
    }
}


void on_cursor_move(){
    int current_x = cursor_tile_position_x - (camera_x / TILE_SIZE);
    int current_y = cursor_tile_position_y - (camera_y / TILE_SIZE);

    signed char target_camera_x = 0, target_camera_y = 0;

    if (current_x <= 1){
        target_camera_x = -TILE_SIZE;
    }else if (current_x >= 14){
        target_camera_x = TILE_SIZE;
    }
    if (current_y <= 2){
        target_camera_y = -TILE_SIZE;
    }else if (current_y >= 13){
        target_camera_y = TILE_SIZE;
    }


    if(target_camera_x != 0 || target_camera_y != 0){
        move_camera(target_camera_x, target_camera_y, CAMERA_MOVE_TIME);
    }
}




void draw_cursor(){

    if(spriteUse == 0){
        queue_draw_sprite((cursor_tile_position_x * TILE_SIZE) - camera_x, (cursor_tile_position_y * TILE_SIZE) - camera_y, 8, 8, 8, 0, *cursorSpritePage);
    }
    else{
        queue_draw_sprite((cursor_tile_position_x  * TILE_SIZE) - camera_x, (cursor_tile_position_y * TILE_SIZE) - camera_y, 8, 8, 16, 0, *cursorSpritePage);
    }
}