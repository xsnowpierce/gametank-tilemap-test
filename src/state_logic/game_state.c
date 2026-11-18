#include "game_state.h"
#include "cursor_movement.h"
#include "unit_selected.h"
#include "../gen/assets/ui.h"
#include "../map/map_drawing.h"

enum GAME_STATE currentGameState = CURSOR_MOVEMENT;
unsigned char current_map_id;

void do_ram_loading(){
    uiSpriteSlot = allocate_sprite(&ASSET__ui__uitilesheet_bmp_load_list);
}

void game_load_map(unsigned char map_id){
    current_map_id = map_id;
    load_map_id(map_id);
}

void change_game_state(enum GAME_STATE targetState){
    initialize_game_state(targetState);
    currentGameState = targetState;
}

void initialize_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            initialize_state_cursor_movement();
            break;
        case SELECTING_UNIT:
            initialize_state_unit_selected();
            break;
    }
}

void update_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            update_state_cursor_movement();
            break;
        case SELECTING_UNIT:
            update_state_unit_selected();
            break;
    }
}

void draw_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            draw_state_cursor_movement();
            break;
        case SELECTING_UNIT:
            draw_state_unit_selected();
            break;
    }
}

void queue_draw_game_state(enum GAME_STATE targetState){
    switch(targetState){
        case CURSOR_MOVEMENT:
            queue_draw_state_cursor_movement();
            break;
        case SELECTING_UNIT:
            queue_draw_state_unit_selected();
            break;
    }
}