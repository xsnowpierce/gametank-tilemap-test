#include "game_state.h"
#include "cursor_movement.h"
#include "unit_selected.h"

enum GAME_STATE currentGameState = CURSOR_MOVEMENT;

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