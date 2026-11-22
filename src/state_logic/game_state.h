#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "../units.h"

enum GAME_STATE {
    CURSOR_MOVEMENT, SELECTING_UNIT
};

extern enum GAME_STATE currentGameState;
extern unsigned char current_map_id;
extern Unit unit_array[MAX_UNIT_COUNT];

void do_ram_loading();
void game_load_map(unsigned char map_id);

void change_game_state(enum GAME_STATE targetState);
void initialize_game_state(enum GAME_STATE targetState);
void update_game_state(enum GAME_STATE targetState);
void draw_game_state(enum GAME_STATE targetState);
void queue_draw_game_state(enum GAME_STATE targetState);

#endif