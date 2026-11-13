#ifndef CAMERA_H
#define CAMERA_H

extern signed int camera_x;
extern signed int camera_y;

void move_camera(signed int d_x, signed int d_y);
void set_camera_position(char x, char y);
void print_camera_position();

#endif