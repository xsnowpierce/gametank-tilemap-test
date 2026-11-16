#ifndef TEXT_DRAWING_H
#define TEXT_DRAWING_H

#include "gt/gfx/sprites.h"

extern SpriteSlot textSlot;

void initialize_text();

void print_text(char x_position, char y_position, char* text);
void print_number(char x_position, char y_position, char* number);


#endif