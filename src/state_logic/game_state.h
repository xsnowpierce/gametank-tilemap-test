#ifndef GAME_STATE_H
#define GAME_STATE_H

enum GAME_STATE {
    CURSOR_MOVEMENT, SELECTING_UNIT
};

extern enum GAME_STATE currentGameState;

void change_game_state(enum GAME_STATE targetState);
void initialize_game_state(enum GAME_STATE targetState);
void update_game_state(enum GAME_STATE targetState);
void draw_game_state(enum GAME_STATE targetState);
void queue_draw_game_state(enum GAME_STATE targetState);

#endif