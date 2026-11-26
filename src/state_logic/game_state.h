#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../units.h"

#define WALKING_SPRITE_ANIMATION_FRAME_LENGTH 20

enum GAME_STATE {
    CURSOR_MOVEMENT, UNIT_SUMMARY_MENU, CHOOSING_MOVEMENT_PATH, 
    UNIT_MOVING_TO_TILE, UNIT_ORDER_MENU
};

extern enum GAME_STATE currentGameState;
extern unsigned char current_map_id;
extern Unit unit_array[MAX_UNIT_COUNT];
extern Unit *currentSelectedUnit;
extern SpriteSlot uiSpriteSlot;

//////////// STATE VARIABLE HOLDERS

/* 
    Used for keeping the units movement position across states. 
    Set by unit_moving_to_tile.c for the ability to store the sprite position
    across other states.
*/ 
extern vector_u8b temporary_unit_tile_position;

/*
    The value to be set when the user starts selecting a unit and moves the cursor around.
    This holds onto the inital value, so if the player cancels the selection, 
    the position can be restored.
*/
extern vector_u8b starting_cursor_position;

void do_ram_loading();
void game_load_map(unsigned char map_id);

void change_game_state(enum GAME_STATE targetState);
void initialize_game_state(enum GAME_STATE targetState);
void update_game_state(enum GAME_STATE targetState);
void draw_game_state(enum GAME_STATE targetState);
void queue_draw_game_state(enum GAME_STATE targetState);

void reset_all_unit_turn_value();

// This function will set the cursor to member starting_cursor_position.
void revert_cursor_position_to_starting_position();
#endif