#ifndef UNIT_ITEM_H
#define UNIT_ITEM_H

#define UNIT_INVENTORY_SIZE 8

// The type of item it is. This will determine how the item will be handled by the program.
typedef enum {
    ITEM_EMPTY,
    ITEM_WEAPON,
    ITEM_POTION
} ITEM_TYPE;

typedef struct {
    ITEM_TYPE type;
    const char *itemName;

    // sword values
    unsigned char strength;
    unsigned char accuracy;
    
    // potion values
    int healing;
} Item;

typedef struct {
    unsigned char slots[UNIT_INVENTORY_SIZE];
} Inventory;

typedef enum {
    ITEM_ID_EMPTY, // Leave this first

    // From here, all items are tied to actual items listed in the ITEM_DATABASE.
    // Tied to the order of that database. These are just an alias for the items in there.
    // This allows for easy and clean initialization of unit inventories.
    // The order of this must be exactly like the ITEM_DATABASE.

    ITEM_ID_IRON_SWORD,
    ITEM_ID_HEALING_POTION,
    
    
    
    ITEM_ID_MAX_COUNT_END // Leave this last
} ITEM_ID;

static const Item ITEM_DATABASE[ITEM_ID_MAX_COUNT_END] = {
    { ITEM_EMPTY,  "EMPTY",       0,  0,  0 },
    { ITEM_WEAPON, "IRON SWORD", 12, 50,  0 },
    { ITEM_POTION, "POTION",      0,  0, 25 }
};

#endif
