#include "game_state.h"

#include "cursor_movement.h"
#include "unit_summary_menu.h"
#include "choosing_movement_path.h"
#include "unit_moving_to_tile.h"
#include "unit_order_menu.h"

#include "../gen/assets/ui.h"
#include "../map/map_drawing.h"
#include "../map/unit_data.h"
#include "../cursor.h"
#include <string.h>

#include "unit_selected_flicker.h"

enum GAME_STATE currentGameState = CURSOR_MOVEMENT;
unsigned char current_map_id;
Unit unit_array[MAX_UNIT_COUNT];

SpriteSlot uiSpriteSlot;
Unit *currentSelectedUnit;

// state variable holders
vector_u8b temporary_unit_tile_position;
vector_u8b starting_cursor_position;

void do_ram_loading(){
    uiSpriteSlot = allocate_sprite(&ASSET__ui__uitilesheet_bmp_load_list);
}

void game_load_map(unsigned char map_id){
    current_map_id = map_id;
    load_map_id(map_id);

    // copy the appropirate unit array into ram
    memcpy(unit_array, game_unit_array[map_id], sizeof(game_unit_array[map_id]));

    draw_unit_sprites_into_sram(unit_array, MAX_UNIT_COUNT);
}

void change_game_state(enum GAME_STATE targetState){
    currentGameState = targetState;
    initialize_game_state(targetState);
}

void initialize_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            initialize_state_cursor_movement();
            break;
        case UNIT_SUMMARY_MENU:
            initialize_state_unit_summary_menu();
            break;
        case CHOOSING_MOVEMENT_PATH:
            initialize_state_choosing_movement_path();
            break;
        case UNIT_MOVING_TO_TILE:
            initialize_state_unit_moving_to_tile();
            break;
        case UNIT_ORDER_MENU:
            initialize_state_unit_order_menu();
            break;
    }
}

void update_game_state(enum GAME_STATE targetState){
    update_unit_flickering();
    
    switch(targetState){
        case CURSOR_MOVEMENT:
            update_state_cursor_movement();
            break;
        case UNIT_SUMMARY_MENU:
            update_state_unit_summary_menu();
            break;
        case CHOOSING_MOVEMENT_PATH:
            update_state_choosing_movement_path();
            break;
        case UNIT_MOVING_TO_TILE:
            update_state_unit_moving_to_tile();
            break;
        case UNIT_ORDER_MENU:
            update_state_unit_order_menu();
            break;
    }
}

void draw_game_state(enum GAME_STATE targetState){
    draw_level_map();

    switch(targetState){
        case CURSOR_MOVEMENT:
            draw_state_cursor_movement();
            break;
        case UNIT_SUMMARY_MENU:
            draw_state_unit_summary_menu();
            break;
        case CHOOSING_MOVEMENT_PATH:
            draw_state_choosing_movement_path();
            break;
        case UNIT_MOVING_TO_TILE:
            draw_state_unit_moving_to_tile();
            break;
        case UNIT_ORDER_MENU:
            draw_state_unit_order_menu();
            break;
    }
}

void queue_draw_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            queue_draw_state_cursor_movement();
            break;
        case UNIT_SUMMARY_MENU:
            queue_draw_state_unit_summary_menu();
            break;
        case CHOOSING_MOVEMENT_PATH:
            queue_draw_state_choosing_movement_path();
            break;
        case UNIT_MOVING_TO_TILE:
            queue_draw_state_unit_moving_to_tile();
            break;
        case UNIT_ORDER_MENU:
            queue_draw_state_unit_order_menu();
            break;
    }
}

void reset_all_unit_turn_value(){
    unsigned char i;

    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        unit_array[i].has_finished_turn = 0;
    }
}

void revert_cursor_position_to_starting_position(){
    cursor_tile_position_x = starting_cursor_position.x;
    cursor_tile_position_y = starting_cursor_position.y;
}