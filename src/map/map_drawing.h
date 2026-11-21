#ifndef MAP_DRAWING_H
#define MAP_DRAWING_H

int load_map_id(unsigned char map_id);
void draw_level_map();
void redraw_tile(unsigned char tile_x, unsigned char tile_y, unsigned char target_quadrant);

#endif