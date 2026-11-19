#ifndef UNIT_STATS_H
#define UNIT_STATS_H

typedef struct {
    unsigned char strength;
    unsigned char speed;
    unsigned char stamina;
    unsigned char movementRange;
} Statistics;

inline unsigned char get_unit_max_health_value(Statistics *unitStats){
    return (unitStats->strength >> 1) + unitStats->stamina;
}

inline unsigned char get_unit_speed_value(Statistics *unitStats){
    return (unitStats->stamina >> 1) + unitStats->speed;
}

#endif