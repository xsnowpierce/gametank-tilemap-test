#include "cursor.h"
#include "camera.h"
#include "gt/banking.h"
#include "gt/gfx/sprites.h"
#include "gt/input.h"
#include "gt/gfx/draw_queue.h"
#include "vector.h"
#include "gen/bank_nums.h"

static void on_cursor_move();
static void query_free_movement();
static void query_locked_movement(vector_u8b *moveable_tiles, unsigned char moveable_tile_count, vector_u8b unit_position); 

#define TILE_SIZE 8

#define SPRITE_ANIMATION_TICK_FRAMES 30

#define CURSOR_MAXIMUM_TILE_X 31
#define CURSOR_MAXIMUM_TILE_Y 30
#define CURSOR_MINIMUM_TILE_X 0
#define CURSOR_MINIMUM_TILE_Y 1

#define INPUT_FRAMES_DELAY 5
#define FIRST_MOVEMENT_TICK_DELAY 15

unsigned char cursor_tile_position_x = CURSOR_MINIMUM_TILE_X, cursor_tile_position_y = CURSOR_MINIMUM_TILE_Y;
unsigned char cursorSpriteBank;

unsigned char current_input_frame_delay = 0;
unsigned char current_sprite_frame_tick = 0;
unsigned char spriteUse = 0;

char is_holding_movement = 0;
char current_holding_movement_delay = 0;

void initialize_cursor(unsigned char bank){
    cursorSpriteBank = bank;
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
    update_cursor_animation();

    if(current_input_frame_delay > 0){
        --current_input_frame_delay;
    }
}

void update_cursor_animation(){
    ++current_sprite_frame_tick;

    if(current_sprite_frame_tick == SPRITE_ANIMATION_TICK_FRAMES){
        spriteUse ^= 1;
        current_sprite_frame_tick = 0;
    }
}

void cursor_update_free_movement(){
    push_rom_bank();
    change_rom_bank(BANK_PROG0);
    query_free_movement();
    pop_rom_bank();
}

#pragma code-name(push, "PROG0")
static void query_free_movement(){
    signed char input_x = 0, input_y = 0;
    signed char cursor_old_x = cursor_tile_position_x;
    signed char cursor_old_y = cursor_tile_position_y;

    if(camera_is_moving != 0){
        return;
    }

    // read inputs
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

    // make sure we are allowed to move it
    if(current_input_frame_delay > 0){
        return;
    }

    if(!is_holding_movement){
        // player isnt holding down movement yet.
        // 
        is_holding_movement = 1;
        current_holding_movement_delay = FIRST_MOVEMENT_TICK_DELAY;
    }else{
        if(input_x == 0 && input_y == 0){
            is_holding_movement = 0;
            current_holding_movement_delay = 0;
        }
        
        if(current_holding_movement_delay > 0){
            --current_holding_movement_delay;
            return;
        }

    }

    

    cursor_tile_position_x = move_axis(cursor_tile_position_x, input_x, CURSOR_MINIMUM_TILE_X, CURSOR_MAXIMUM_TILE_X);
    cursor_tile_position_y = move_axis(cursor_tile_position_y, input_y, CURSOR_MINIMUM_TILE_Y, CURSOR_MAXIMUM_TILE_Y);

    if (cursor_tile_position_x != cursor_old_x || cursor_tile_position_y != cursor_old_y){
        on_cursor_move();
        current_input_frame_delay = INPUT_FRAMES_DELAY;
    }else{
        // player has stopped moving the cursor
        // reset values
        is_holding_movement = 0;
        current_holding_movement_delay = 0;
    }
}
#pragma code-name (pop)

void cursor_update_locked_movement(vector_u8b *moveable_tiles, unsigned char moveable_tile_count, vector_u8b unit_position){
    push_rom_bank();
    change_rom_bank(BANK_PROG0);
    query_locked_movement(moveable_tiles, moveable_tile_count, unit_position);
    pop_rom_bank();
}

#pragma code-name(push, "PROG0")
static void query_locked_movement(vector_u8b *moveable_tiles, unsigned char moveable_tile_count, vector_u8b unit_position){
    unsigned char i, found_tile_in_array = 0;
    signed char input_x = 0, input_y = 0;
    vector_u8b cursor_old_position;
    vector_u8b cursor_target_position;

    cursor_old_position.x = cursor_tile_position_x;
    cursor_old_position.y = cursor_tile_position_y;

    if(camera_is_moving != 0){
        return;
    }

    // read inputs
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

    // make sure we are allowed to move it
    if(current_input_frame_delay > 0){
        return;
    }

    cursor_target_position.x = move_axis(cursor_tile_position_x, input_x, CURSOR_MINIMUM_TILE_X, CURSOR_MAXIMUM_TILE_X);
    cursor_target_position.y = move_axis(cursor_tile_position_y, input_y, CURSOR_MINIMUM_TILE_Y, CURSOR_MAXIMUM_TILE_Y);


    // check if we can move here
    // first, check if destination is the units home tile
    if(cursor_target_position.x == unit_position.x && cursor_target_position.y == unit_position.y){
        found_tile_in_array = 1;
    }else{
        for (i = 0; i < moveable_tile_count; ++i) {
            if (moveable_tiles[i].x == cursor_target_position.x && moveable_tiles[i].y == cursor_target_position.y){
                found_tile_in_array = 1;
                break;
            }
        }
    }

    if(found_tile_in_array == 1){

        if(!is_holding_movement){
            // player isnt holding down movement yet.
            // 
            is_holding_movement = 1;
            current_holding_movement_delay = FIRST_MOVEMENT_TICK_DELAY;
        }else{
            if(input_x == 0 && input_y == 0){
                is_holding_movement = 0;
                current_holding_movement_delay = 0;
            }
            
            if(current_holding_movement_delay > 0){
                --current_holding_movement_delay;
                return;
            }

        }

        cursor_tile_position_x = cursor_target_position.x;
        cursor_tile_position_y = cursor_target_position.y;

        if (cursor_tile_position_x != cursor_old_position.x || cursor_tile_position_y != cursor_old_position.y){
            on_cursor_move();
            current_input_frame_delay = INPUT_FRAMES_DELAY;
        }else{
            // player has stopped moving the cursor
            // reset values
            is_holding_movement = 0;
            current_holding_movement_delay = 0;
        }
    }else{
        is_holding_movement = 0;
        current_holding_movement_delay = 0;
    }
}
#pragma code-name (pop)

static void on_cursor_move(){
    int current_x = cursor_tile_position_x - (camera_x >> 3);
    int current_y = cursor_tile_position_y - (camera_y >> 3);

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
        move_camera(target_camera_x, target_camera_y);
    }
}

void draw_cursor(){
    queue_draw_sprite((cursor_tile_position_x << 3) - camera_x, (cursor_tile_position_y << 3) - camera_y, 8, 8, 8 + (spriteUse << 3), 0, cursorSpritePage);
}

void draw_cursor_selecting(){
    queue_draw_sprite((cursor_tile_position_x << 3) - camera_x, (cursor_tile_position_y << 3) - camera_y, 8, 8, 8 + (spriteUse << 3) + 16, 0, cursorSpritePage);
}