#include "unit_summary_menu.h"

#include "../gt/gfx/draw_direct.h"
#include "../gt/gfx/draw_queue.h"
#include "../units.h"
#include "game_state.h"
#include "../cursor.h"
#include "../gt/feature/bittext/bittext.h"
#include "../gt/input.h"
#include "../map/map_tile_helper.h"
#include "../gt/gfx/draw_queue.h"

#include "../gt/banking.h"
#include "../gen/bank_nums.h"
#include "unit_selected_flicker.h"


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

static unsigned char current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
static unsigned char current_animation_frame = 0;

static void draw_unit_information();
static void print_unit_information_into_gram();
static void cancel_selecting_unit();

void initialize_state_unit_summary_menu(){

    push_rom_bank();
    change_rom_bank(BANK_PROG0);
    print_unit_information_into_gram();
    pop_rom_bank();

    // replace the tile the unit is on in sram with the blank tile
    // because we are going to draw it as an actual sprite (not linked to tilemap) 
    // since its selected now.
    redraw_tile_in_sram(currentSelectedUnit->tile_position, 
        currentSelectedUnit->currentQuadrant);
}

void update_state_unit_summary_menu(){
    --current_unit_animation_frame_tick;
    if(current_unit_animation_frame_tick <= 0){
        current_animation_frame ^= 1;
        current_unit_animation_frame_tick = WALKING_SPRITE_ANIMATION_FRAME_LENGTH;
    }

    update_cursor_animation();

    // if player moves the cursor then exit the menu
    if(player1_new_buttons & INPUT_MASK_A || player1_new_buttons & INPUT_MASK_ANY_DIRECTION)
    {
        change_game_state(CHOOSING_MOVEMENT_PATH);
        return;
    }

    else if(player1_new_buttons & INPUT_MASK_B){
        // cancel out of menu
        cancel_selecting_unit();
        return;
    }
}

void queue_draw_state_unit_summary_menu(){
    if(unit_flicker_do_draw_unit){
        draw_cursor_selecting();
    }
    draw_unit_information();
}

void draw_state_unit_summary_menu(){
    if(unit_flicker_do_draw_unit){
        direct_draw_unit(currentSelectedUnit, 3 + current_animation_frame);
        await_drawing();
    }
}

#pragma code-name (push, "PROG0")
void print_unit_information_into_gram(){
    char i;

    //direct_prepare_sprite_mode(TEXT_BANK);
    

    // now draw onto this somehow
    direct_prepare_sprite_ram_array_mode(TEXT_BANK);
    
    // draw the units name
    bittext_set_x(0);
    bittext_set_y(0);
    bittext_write_str("      ");
    bittext_set_x(0);
    //bittext_set_y(0);
    bittext_write_str(currentSelectedUnit->unitName);

    // draw the job name
    bittext_set_x(0);
    bittext_set_y(8);
    bittext_write_str("         ");
    bittext_set_x(0);
    //bittext_set_y(8);
    bittext_write_str(get_job_name(currentSelectedUnit->unitJob));

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
#pragma code-name (pop)

static void draw_unit_information(){
    // TODO: make it so that if the cursor/unit is blocked by the UI area,
    // render the screen on the right side instead.
    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 37, 0, 0, uiSpriteSlot);
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 3, UNIT_NAME_PIXEL_WIDTH, 8, 0, 0, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 11, JOB_NAME_PIXEL_WIDTH, 8, 0, 8, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 14, UI_OFFSET_Y + 26, HEALTH_PIXEL_WIDTH, 8, 0, 16, TEXT_BANK);
    queue_draw_sprite(UI_OFFSET_X + 28, UI_OFFSET_Y + 26, HEALTH_PIXEL_WIDTH, 8, HEALTH_PIXEL_WIDTH, 16, TEXT_BANK);
}

static void cancel_selecting_unit(){
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}