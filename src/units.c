#include "units.h"
#include "gt/banking.h"
#include "gt/gfx/draw_direct.h"
#include "gt/gfx/draw_queue.h"
#include "camera.h"
#include "gt/gfx/gfx_sys.h"
#include "vector.h"

#include "gen/bank_nums.h"

#define TILE_SIZE 8
#define TILES_ON_SCREEN 16

//static void draw_unit(Unit *unit, unsigned char spriteFrame);
void draw_unit_into_sram(Unit *unit);

#define spriteSheetBank QUADRANT_0 | 0

void draw_unit_sprites_into_sram(Unit *unit_array, unsigned char array_size){
    char i = 0;
    Unit *unit;
    
    for(i = 0; i < array_size; ++i){
        unit = &unit_array[i];

        if(unit->unitJob == NULL){
            continue;
        }

        push_rom_bank();
        change_rom_bank(BANK_PROG0);
        draw_unit_into_sram(unit);
        pop_rom_bank();
    }
}

#pragma code-name (push, "PROG0")
void private_draw_unit_into_sram(Unit *unit){
    char i, j;
    vector_u8b spritePosition;
    unsigned char tile_pixels[TILE_SIZE << 3];
    unsigned int target_x = unit->tile_position.x << 3, target_y = unit->tile_position.y << 3;


    spritePosition = get_unit_sprite_point(unit->unitJob, unit->unit_team_id);

    if(unit->tile_position.x < 16 && unit->tile_position.y < 16){
        unit->currentQuadrant = QUADRANT_3;
    }
    else if(unit->tile_position.x >= 16 && unit->tile_position.y < 16){
        target_x -= (16 << 3);
        //target_y -= (16 << 3);
        unit->currentQuadrant = QUADRANT_2;
    }
    else if(unit->tile_position.x < 16 && unit->tile_position.y >= 16){
        //target_x -= (16 << 3);
        target_y -= (16 << 3);
        unit->currentQuadrant = QUADRANT_1;
    }
    else{
        target_x -= (16 << 3);
        target_y -= (16 << 3);
        unit->currentQuadrant = QUADRANT_0;
    }

    // for sprite 0
    direct_prepare_sprite_ram_array_mode(spriteSheetBank);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int source_row = ((spritePosition.y + i) << 7) + spritePosition.x;
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[tile_row + j] = vram[source_row + j];
        }
    }

    direct_prepare_sprite_ram_array_mode(unit->currentQuadrant | 7);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int target_row = ((target_y + i) << 7) + target_x;
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            if(tile_pixels[tile_row + j] != 0x00){
                vram[target_row + j] = tile_pixels[tile_row + j];
            }
        }
    }

    // for sprite 1
    direct_prepare_sprite_ram_array_mode(spriteSheetBank);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int source_row = ((spritePosition.y + i) << 7) + spritePosition.x + (TILE_SIZE);
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[tile_row + j] = vram[source_row + j];
        }
    }

    direct_prepare_sprite_ram_array_mode(unit->currentQuadrant | 6);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int target_row = ((target_y + i) << 7) + target_x;
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            if(tile_pixels[tile_row + j] != 0x00){
                vram[target_row + j] = tile_pixels[tile_row + j];
            }
        }
    }

    // for sprite 2
    direct_prepare_sprite_ram_array_mode(spriteSheetBank);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int source_row = ((spritePosition.y + i) << 7) + spritePosition.x + (16);
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            tile_pixels[tile_row + j] = vram[source_row + j];
        }
    }

    direct_prepare_sprite_ram_array_mode(unit->currentQuadrant | 5);
    for (i = 0; i < TILE_SIZE; ++i) {
        unsigned int target_row = ((target_y + i) << 7) + target_x;
        unsigned int tile_row = i << 3;

        for (j = 0; j < TILE_SIZE; ++j) {
            if(tile_pixels[tile_row + j] != 0x00){
                vram[target_row + j] = tile_pixels[tile_row + j];
            }
        }
    }
}

#pragma code-name (pop)

void draw_unit_into_sram(Unit *unit){
    push_rom_bank();
    change_rom_bank(BANK_PROG0);
    private_draw_unit_into_sram(unit);
    pop_rom_bank();
}

void direct_draw_unit(Unit *unit, unsigned char spriteFrame){
    vector_u8b spritePosition;
    unsigned char animationOffset = 0;

    if (unit->unitJob == NULL)
        return;

    animationOffset = spriteFrame << 3;

    spritePosition = get_unit_sprite_point(unit->unitJob, unit->unit_team_id);
    direct_prepare_sprite_mode(spriteSheetBank);
    DIRECT_DRAW_SPRITE((unit->tile_position.x << 3) - camera_x, (unit->tile_position.y << 3) - camera_y, 
        TILE_SIZE, TILE_SIZE, spritePosition.x + animationOffset, spritePosition.y);
}

void direct_draw_unit_at_position(Unit *unit, unsigned char spriteFrame, vector_u8b position){
    vector_u8b spritePosition;
    unsigned char animationOffset = 0;

    if (unit->unitJob == NULL)
        return;

    animationOffset = spriteFrame << 3;

    spritePosition = get_unit_sprite_point(unit->unitJob, unit->unit_team_id);
    direct_prepare_sprite_mode(spriteSheetBank);
    DIRECT_DRAW_SPRITE(position.x - camera_x, position.y - camera_y, 
        TILE_SIZE, TILE_SIZE, spritePosition.x + animationOffset, spritePosition.y);
}

vector_u8b get_unit_sprite_point(enum UNIT_JOB type, unsigned char team_id){
    vector_u8b return_vector;

    switch(type){
        case SWORDSMAN:
            return_vector.x = 0;
            return_vector.y = 8;
            break;

        case MAGE:
            return_vector.x = 0;
            return_vector.y = 24;
            break;
        
        case VAMPIRE:
            return_vector.x = 0;
            return_vector.y = 40;
            break;

        default:
            return_vector.x = 0;
            return_vector.y = 0;
            break;
    }

    if(team_id == 1){
        return_vector.y += 8;
    }

    return return_vector;
}

char* get_job_name(enum UNIT_JOB job){
    switch(job){
        case SWORDSMAN:
            return "BLADE";
        case MAGE:
            return "MAGE";
        case VAMPIRE:
            return "BLOOD";
        default:
            return "NULL";
    }
}
