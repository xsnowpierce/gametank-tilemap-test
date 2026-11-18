#include "unit_selected.h"
#include "../gt/gfx/draw_direct.h"
#include "../units.h"
#include "../gt/feature/text/text.h"
#include "../map/map_moving.h"
#include "game_state.h"
#include "../camera.h"
#include "../cursor.h"

#include "../gen/assets/ui.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

//#define PROFILER_START(x) ((char*) 0x2800)[0] = 0x80; ((char*) 0x2800)[0] = x;
//#define PROFILER_END(x) ((char*) 0x2800)[0] = 0x80; ((char*) 0x2800)[0] = x | 0x40;

Unit selectedUnit;
SpriteSlot uiSpriteSlot;

vector_u8b cursor_starting_position;
unsigned char player_moved_cursor = 0;

vector_u8b *out_tiles;

void draw_unit_information();
void print_unit_information_into_gram();

void initialize_state_unit_selected(){
    PROFILER_START(3);
    //print_unit_information_into_gram();
    PROFILER_END(3);
    cursor_starting_position.x = cursor_tile_position_x;
    cursor_starting_position.y = cursor_tile_position_y;
    player_moved_cursor = 0;

    
    find_reachable_tiles(current_map_id, selectedUnit.tile_position, selectedUnit.unitStats.movementRange);
    get_reachable_tiles(out_tiles);
}

void update_state_unit_selected(){
    if(player_moved_cursor == 0){
        if(cursor_tile_position_x != cursor_starting_position.x || cursor_tile_position_y != cursor_starting_position.y){
            player_moved_cursor = 1;
        }
    }
    else{
        update_camera();
        update_cursor();
        //update_unit_animation();
        //update_unit_cache();
    }
}

void queue_draw_state_unit_selected(){
    draw_visible_units();
    draw_cursor();

    if(player_moved_cursor == 0){
        draw_unit_information();
    }
}

void draw_state_unit_selected(){
    
}

void print_unit_information_into_gram(){
    free_sprite(uiSpriteSlot);
    uiSpriteSlot = allocate_sprite(&ASSET__ui__uitilesheet_bmp_load_list);

    // now draw onto this somehow
}

void draw_unit_information(){
    PROFILER_START(1);
    //queue_draw_box(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0);
    direct_prepare_sprite_mode(uiSpriteSlot);
    DIRECT_DRAW_SPRITE(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0);
    await_drawing();
    //queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0, uiSpriteSlot); // draw unit selected page
    // now draw text on top

    PROFILER_END(1);
    //await_draw_queue();

    PROFILER_START(2);
    text_color = TEXT_COLOR_WHITE;

    text_cursor_x = UI_OFFSET_X + 3;
    text_cursor_y = UI_OFFSET_Y + 4;
    text_print_string(selectedUnit.unitName);

    text_cursor_x = UI_OFFSET_X + 3;
    text_cursor_y = UI_OFFSET_Y + 11;
    text_print_string(get_job_name(selectedUnit.unitJob));

    text_cursor_x = UI_OFFSET_X + 14;
    text_cursor_y = UI_OFFSET_Y + 19;
    text_print_string("25");

    text_cursor_x = UI_OFFSET_X + 14;
    text_cursor_y = UI_OFFSET_Y + 27;
    text_print_string("99");

    text_cursor_x = UI_OFFSET_X + 28;
    text_cursor_y = UI_OFFSET_Y + 27;
    text_print_string("99");


    await_drawing();
    PROFILER_END(2);
}

void unload_ram_banks(){

}