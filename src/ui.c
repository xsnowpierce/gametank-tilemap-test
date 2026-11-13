#include "ui.h"
#include "camera.h"
#include "gt/gfx/sprites.h"
#include "gt/feature/text/text.h"
#include "cursor.h"
#include "map.h"

SpriteSlot textSlot;

void initialize_ui(){
    text_init();
    textSlot = text_load_font();
}

void update_ui(){

}

void draw_ui(){
    
}

void ui_draw_hovered_tile(MapLevel *level){

    unsigned char tile_id = level->TILE_DATA[cursor_tile_position_y * level->MAP_WIDTH + cursor_tile_position_x] - 1;

    char number_text[5];

    text_cursor_x = 0;
    text_cursor_y = 8;
    text_color = TEXT_COLOR_WHITE;

    text_print_string(get_tile_name_from_id(tile_id));
    text_print_string(", ");
    text_sprint_int(number_text, tile_id);
    text_print_string(number_text);
}

void draw_camera_and_cursor_position(){
    char number_text[5];
    char number_text2[5];

    text_cursor_x = 0;
    text_cursor_y = 8;
    text_color = TEXT_COLOR_WHITE;

    text_print_string("x = ");
    text_sprint_int(number_text, cursor_tile_position_x);
    text_print_string(number_text);

    text_cursor_x = 0;
    text_cursor_y = 16;
    text_print_string("y = ");
    text_sprint_int(number_text, cursor_tile_position_y);
    text_print_string(number_text);


    text_cursor_x = 0;
    text_cursor_y = 24;
    text_color = TEXT_COLOR_WHITE;

    text_print_string("cx = ");
    text_sprint_int(number_text, camera_x);
    text_print_string(number_text);

    text_cursor_x = 0;
    text_cursor_y = 32;
    text_print_string("cy = ");
    text_sprint_int(number_text, camera_y);
    text_print_string(number_text);
}