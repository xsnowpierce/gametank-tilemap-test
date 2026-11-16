#include "unit_selected.h"
#include "../gt/gfx/draw_queue.h"
#include "../units.h"

Unit selectedUnit;
SpriteSlot uiSpriteSlot;

void initialize_state_unit_selected(){
    
}

void update_state_unit_selected(){

}

void queue_draw_state_unit_selected(){
    draw_visible_units();
    queue_draw_sprite(8, 8, 40, 48, 0, 0, uiSpriteSlot); // draw unit selected page
    // now draw text on top
}

void draw_state_unit_selected(){

}