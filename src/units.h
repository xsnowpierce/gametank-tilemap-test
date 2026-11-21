#ifndef UNITS_H
#define UNITS_H

#include "gt/gfx/sprites.h"
#include "unit_stats.h"
#include "vector.h"

#define MAX_UNIT_COUNT 30

enum UNIT_JOB {
    NULL = 0, SWORDSMAN = 1, MAGE = 2, VAMPIRE = 3
};

typedef struct {
    enum UNIT_JOB unitJob;
    char* unitName;
    Statistics unitStats;
    vector_u8b tile_position;
    unsigned char currentQuadrant;
} Unit;

extern Unit units_array[];

void set_unit_spritesheet(SpriteSlot *slot);
void load_units_into_array(Unit units[MAX_UNIT_COUNT]);
void draw_unit_sprites_into_sram();

void draw_unit_into_sram(Unit *unit);

int get_unit_on_tile(unsigned char tile_x, unsigned char tile_y, Unit *return_unit);
char* get_job_name(enum UNIT_JOB job);

vector_u8b get_unit_sprite_point(unsigned char type);

#endif