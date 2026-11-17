#include "map_defs.h"
#include "map_data.h"

#include "gt/banking.h" //Banking API
#include "gen/bank_nums.h"

const MapLevel* get_map_from_id(char id){
    return &game_level_array[id];
}


static unsigned char get_tile_from_point(unsigned char map_id, vector_u8b point){
    unsigned char return_value;
    const MapLevel* target_level;

    push_rom_bank();
    change_rom_bank(BANK_PROG0);

    target_level = &game_level_array[map_id];
    return_value = target_level->TILE_DATA[point.y * target_level->MAP_WIDTH + point.x];
    
    //level->TILE_DATA[point.y * level->MAP_WIDTH + point.x];

    pop_rom_bank();
    return return_value;
}