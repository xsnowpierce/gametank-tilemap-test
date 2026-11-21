#include "unit_selected.h"
#include "../gt/gfx/draw_direct.h"
#include "../gt/gfx/draw_queue.h"
#include "../units.h"
#include "../map/map_moving.h"
#include "game_state.h"
#include "../camera.h"
#include "../cursor.h"
#include "../gt/feature/bittext/bittext.h"
#include "../map/map_sprite_animation.h"
#include "../gt/input.h"
#include "../map/map_tile_helper.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

#define TEXT_BANK QUADRANT_3 | 4

// pixel width of font, really
#define PIXELS_PER_TEXT_CHARACTER 4

// user specified definitions
#define UNIT_NAME_MAX_CHARACTERS 6
#define JOB_NAME_MAX_CHARACTERS 9
#define HEALTH_MAX_CHARACTERS 2

// macros that should be auto defined
#define UNIT_NAME_PIXEL_WIDTH (UNIT_NAME_MAX_CHARACTERS * PIXELS_PER_TEXT_CHARACTER)
#define JOB_NAME_PIXEL_WIDTH (JOB_NAME_MAX_CHARACTERS * PIXELS_PER_TEXT_CHARACTER)
#define HEALTH_PIXEL_WIDTH (HEALTH_MAX_CHARACTERS * PIXELS_PER_TEXT_CHARACTER)


enum PROGRESS_STATE { IN_SUMMARY_MENU, MOVING_CURSOR };
enum PROGRESS_STATE currentProgressionState;

Unit selectedUnit;
SpriteSlot uiSpriteSlot;

vector_u8b cursor_starting_position;

vector_u8b unit_reachable_tiles;
unsigned char unit_reachable_tiles_count;

void draw_unit_information();
void print_unit_information_into_gram();

void initialize_state_unit_selected(){
    PROFILER_START(1);
    print_unit_information_into_gram();
    PROFILER_END(1);

    cursor_starting_position.x = cursor_tile_position_x;
    cursor_starting_position.y = cursor_tile_position_y;
    
    PROFILER_START(2);
    unit_reachable_tiles_count = get_unit_reachable_tiles(current_map_id, selectedUnit.tile_position, selectedUnit.unitStats.movementRange, &unit_reachable_tiles);
    PROFILER_END(2);

    // now i need to take the unit off of the sram and replace that with a tile.
    // create a helper for it in maybe a new file to lighten the includes?
    redraw_tile_in_sram(selectedUnit.tile_position, selectedUnit.currentQuadrant);

    // start drawing unit as a proper sprite, not linked to the tilemap

    currentProgressionState = IN_SUMMARY_MENU;
}

void update_state_unit_selected(){
    update_cursor();
    
    if(currentProgressionState == IN_SUMMARY_MENU){
        // check if cursor has moved from the starting position yet
        if(player1_buttons & INPUT_MASK_A || player1_buttons & INPUT_MASK_ANY_DIRECTION){
            currentProgressionState = MOVING_CURSOR;
        }
    }
    else{
        update_map_sprite_animation();
        update_camera();
        cursor_update_locked_movement(&unit_reachable_tiles, unit_reachable_tiles_count, selectedUnit.tile_position);
    }
}

void queue_draw_state_unit_selected(){
    // before we draw the visible units:
    // we should check to see if we are IN_SUMMARY_MENU.
    // We can set the selected unit to be "invisible" so they will not be drawn.
    if(currentProgressionState == IN_SUMMARY_MENU){
        draw_cursor();
        draw_unit_information();
    }else{
        draw_cursor();
    }
}

void draw_state_unit_selected(){
    
}

void print_unit_information_into_gram(){
    char i;
    // now draw onto this somehow
    direct_prepare_sprite_ram_array_mode(TEXT_BANK);
    
    // draw the units name
    bittext_set_x(0);
    bittext_set_y(0);
    for(i = 0; i < UNIT_NAME_MAX_CHARACTERS; ++i){
        bittext_draw_char(' ');
    }
    bittext_set_x(0);
    //bittext_set_y(0);
    bittext_write_str(selectedUnit.unitName);

    // draw the job name
    bittext_set_x(0);
    bittext_set_y(8);
    for(i = 0; i < JOB_NAME_MAX_CHARACTERS; ++i){
        bittext_draw_char(' ');
    }
    bittext_set_x(0);
    //bittext_set_y(8);
    bittext_write_str(get_job_name(selectedUnit.unitJob));

    // draw the health
    bittext_set_x(0);
    bittext_set_y(16);
    for(i = 0; i < HEALTH_MAX_CHARACTERS; ++i){
        bittext_draw_char(' ');
    }
    bittext_set_x(0);
    //bittext_set_y(8);
    bittext_write_str("1");
    bittext_write_str("2");
    bittext_write_str("3");
    bittext_write_str("4");
}



void draw_unit_information(){
    PROFILER_START(1);
    // TODO: make it so that if the cursor/unit is blocked by the UI area,
    // render the screen on the right side instead.
    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0, uiSpriteSlot);
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 3, UNIT_NAME_PIXEL_WIDTH, 8, 0, 0, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 11, JOB_NAME_PIXEL_WIDTH, 8, 0, 8, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 14, UI_OFFSET_Y + 26, HEALTH_PIXEL_WIDTH, 8, 0, 16, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 28, UI_OFFSET_Y + 26, HEALTH_PIXEL_WIDTH, 8, HEALTH_PIXEL_WIDTH, 16, TEXT_BANK);
    
    PROFILER_END(1);
}