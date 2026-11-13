#include "camera.h"

unsigned int camera_x = 0;
unsigned int camera_y = 0;

void move_camera(int d_x, int d_y)
{
    int next_x = camera_x + d_x;
    int next_y = camera_y + d_y;

    if (next_x < 0)
        next_x = 0;
    else if (next_x > 128)
        next_x = 128;

    if (next_y < 0)
        next_y = 0;
    else if (next_y > 128)
        next_y = 128;

    camera_x = next_x;
    camera_y = next_y;
}

void set_camera_position(char x, char y){
    camera_x = x;
    camera_y = y;
}