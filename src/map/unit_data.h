#ifndef UNIT_DATA_H
#define UNIT_DATA_H

#include "../units.h"
#include "../unit_item.h"

#define MAP_COUNT 1
#define MAX_UNIT_COUNT 30

#pragma rodata-name (push, "PROG0")
const Unit game_unit_array[MAP_COUNT][MAX_UNIT_COUNT] = {
{
    {SWORDSMAN, "JAMERO", { 1, 1, 1, 4 }, { ITEM_ID_IRON_SWORD }, 0, 0, {1, 1}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 0, EQUIP_NULL, {2, 2}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 0, EQUIP_NULL, {3, 3}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 0, EQUIP_NULL, {4, 4}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 0, EQUIP_NULL, {5, 5}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 1, EQUIP_NULL, {6, 6}},
    {MAGE, "CRAS", {1,1,1, 4}, {}, 1, EQUIP_NULL, {7, 7}}
    }
};
#pragma rodata-name (pop)

#endif