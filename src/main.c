#include "gt/gametank.h"
#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/input.h"
#include "camera.h"
#include "drawing.h"
#include "map.h"
//#include "gt/feature/text/text.h"
#include "cursor.h"

SpriteSlot textSlot;

void start(){
    init_graphics();
    //text_init();
    //textSlot = text_load_font();
    initialize_cursor();

    load_map_into_gram(&level_01);
    //load_drawing();
}

void update(){
    update_inputs();
    update_cursor();
}


void draw(){
    draw_level_map();
    draw_cursor();
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