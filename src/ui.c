#include "ui.h"
#include "camera.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/feature/text/text.h"
#include "cursor.h"
#include "map_defs.h"

void initialize_ui(){
    
}

void update_ui(){

}

void draw_ui(){
    
}

void ui_draw_hovered_tile(MapLevel *level){

    unsigned char tile_id = level->TILE_DATA[cursor_tile_position_y * level->MAP_WIDTH + cursor_tile_position_x] - 1;

    text_cursor_x = 0;
    text_cursor_y = 8;
    text_color = TEXT_COLOR_WHITE;
    text_print_string(get_tile_name_from_id(tile_id));
    await_drawing();
}