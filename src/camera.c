#include "camera.h"

#define CAMERA_MOVE_TIME 8

unsigned int camera_x = 0, camera_y = 0;

char camera_is_moving = 0;

unsigned int target_camera_x = 0, target_camera_y = 0;
static int start_camera_x, start_camera_y;

static unsigned int move_duration;
static unsigned int move_elapsed;

// idk how any of this is working with these casts but i dont want to touch it
void move_camera(int d_x, int d_y){
    int next_x = (int) camera_x + d_x;
    int next_y = (int) camera_y + d_y;

    if(camera_is_moving){
        return;
    }

    if(d_x == 0 && d_y == 0){
        return;
    }

    if (next_x < 0) next_x = 0;
    if (next_x > 128) next_x = 128;
    if (next_y < 0) next_y = 0;
    if (next_y > 128) next_y = 128;

    target_camera_x = (unsigned int) next_x;
    target_camera_y = (unsigned int) next_y;

    start_camera_x = (int) camera_x;
    start_camera_y = (int) camera_y;

    if(target_camera_x == start_camera_x && target_camera_y == start_camera_y){
        return;
    }

    camera_is_moving = 1;

    move_duration = CAMERA_MOVE_TIME;
    move_elapsed = 0;
}

void update_camera(){
    if (!camera_is_moving)
        return;

    ++move_elapsed;

    camera_x = (unsigned int) (start_camera_x + ((int)target_camera_x - start_camera_x) * (int)move_elapsed / (int)move_duration);
    camera_y = (unsigned int) (start_camera_y + ((int)target_camera_y - start_camera_y) * (int)move_elapsed / (int)move_duration);

    if (move_elapsed >= move_duration) {
        camera_x = target_camera_x;
        camera_y = target_camera_y;
        camera_is_moving = 0;
    }
}

void set_camera_position(char x, char y){
    camera_x = x;
    camera_y = y;
}