#include "map_moving.h"
#include "map_defs.h"
#include "../gt/banking.h"
#include "../gen/bank_nums.h"

#define MAP_WIDTH 32
#define MAP_HEIGHT 32

#define UNIT_MOVE_LIMIT 8

// choosing 17 here because 8x8, but have to add one cause of
// the centre that the unit starts from
#define MOVE_WINDOW_WIDTH 17
#define MOVE_WINDOW_HEIGHT 17

// we can technically have 255 tiles, but its unlikely.
// so we will set the max value to be the dummy value
#define UNVISITED_TILE_ID 255
// same with this
#define NO_PARENT 0xFFFFu

#define NODE_COUNT (MOVE_WINDOW_WIDTH * MOVE_WINDOW_HEIGHT)

unsigned char node_distance[NODE_COUNT];
unsigned int node_queue[NODE_COUNT];
unsigned int node_parent[NODE_COUNT];

vector_u8b node_pos[NODE_COUNT];
unsigned char node_valid[NODE_COUNT];
unsigned char node_local_x[NODE_COUNT];
unsigned char node_local_y[NODE_COUNT];


#pragma code-name (push, "PROG1")
static void add_node_to_queue(unsigned char map_id,unsigned int node, unsigned int parent,
    unsigned char next_distance, unsigned char max_steps, unsigned int *queue_back) {

    if (!node_valid[node] || node_distance[node] != UNVISITED_TILE_ID) {
        return;
    }

    if (!get_tile_is_passable(get_tile_from_point(map_id, node_pos[node]))) {
        return;
    }

    if (next_distance > max_steps) {
        return;
    }

    node_distance[node] = next_distance;
    node_parent[node] = parent;
    node_queue[*queue_back] = node;
    ++(*queue_back);
}
#pragma code-name (pop)

#pragma code-name (push, "PROG1")
static void find_reachable_tiles(unsigned char map_id, vector_u8b unit_start_position, 
    unsigned char movement_range) {
    
        unsigned int i;
    unsigned int queue_front, queue_back, start_node;
    unsigned char local_x, local_y;
    int map_x, map_y;

    // doing this so if somewhere i make a mistake and have a unit
    // with too high of a movement range, we're still safe
    if (movement_range > UNIT_MOVE_LIMIT) {
        movement_range = UNIT_MOVE_LIMIT;
    }

    for (i = 0; i < NODE_COUNT; ++i) {
        local_x = (unsigned char) i % MOVE_WINDOW_WIDTH;
        local_y = (unsigned char) i / MOVE_WINDOW_WIDTH;

        node_local_x[i] = local_x;
        node_local_y[i] = local_y;
        node_valid[i] = 0;
        node_distance[i] = UNVISITED_TILE_ID;
        node_parent[i] = NO_PARENT;

        map_x = (int) unit_start_position.x + local_x - UNIT_MOVE_LIMIT;
        map_y = (int) unit_start_position.y + local_y - UNIT_MOVE_LIMIT;

        if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT) {
            node_valid[i] = 1;
            node_pos[i].x = (unsigned char) map_x;
            node_pos[i].y = (unsigned char) map_y;
        }
    }

    queue_front = 0;
    queue_back = 0;

    start_node = UNIT_MOVE_LIMIT + UNIT_MOVE_LIMIT * MOVE_WINDOW_WIDTH;
    node_distance[start_node] = 0;
    node_parent[start_node] = NO_PARENT;
    node_queue[queue_back] = start_node;
    ++queue_back;

    while (queue_front < queue_back) {
        unsigned int node, next_distance, x, y;

        node = node_queue[queue_front];
        ++queue_front;

        next_distance = node_distance[node] + 1;
        if (next_distance > movement_range) {
            continue;
        }

        x = node_local_x[node];
        y = node_local_y[node];

        if (x > 0) {
            add_node_to_queue(map_id, node - 1, node, next_distance, movement_range, &queue_back);
        }
        if (x + 1 < MOVE_WINDOW_WIDTH) {
            add_node_to_queue(map_id, node + 1, node, next_distance,movement_range, &queue_back);
        }
        if (y > 0) {
            add_node_to_queue(map_id, node - MOVE_WINDOW_WIDTH, node, next_distance, movement_range, &queue_back);
        }
        if (y + 1 < MOVE_WINDOW_HEIGHT) {
            add_node_to_queue(map_id, node + MOVE_WINDOW_WIDTH, node, next_distance,movement_range, &queue_back);
        }
    }
}
#pragma code-name (pop)

#pragma code-name (push, "PROG1")
static unsigned int get_reachable_tiles(vector_u8b *out_tiles) {
    unsigned int i;
    unsigned int count = 0;

    for (i = 0; i < NODE_COUNT; ++i) {
        if (node_valid[i] && node_distance[i] != UNVISITED_TILE_ID) {
            out_tiles[count] = node_pos[i];
            ++count;
        }
    }

    return count;
}
#pragma code-name (pop)

#pragma code-name (push, "PROG1")
static unsigned int get_node_at_position(vector_u8b position) {
    unsigned int i;

    for (i = 0; i < NODE_COUNT; ++i) {
        if (node_valid[i] &&
            node_pos[i].x == position.x &&
            node_pos[i].y == position.y) {
            return i;
        }
    }

    return NO_PARENT;
}
#pragma code-name (pop)

#pragma code-name (push, "PROG1")
static unsigned char get_path(vector_u8b destination, vector_u8b *out_path, unsigned char out_capacity) {
    unsigned int node;
    unsigned int length = 0;
    unsigned int i;

    node = get_node_at_position(destination);

    if (node == NO_PARENT || node_distance[node] == UNVISITED_TILE_ID) {
        return 0;
    }

    while (node != NO_PARENT) {
        ++length;
        node = node_parent[node];
    }

    if (length > out_capacity) {
        return 0;
    }

    node = get_node_at_position(destination);

    for (i = length; i > 0; --i) {
        out_path[i - 1] = node_pos[node];
        node = node_parent[node];
    }

    return (unsigned char) length;
}
#pragma code-name (pop)

unsigned int get_unit_reachable_tiles(unsigned char map_id, vector_u8b unit_position,
    unsigned char unit_movement_range, vector_u8b *out) {

    unsigned int value = 0;

    push_rom_bank();
    change_rom_bank(BANK_PROG1);

    find_reachable_tiles(map_id, unit_position, unit_movement_range);
    value = get_reachable_tiles(out);

    pop_rom_bank();
    return value;
}

unsigned char get_unit_path_to_tile(unsigned char map_id, vector_u8b unit_position, vector_u8b destination,
    unsigned char unit_movement_range, vector_u8b *out_path) {
    
    unsigned char path_length;

    push_rom_bank();
    change_rom_bank(BANK_PROG1);

    find_reachable_tiles(map_id, unit_position, unit_movement_range);
    path_length = get_path(destination, out_path, unit_movement_range + 1);

    pop_rom_bank();
    return path_length;
}
