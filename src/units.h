#ifndef UNITS_H
#define UNITS_H

#include "gt/gfx/sprites.h"
#include "unit_stats.h"
#include "vector.h"

#define MAX_UNIT_COUNT 18

enum UNIT_JOB {
    NULL = 0, SWORDSMAN = 1, MAGE = 2
};

typedef struct {
    enum UNIT_JOB unitJob;
    char* unitName;
    Statistics unitStats;
    vector_u8b tile_position;
    char is_on_screen;
    char do_animation;
} Unit;

extern Unit units_array[];

void set_unit_spritesheet(SpriteSlot *slot);
void load_units_into_array(Unit units[MAX_UNIT_COUNT]);
void update_unit_cache();
void draw_visible_units();
void draw_unit(Unit *unit, char spriteFrame);
void update_unit_animation();
int get_unit_on_tile(char tile_x, char tile_y, Unit *return_unit);
char* get_job_name(enum UNIT_JOB job);

vector_u8b get_unit_sprite_point(char type);

#endif