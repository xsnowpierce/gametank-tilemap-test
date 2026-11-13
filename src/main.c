#include "gt/gametank.h"
#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/input.h"
#include "camera.h"
#include "drawing.h"
#include "map.h"
#include "cursor.h"
#include "ui.h"


void start(){
    init_graphics();
    initialize_cursor();
    initialize_ui();

    load_map_into_gram(&level_01);
}

void update(){
    update_inputs();
    update_cursor();
    update_ui();
}


void draw(){
    draw_level_map();
    draw_cursor();
    draw_ui();
}


int main () {
    start();
    
    while (1) {
        queue_clear_screen(3);
        
        update();

        draw();
        
        queue_clear_border(0);
        await_draw_queue();
        await_vsync(1);
        flip_pages(); 
    }
    return 0;
}