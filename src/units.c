#include "units.h"
#include "gt/gfx/draw_queue.h"
#include "camera.h"
#include "vector.h"

#define TILE_SIZE 8
#define TILES_ON_SCREEN 16

#define SPRITE_ANIMATION_FRAME_TIME 10
#define SPRITE_ANIMATION_MAX_FRAME 2

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

void update_unit_cache(){
    unsigned char camera_tile_x = camera_x / TILE_SIZE, camera_tile_y = camera_y / TILE_SIZE;
    unsigned char camera_furthest_right = camera_tile_x + TILES_ON_SCREEN - 1, camera_furthest_down = camera_tile_y + TILES_ON_SCREEN - 1;
    unsigned char i;

    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        if(units_array[i].unitType != NULL){
            
            // check if the unit is on screen to be rendered
            if(units_array[i].tile_position.x < camera_tile_x || units_array[i].tile_position.y < camera_tile_y || units_array[i].tile_position.x > camera_furthest_right || units_array[i].tile_position.y > camera_furthest_down){
                units_array[i].is_on_screen = 0;
            }
            else{
                units_array[i].is_on_screen = 1;
            }
        }
    }
}

void update_unit_animation() {
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

    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        draw_unit(&units_array[i], current_sprite_frame_index);
    }
}

void draw_unit(Unit *unit, char spriteFrame){
    vector_u8b spritePosition;
    char animationOffset;

    if(unit->is_on_screen){
        if(unit->do_animation){
            animationOffset = spriteFrame * TILE_SIZE;
        }
        spritePosition = get_unit_sprite_point(unit->unitType);
        queue_draw_sprite((unit->tile_position.x * TILE_SIZE) - camera_x, (unit->tile_position.y * TILE_SIZE) - camera_y, TILE_SIZE, TILE_SIZE, spritePosition.x + animationOffset, spritePosition.y, *spriteSheet);
    }
}

vector_u8b get_unit_sprite_point(char type){
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

        default:
            return_vector.x = 0;
            return_vector.y = 0;
            break;
    }

    return return_vector;
}
