#include "text_drawing.h"
#include "gen/assets/font.h"


SpriteSlot textSlot;

void initialize_text(){
    textSlot = allocate_sprite(&ASSET__font__bios5_bmp_load_list);
}

