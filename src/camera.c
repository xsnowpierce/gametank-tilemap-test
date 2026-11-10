#include "camera.h"

unsigned int camera_x = 0;
unsigned int camera_y = 0;

void move_camera(unsigned int d_x, unsigned int d_y){
    camera_x += d_x;
    camera_y += d_y;
}

void set_camera_position(unsigned int x, unsigned int y){
    camera_x = x;
    camera_y = y;
}