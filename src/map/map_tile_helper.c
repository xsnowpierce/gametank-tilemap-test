#include "map_tile_helper.h"

#include "map_drawing.h"

#include "../gt/banking.h"
#include "../gen/bank_nums.h"

#include "../units.h"

void redraw_tile_in_sram(vector_u8b tile_position, unsigned char target_quadrant){
    push_rom_bank();
    change_rom_bank(BANK_PROG0);
    redraw_tile(tile_position.x, tile_position.y, target_quadrant);
    pop_rom_bank();
}

void redraw_unit_in_sram(Unit *unit){
    draw_unit_into_sram(unit);
}