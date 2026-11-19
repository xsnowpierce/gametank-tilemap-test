#include "units.h"
#include "gt/gfx/draw_direct.h"
#include "gt/gfx/draw_queue.h"
#include "camera.h"
#include "vector.h"

#define TILE_SIZE 8
#define TILES_ON_SCREEN 16

#define SPRITE_ANIMATION_FRAME_TIME 10
#define SPRITE_ANIMATION_MAX_FRAME 2

static void draw_unit(Unit *unit, unsigned char spriteFrame);

SpriteSlot *spriteSheet;
Unit units_array[MAX_UNIT_COUNT];

char current_sprite_frame_index = 0;
char current_sprite_animation_counter = 0;
char sprite_animation_ascending = 0;

void set_unit_spritesheet(SpriteSlot *slot){
    spriteSheet = slot;
}

void load_units_into_array(Unit units[MAX_UNIT_COUNT]){
    char i = 0;
    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        units_array[i] = units[i];
    }
}

/*
void update_unit_cache(){
    unsigned char left = camera_x >> 3;
    unsigned char top = camera_y >> 3;
    unsigned char right = left + 15;
    unsigned char bottom = top + 15;
    unsigned char i;
    return;

    for (i = 0; i < MAX_UNIT_COUNT; ++i) {
        Unit *unit = &units_array[i];

        if (unit->unitJob == NULL) {
            unit->is_on_screen = 0;
            continue;
        }

        unit->is_on_screen = unit->tile_position.x >= left && unit->tile_position.x <= right &&
            unit->tile_position.y >= top && unit->tile_position.y <= bottom;
    }
}
*/

void update_unit_animation(){
    ++current_sprite_animation_counter;

    if (current_sprite_animation_counter >= SPRITE_ANIMATION_FRAME_TIME) {
        current_sprite_animation_counter = 0;

        if (sprite_animation_ascending) {
            if (current_sprite_frame_index >= SPRITE_ANIMATION_MAX_FRAME) {
                sprite_animation_ascending = 0;
            } else {
                ++current_sprite_frame_index;
            }
        } else {
            if (current_sprite_frame_index <= 0) {
                sprite_animation_ascending = 1;
            } else {
                --current_sprite_frame_index;
            }
        }
    }
}


void draw_visible_units(){
    unsigned char i;

    __asm__("SEI");
    direct_prepare_sprite_mode(*spriteSheet);
    for (i = 0; i < MAX_UNIT_COUNT; ++i) {
        draw_unit(&units_array[i], current_sprite_frame_index);
    }
    __asm__("CLI");
}

void draw_visible_units_at_frame(unsigned char target_frame){
    unsigned char i;
    __asm__("SEI");
    direct_prepare_sprite_mode(*spriteSheet);
    for (i = 0; i < MAX_UNIT_COUNT; ++i) {
        draw_unit(&units_array[i], target_frame);
    }

    __asm__("CLI");
}

void force_draw_target_unit(Unit *unit){
    direct_prepare_sprite_mode(*spriteSheet);
    draw_unit(unit, current_sprite_frame_index);
}

static void draw_unit(Unit *unit, unsigned char spriteFrame){
    vector_u8b spritePosition;
    unsigned char animationOffset = 0;

    if (unit->unitJob == NULL)
        return;

    if (unit->do_animation)
        animationOffset = spriteFrame << 3;

    spritePosition = get_unit_sprite_point(unit->unitJob);
    DIRECT_DRAW_SPRITE((unit->tile_position.x << 3) - camera_x, (unit->tile_position.y << 3) - camera_y, 
        TILE_SIZE, TILE_SIZE, spritePosition.x + animationOffset, spritePosition.y);
}

int get_unit_on_tile(unsigned char tile_x, unsigned char tile_y, Unit *return_unit){
    unsigned char i = 0;
    
    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        if(units_array[i].tile_position.x != tile_x){
            continue;
        }

        if(units_array[i].tile_position.y != tile_y){
            continue;
        }

        *return_unit = units_array[i];
        return 1;
    } 

    return 0;
}

vector_u8b get_unit_sprite_point(unsigned char type){
    vector_u8b return_vector;

    switch(type){
        case SWORDSMAN:
            return_vector.x = 0;
            return_vector.y = 8;
            break;

        case MAGE:
            return_vector.x = 0;
            return_vector.y = 16;
            break;
        
        case VAMPIRE:
            return_vector.x = 0;
            return_vector.y = 24;
            break;

        default:
            return_vector.x = 0;
            return_vector.y = 0;
            break;
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
