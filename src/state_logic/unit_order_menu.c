#include "unit_order_menu.h"

#include "game_state.h"
#include "../map/map_tile_helper.h"
#include "unit_selected_flicker.h"
#include "../map/map_sprite_animation.h"
#include "../gt/gfx/gfx_sys.h"
#include "../gt/input.h"
#include "../map/map_tile_helper.h"
#include "../gt/feature/bittext/bittext.h"
#include "../gt/gfx/draw_direct.h"
#include "../unit_item.h"
#include "../gt/gfx/draw_queue.h"

#include "../gt/banking.h"
#include "../gen/bank_nums.h"


#include "../gt/audio/music.h"
#include "../gen/assets/sfx.h"

#define UI_OFFSET_X 1
#define UI_OFFSET_Y 8

#define TEXT_BANK QUADRANT_3 | 4

// pixel width of font, really
#define PIXELS_PER_TEXT_CHARACTER 4

void cancel_order_menu();
void preload_menu_into_vram();
void draw_unit();
void draw_order_ui();
void player_moved_menu_cursor();
void player_selected_menu_item();
static void private_update();
void update_menu_cursor_sprite();

signed char menu_cursor_selecting_index = 0;

#define SPRITE_ANIMATION_FRAMES 15
unsigned char current_sprite_index = 0;

void initialize_state_unit_order_menu(){
    // need to detect whether enemies are within our attacking range
    // if so, add attack to the list

    // have item and wait always

    // item will allow for changing the current weapon

    // wait will set them to have their turn over.

    // order menu should have a display of the current weapon selected.
    preload_menu_into_vram();
    draw_order_ui();
    menu_cursor_selecting_index = 0;
    current_sprite_index = 0;
}

void update_state_unit_order_menu(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    private_update();
    pop_rom_bank();
}

void queue_draw_state_unit_order_menu(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    draw_order_ui();
    pop_rom_bank();
}

void draw_state_unit_order_menu(){
    push_rom_bank();
    change_rom_bank(BANK_PROG1);
    draw_unit();
    pop_rom_bank();
}

#pragma code-name (push, "PROG1")
static void private_update(){
    update_unit_flickering();
    //update_map_sprite_animation();

    if(player1_new_buttons & INPUT_MASK_B){
        // cancel
        cancel_order_menu();
        return;
    }

    if(player1_new_buttons & INPUT_MASK_UP || player1_new_buttons & INPUT_MASK_DOWN){
        push_rom_bank();
        change_rom_bank(BANK_PROG1);
        player_moved_menu_cursor();
        pop_rom_bank();
        return;
    }

    if(player1_new_buttons & INPUT_MASK_A){
        push_rom_bank();
        change_rom_bank(BANK_PROG1);
        player_selected_menu_item();
        pop_rom_bank();
        return;
    }
    update_menu_cursor_sprite();
}



void update_menu_cursor_sprite(){
    static unsigned char current_frames = SPRITE_ANIMATION_FRAMES;

    current_frames--;
    if(current_frames <= 0){
        current_sprite_index ^= 1;
        current_frames = SPRITE_ANIMATION_FRAMES;
    }
}

// can probably preload the text here, 
// improve later. but im not sure if it will be a noticeable optimization.
void preload_menu_into_vram(){
    const Item *units_item = &ITEM_DATABASE[currentSelectedUnit->inventory.slots[currentSelectedUnit->equipped_inventory_slot]];
    direct_prepare_sprite_ram_array_mode(TEXT_BANK);
    bittext_set_x(0);
    bittext_set_y(112);
    bittext_write_str("ATTACK ITEM WAIT");
    bittext_set_x(0);
    bittext_set_y(120);
    bittext_write_str("            ");
    bittext_set_x(0);
    bittext_write_str(units_item->itemName);
}

void draw_unit(){
    vector_u8b draw_position;

    draw_position.x = temporary_unit_tile_position.x << 3;
    draw_position.y = temporary_unit_tile_position.y << 3;
    
    if(unit_flicker_do_draw_unit){
        direct_draw_unit_at_position(currentSelectedUnit, 
            get_current_map_frame_index(), draw_position);
        await_drawing();
    }
}

#define FIRST_POSITION_Y UI_OFFSET_Y + 3
#define SECOND_POSITION_Y UI_OFFSET_Y + 11
#define THIRD_POSITION_Y UI_OFFSET_Y + 19

#define MENU_CURSOR_X_POSITION 30
#define MENU_CURSOR_Y_STARTING_POSITION FIRST_POSITION_Y - 1

void draw_order_ui(){
    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y, 40, 28, 0, 37, uiSpriteSlot); // background
    queue_draw_sprite(UI_OFFSET_X + 3, FIRST_POSITION_Y, 23, 7, 0, 112, TEXT_BANK); // attack
    queue_draw_sprite(UI_OFFSET_X + 3, SECOND_POSITION_Y, 16, 7, 28, 112, TEXT_BANK); // item
    queue_draw_sprite(UI_OFFSET_X + 3, THIRD_POSITION_Y, 16, 7, 48, 112, TEXT_BANK); // wait

    queue_draw_sprite(UI_OFFSET_X, UI_OFFSET_Y + 30, 40, 17, 0, 65, uiSpriteSlot) // equipped item background
    queue_draw_sprite(UI_OFFSET_X + 3, UI_OFFSET_Y + 32, 34, 7, 0, 120, TEXT_BANK); // equipped item name

    // player menu cursor
    if(current_sprite_index == 0){
        queue_draw_sprite(MENU_CURSOR_X_POSITION, MENU_CURSOR_Y_STARTING_POSITION + (menu_cursor_selecting_index << 3), 8, 8, 40, 0, uiSpriteSlot);
    }else{
        queue_draw_sprite(MENU_CURSOR_X_POSITION, MENU_CURSOR_Y_STARTING_POSITION + (menu_cursor_selecting_index << 3), 8, 8, 48, 0, uiSpriteSlot);
    }
}

void player_moved_menu_cursor(){

    play_sound_effect(ASSET__sfx__cursor_move_sound_sfx_ID, 0);

    if(player1_new_buttons & INPUT_MASK_UP){
        --menu_cursor_selecting_index;
        if(menu_cursor_selecting_index < 0){
            menu_cursor_selecting_index = 2;
        }
    }

    else if(player1_new_buttons & INPUT_MASK_DOWN){
        ++menu_cursor_selecting_index;
        if(menu_cursor_selecting_index > 2){
            menu_cursor_selecting_index = 0;
        }
    }
}
#pragma code-name (pop)

void unit_finish_turn(){
    currentSelectedUnit->has_finished_turn = 1;
    currentSelectedUnit->tile_position = temporary_unit_tile_position;
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}

void cancel_order_menu(){
    revert_cursor_position_to_starting_position();
    redraw_unit_in_sram(currentSelectedUnit);
    change_game_state(CURSOR_MOVEMENT);
}

void player_selected_menu_item(){
    switch(menu_cursor_selecting_index){
        case 0:
            break;
        case 1:
            break;
        case 2:
            unit_finish_turn();
            break;
        default:
            break;
    }
}



