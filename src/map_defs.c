#include "map_defs.h"
#include "map_data.h"

#include "gt/banking.h" //Banking API
#include "gen/bank_nums.h"

const unsigned char* get_map_from_id(char map_id){
    const unsigned char* target_map_array;
    push_rom_bank();
    change_rom_bank(BANK_PROG0);

    target_map_array = game_level_array[map_id];

    pop_rom_bank();

    return target_map_array;
}


static unsigned char get_tile_from_point(unsigned char map_id, vector_u8b point){
    unsigned char return_value;


    return_value = get_map_from_id(map_id)[(point.y << 5) + point.x];
    
    //level->TILE_DATA[point.y * level->MAP_WIDTH + point.x];

    return return_value;
}