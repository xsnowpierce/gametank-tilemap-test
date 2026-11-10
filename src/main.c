#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "map_drawing.h"
#include "gt/input.h"
#include "camera.h"

int main () {

    init_graphics();
    load_map();


    while (1) {
        queue_clear_screen(3);

        draw_map(17, 11, 0, 4);
        
        queue_clear_border(0);

        update_inputs();

        if(player1_buttons & INPUT_MASK_A) {
            camera_x += 1;
        }
        else if(player1_buttons & INPUT_MASK_B){
            camera_x -= 1;
        }

        if(camera_x < 0){
            camera_x = 0;
        }

        await_draw_queue();
        await_vsync(1);
        flip_pages(); 
    }
    return 0;
}