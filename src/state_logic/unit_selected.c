#include "unit_selected.h"
#include "../gt/gfx/draw_direct.h"
#include "../gt/gfx/draw_queue.h"
#include "../units.h"
#include "../map/map_moving.h"
#include "game_state.h"
#include "../camera.h"
#include "../cursor.h"
#include "../gt/feature/bittext/bittext.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

#define TEXT_BANK QUADRANT_3 | 6

//#define PROFILER_START(x) ((char*) 0x2800)[0] = 0x80; ((char*) 0x2800)[0] = x;
//#define PROFILER_END(x) ((char*) 0x2800)[0] = 0x80; ((char*) 0x2800)[0] = x | 0x40;

Unit selectedUnit;
SpriteSlot uiSpriteSlot;

vector_u8b cursor_starting_position;
unsigned char player_moved_cursor = 0;

vector_u8b unit_reachable_tiles;

void draw_unit_information();
void print_unit_information_into_gram();

void initialize_state_unit_selected(){
    PROFILER_START(3);
    print_unit_information_into_gram();
    PROFILER_END(3);
    cursor_starting_position.x = cursor_tile_position_x;
    cursor_starting_position.y = cursor_tile_position_y;
    player_moved_cursor = 0;

    
    unit_reachable_tiles = get_unit_reachable_tiles(current_map_id, selectedUnit.tile_position, selectedUnit.unitStats.movementRange);

    //find_reachable_tiles(current_map_id, selectedUnit.tile_position, selectedUnit.unitStats.movementRange);
    //get_reachable_tiles(out_tiles);
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
    // now draw onto this somehow
    direct_prepare_sprite_ram_array_mode(TEXT_BANK);
    bittext_set_x(0);
    bittext_set_y(0);
    bittext_write_str(selectedUnit.unitName);
}

// pixel width of font, really
#define PIXELS_PER_TEXT_CHARACTER 4

// user specified definitions
#define UNIT_NAME_MAX_CHARACTERS 6

// macros that should be auto defined
#define NAME_PIXEL_WIDTH (UNIT_NAME_MAX_CHARACTERS * PIXELS_PER_TEXT_CHARACTER)

void draw_unit_information(){
    PROFILER_START(1);
    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0, uiSpriteSlot);
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 3, NAME_PIXEL_WIDTH, 8, 0, 0, TEXT_BANK);
    PROFILER_END(1);
}