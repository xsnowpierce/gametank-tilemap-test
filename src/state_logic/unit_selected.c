#include "unit_selected.h"
#include "../gt/gfx/draw_queue.h"
#include "../units.h"
#include "../gt/feature/text/text.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

Unit selectedUnit;
SpriteSlot uiSpriteSlot;

void initialize_state_unit_selected(){
    
}

void update_state_unit_selected(){

}

void queue_draw_state_unit_selected(){
    draw_visible_units();
    
}

void draw_state_unit_selected(){
    

    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0, uiSpriteSlot); // draw unit selected page
    // now draw text on top

    await_draw_queue();

    text_cursor_x = UI_OFFSET_X + 3;
    text_cursor_y = UI_OFFSET_Y + 4;
    text_color = TEXT_COLOR_WHITE;
    text_print_string(selectedUnit.unitName);

    text_cursor_x = UI_OFFSET_X + 3;
    text_cursor_y = UI_OFFSET_Y + 11;
    text_color = TEXT_COLOR_WHITE;
    text_print_string(get_job_name(selectedUnit.unitJob));

    text_cursor_x = UI_OFFSET_X + 14;
    text_cursor_y = UI_OFFSET_Y + 19;
    text_color = TEXT_COLOR_WHITE;
    text_print_string("25");

    text_cursor_x = UI_OFFSET_X + 14;
    text_cursor_y = UI_OFFSET_Y + 27;
    text_color = TEXT_COLOR_WHITE;
    text_print_string("99");

    text_cursor_x = UI_OFFSET_X + 28;
    text_cursor_y = UI_OFFSET_Y + 27;
    text_color = TEXT_COLOR_WHITE;
    text_print_string("99");

    await_drawing();
}