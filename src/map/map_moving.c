#include "map_moving.h"
#include "map_defs.h"
#include "../gt/banking.h"
#include "../gen/bank_nums.h"

unsigned char node_distance[NODE_COUNT];
unsigned int node_queue[NODE_COUNT];
unsigned int node_parent[NODE_COUNT];

vector_u8b node_pos[NODE_COUNT];
unsigned char node_valid[NODE_COUNT];
unsigned char node_local_x[NODE_COUNT];
unsigned char node_local_y[NODE_COUNT];

vector_u8b current_reachable_tiles[NODE_COUNT];
unsigned char current_reachable_tiles_count;

vector_u8b target_movement_path[NODE_COUNT];
unsigned char target_movement_path_length;

#pragma code-name (push, "PROG1")
void calculate_reachable_tiles(unsigned char map_id, Unit *target_unit, Unit *unit_array){
    unsigned int i;
    unsigned int queue_front, queue_back, start_node;
    unsigned char local_x, local_y;
    int map_x, map_y;
    unsigned char movement_range = target_unit->unitStats.movementRange;

    if (movement_range > UNIT_MOVE_LIMIT) {
        movement_range = UNIT_MOVE_LIMIT;
    }

    current_reachable_tiles_count = 0;

    for (i = 0; i < NODE_COUNT; ++i) {
        local_x = (unsigned char)(i % MOVE_WINDOW_WIDTH);
        local_y = (unsigned char)(i / MOVE_WINDOW_WIDTH);

        node_local_x[i] = local_x;
        node_local_y[i] = local_y;
        node_valid[i] = 0;
        node_distance[i] = UNVISITED_TILE_ID;
        node_parent[i] = NO_PARENT;

        map_x = (int)target_unit->tile_position.x + local_x - UNIT_MOVE_LIMIT;
        map_y = (int)target_unit->tile_position.y + local_y - UNIT_MOVE_LIMIT;

        if (map_x >= 0 && map_x < MAP_WIDTH &&
            map_y >= 0 && map_y < MAP_HEIGHT) {
            node_valid[i] = 1;
            node_pos[i].x = (unsigned char)map_x;
            node_pos[i].y = (unsigned char)map_y;
        }
    }

    start_node = UNIT_MOVE_LIMIT + UNIT_MOVE_LIMIT * MOVE_WINDOW_WIDTH;

    /* Reject an out-of-map starting position. */
    if (!node_valid[start_node]) {
        return;
    }

    queue_front = 0;
    queue_back = 0;

    node_distance[start_node] = 0;
    node_parent[start_node] = NO_PARENT;
    node_queue[queue_back++] = start_node;

    current_reachable_tiles[current_reachable_tiles_count++] = node_pos[start_node];

    while (queue_front < queue_back) {
        unsigned int node;
        unsigned int next_distance;
        unsigned int x, y;
        unsigned char direction;

        node = node_queue[queue_front++];
        next_distance = (unsigned int) node_distance[node] + 1;

        if (next_distance > movement_range) {
            continue;
        }

        x = node_local_x[node];
        y = node_local_y[node];

        for (direction = 0; direction < 4; ++direction) {
            unsigned int next_node;
            unsigned char unit_on_tile_team_id;

            if (direction == 0) {
                if (x == 0){
                    continue;
                }
                next_node = node - 1;
            } 
            else if (direction == 1) {
                if (x + 1 >= MOVE_WINDOW_WIDTH){
                    continue;
                }
                next_node = node + 1;
            } 
            else if (direction == 2) {
                if (y == 0){
                    continue;
                }
                next_node = node - MOVE_WINDOW_WIDTH;
            } 
            else {
                if (y + 1 >= MOVE_WINDOW_HEIGHT){
                    continue;
                }
                next_node = node + MOVE_WINDOW_WIDTH;
            }

            if (!node_valid[next_node] ||
                node_distance[next_node] != UNVISITED_TILE_ID) {
                continue;
            }

            unit_on_tile_team_id = is_unit_on_tile(node_pos[next_node], unit_array);
            if (unit_on_tile_team_id != 0){
                // unit is on this tile
                if(unit_on_tile_team_id != target_unit->unit_team_id + 1) { // add 1 because its 0-based
                    // an enemy is occupying this tile, so don't add it to the queue
                    continue;
                }
            }

            if (!get_tile_is_passable(get_tile_from_point(map_id, node_pos[next_node]))) {
                continue;
            }

            node_distance[next_node] = (unsigned char)next_distance;
            node_parent[next_node] = node;
            node_queue[queue_back++] = next_node;

            current_reachable_tiles[current_reachable_tiles_count++] = node_pos[next_node];
        }
    }
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
void calculate_unit_path_to_tile(Unit *unit, vector_u8b destination){
    unsigned int node;
    unsigned int length = 0;
    unsigned int i;

    target_movement_path_length = 0;

    node = get_node_at_position(destination);

    if (node == NO_PARENT || node_distance[node] == UNVISITED_TILE_ID) {
        return;
    }

    while (node != NO_PARENT) {
        ++length;
        node = node_parent[node];
    }

    if (length > NODE_COUNT || length > (unsigned int)unit->unitStats.movementRange + 1) {
        return;
    }

    node = get_node_at_position(destination);

    for (i = length; i > 0; --i) {
        target_movement_path[i - 1] = node_pos[node];
        node = node_parent[node];
    }

    target_movement_path_length = (unsigned char) length;
}
#pragma code-name (pop)

// checks whether a unit is on the given tile.
// Returns with 0 if there are none. Returns with 1 or 2 if there is, and the given team ID
// of the unit.
unsigned char is_unit_on_tile(vector_u8b tile_position, Unit *unit_array){
    unsigned char i;
    for(i = 0; i < MAX_UNIT_COUNT; ++i){
        if(unit_array[i].unitJob == NULL){
            // unit is not real, skip
            continue;
        }

        if(unit_array[i].tile_position.x == tile_position.x 
            && unit_array[i].tile_position.y == tile_position.y)
        {
            // there is a unit here
            return unit_array[i].unit_team_id + 1; // adding one because 0 is no units
        }
    }

    // no units found
    return 0;
}