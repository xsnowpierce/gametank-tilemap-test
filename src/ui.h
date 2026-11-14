#ifndef UI_H
#define UI_H

#include "map_defs.h"
void initialize_ui();
void update_ui();
void draw_ui();
void ui_draw_hovered_tile(MapLevel *level);
void draw_camera_and_cursor_position();

#endif