#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../units.h"

enum GAME_STATE {
    CURSOR_MOVEMENT, UNIT_SUMMARY_MENU, CHOOSING_MOVEMENT_PATH, 
    UNIT_MOVING_TO_TILE, UNIT_ORDER_MENU
};

extern enum GAME_STATE currentGameState;
extern unsigned char current_map_id;
extern Unit unit_array[MAX_UNIT_COUNT];
extern Unit *currentSelectedUnit;
extern SpriteSlot uiSpriteSlot;

void do_ram_loading();
void game_load_map(unsigned char map_id);

void change_game_state(enum GAME_STATE targetState);
void initialize_game_state(enum GAME_STATE targetState);
void update_game_state(enum GAME_STATE targetState);
void draw_game_state(enum GAME_STATE targetState);
void queue_draw_game_state(enum GAME_STATE targetState);

void reset_all_unit_turn_value();

#endif