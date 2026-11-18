#include "camera.h"

#define CAMERA_MOVE_TIME 8

unsigned int camera_x = 0, camera_y = 0;

unsigned char camera_is_moving = 0;

unsigned int target_camera_x = 0, target_camera_y = 0;
int start_camera_x, start_camera_y;

unsigned int move_duration;
unsigned int move_elapsed;

// idk how any of this is working with these casts but i dont want to touch it
void move_camera(int dX, int dY){
    int nextX = (int) camera_x + dX;
    int nextY = (int) camera_y + dY;

    if (camera_is_moving) {
        return;
    }

    if (dX == 0 && dY == 0) {
        return;
    }

    if (nextX < 0) { 
        nextX = 0; 
    }
    if (nextX > 128) { 
        nextX = 128; 
    }
    if (nextY < 0) { 
        nextY = 0; 
    }
    if (nextY > 128) { 
        nextY = 128; 
    }

    target_camera_x = (unsigned int) nextX;
    target_camera_y = (unsigned int) nextY;

    start_camera_x = (int) camera_x;
    start_camera_y = (int) camera_y;

    if (target_camera_x == start_camera_x && target_camera_y == start_camera_y) {
        return;
    }

    camera_is_moving = 1;

    move_duration = CAMERA_MOVE_TIME;
    move_elapsed = 0;
}

void update_camera(){
    if (!camera_is_moving) {
        return;
    }

    ++move_elapsed;

    camera_x = (unsigned int) (start_camera_x + ((int) target_camera_x - start_camera_x) * (int) move_elapsed / (int) move_duration);
    camera_y = (unsigned int) (start_camera_y + ((int) target_camera_y - start_camera_y) * (int) move_elapsed / (int) move_duration);

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