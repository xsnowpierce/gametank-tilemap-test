#include "input.h"
#include "gametank.h"

int player1_buttons = 0, player1_old_buttons = 0, player1_new_buttons = 0;
int player2_buttons = 0, player2_old_buttons = 0, player2_new_buttons = 0;

#pragma optimize (push, off)
void update_inputs(){
    char inputsA, inputsB;
    inputsA = *gamepad_2;
    inputsA = *gamepad_1;
    inputsB = *gamepad_1;

    player1_old_buttons = player1_buttons;
    player1_buttons = ~((((int) inputsB) << 8) | inputsA);
    player1_buttons &= INPUT_MASK_ALL_KEYS;
    player1_new_buttons = player1_buttons & ~player1_old_buttons;

    inputsA = *gamepad_2;
    inputsB = *gamepad_2;
    player2_old_buttons = player2_buttons;
    player2_buttons = ~((((int) inputsB) << 8) | inputsA);
    player2_buttons &= INPUT_MASK_ALL_KEYS;
    player2_new_buttons = player2_buttons & ~player2_old_buttons;
}
#pragma optimize (pop)

unsigned char pressed_input_this_frame(unsigned char controller_port, int button_mask){
    switch(controller_port){
        case 0:
            if((!(player1_old_buttons & button_mask)) && (player1_new_buttons & button_mask)){
                return 1;
            }
            return 0;
            break;
        case 1:
            if((!(player2_old_buttons & button_mask)) && (player2_new_buttons & button_mask)){
                return 1;
            }
            return 0;
            break;
    }
}