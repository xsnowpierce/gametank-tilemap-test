#include "map_defs.h"
#include "map_data.h"

#include "../gt/banking.h" //Banking API
#include "../gen/bank_nums.h"

const unsigned char* get_map_from_id(unsigned char map_id){
    const unsigned char* target_map_array;
    push_rom_bank();
    change_rom_bank(BANK_PROG0);

    target_map_array = game_level_array[map_id];

    pop_rom_bank();

    return target_map_array;
}


enum TILE get_tile_from_point(unsigned char map_id, vector_u8b point){
    unsigned char return_value;

    return_value = get_map_from_id(map_id)[(point.y << 5) + point.x] - 1;
    
    //level->TILE_DATA[point.y * level->MAP_WIDTH + point.x];

    return return_value;
}


const char * get_tile_name_from_id(enum TILE tile_id){
    switch(tile_id){
        case TILE_BLACK:
            return "VOID";
        case TILE_GRASS:
            return "GRASS";
        case TILE_DIRT:
            return "DIRT";
        case TILE_BUSH:
            return "BUSH";
        case TILE_TREE:
            return "TREE";
        case TILE_WATER:
            return "WATER";
        case TILE_TALL_GRASS:
            return "GRASS";
        case TILE_FLOWER_GRASS:
            return "GRASS";
        case TILE_MOUNTAIN:
            return "HEIGHT";
        default:
            return "NULL";
    }
}


unsigned char get_tile_is_passable(enum TILE tile_id){
    switch(tile_id){
        case TILE_BLACK:
            return 0;
        case TILE_TREE:
            return 0;
        case TILE_MOUNTAIN:
            return 0;
        default:
            return 1;
    }
}
