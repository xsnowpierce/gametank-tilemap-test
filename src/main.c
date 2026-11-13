#include "gt/gfx/draw_queue.h"
#include "gt/gfx/gfx_sys.h"
#include "gt/input.h"
#include "camera.h"
#include "drawing.h"

int main () {

    init_graphics();

    await_drawing();
    await_draw_queue();

    load_drawing();

    while (1) {
        queue_clear_screen(3);

        //draw_map(13, 10, 0, 0);
        draw();
        
        queue_clear_border(0);

        update_inputs();

        if(player1_buttons & INPUT_MASK_LEFT) {
            camera_x += 1;
        }

        else if(player1_buttons & INPUT_MASK_RIGHT){
            camera_x -= 1;
        }

        if(player1_buttons & INPUT_MASK_UP){
            camera_y += 1;
        }
        else if(player1_buttons & INPUT_MASK_DOWN){
            camera_y -= 1;
        }

        await_draw_queue();
        await_vsync(1);
        flip_pages(); 
    }
    return 0;
}