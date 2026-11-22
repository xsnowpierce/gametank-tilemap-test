#ifndef UNIT_DATA_H
#define UNIT_DATA_H

#include "../units.h"

#define MAP_COUNT 1
#define MAX_UNIT_COUNT 30

const Unit game_unit_array[MAP_COUNT][MAX_UNIT_COUNT] = {
    {
    {SWORDSMAN, "JAMERO", { 1, 1, 1, 4 }, {1, 1}},
    {MAGE, "CRAS", {1,1,1, 4}, {2, 2}},
    {MAGE, "CRAS", {1,1,1, 4}, {3, 3}},
    {MAGE, "CRAS", {1,1,1, 4}, {4, 4}},
    {MAGE, "CRAS", {1,1,1, 4}, {5, 5}},
    {MAGE, "CRAS", {1,1,1, 4}, {6, 6}},
    {MAGE, "CRAS", {1,1,1, 4}, {7, 7}}
    }
};

#endif