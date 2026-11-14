#include "camera.h"

unsigned int camera_x = 0;
unsigned int camera_y = 0;

char camera_is_moving = 0;

unsigned int target_camera_x = 0;
unsigned int target_camera_y = 0;

static int start_camera_x;
static int start_camera_y;
static unsigned int move_duration;
static unsigned int move_elapsed;

void move_camera(int d_x, int d_y, unsigned char move_frame_duration)
{
    int next_x = (int)camera_x + d_x;
    int next_y = (int)camera_y + d_y;

    if(d_x == 0 && d_y == 0){
        return;
    }

    if (next_x < 0) next_x = 0;
    if (next_x > 128) next_x = 128;
    if (next_y < 0) next_y = 0;
    if (next_y > 128) next_y = 128;

    target_camera_x = (unsigned int)next_x;
    target_camera_y = (unsigned int)next_y;

    start_camera_x = (int)camera_x;
    start_camera_y = (int)camera_y;
    move_duration = move_frame_duration;
    move_elapsed = 0;

    if (move_duration == 0) {
        camera_x = target_camera_x;
        camera_y = target_camera_y;
        camera_is_moving = 0;
    } else {
        camera_is_moving = 1;
    }
}

void update_camera(void)
{
    if (!camera_is_moving)
        return;

    ++move_elapsed;

    camera_x = (unsigned int)(start_camera_x + ((int)target_camera_x - start_camera_x) * (int)move_elapsed / (int)move_duration);
    camera_y = (unsigned int)(start_camera_y + ((int)target_camera_y - start_camera_y) * (int)move_elapsed / (int)move_duration);

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