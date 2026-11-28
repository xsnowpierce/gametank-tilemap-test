#ifndef UNITS_H
#define UNITS_H

#include "gt/gfx/sprites.h"
#include "unit_stats.h"
#include "vector.h"
#include "unit_item.h"

#define MAX_UNIT_COUNT 30
#define EQUIP_NULL 255

enum UNIT_JOB {
    NULL = 0, SWORDSMAN = 1, MAGE = 2, VAMPIRE = 3
};

typedef struct {
    // UNIT INFORMATION
    enum UNIT_JOB unitJob;
    const char* unitName;
    Statistics unitStats;

    /*
    
    */
    Inventory inventory;
    /*
    The current equpped slot ID from the inventory.
    255 or EQUIP_NULL is the equivalent of nothing being equipped.
    In normal operation, it should be a number between 0 and 7, as per UNIT_INVENTORY_SIZE
    */
    unsigned char equipped_inventory_slot;

    unsigned char unit_team_id;

    // UNIT PROGRAMMING
    vector_u8b tile_position;

    // SYSTEM VALUES
    unsigned char currentQuadrant;
    unsigned char has_finished_turn;
} Unit;

void draw_unit_sprites_into_sram(Unit* unit_array, unsigned char array_size);

void draw_unit_into_sram(Unit *unit);
void direct_draw_unit(Unit *unit, unsigned char spriteFrame);
void direct_draw_unit_at_position(Unit *unit, unsigned char spriteFrame, vector_u8b position);

Unit* get_unit_on_tile(unsigned char tile_x, unsigned char tile_y);
char* get_job_name(enum UNIT_JOB job);

vector_u8b get_unit_sprite_point(enum UNIT_JOB type, unsigned char team_id);

#endif