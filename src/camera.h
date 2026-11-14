#ifndef CAMERA_H
#define CAMERA_H

extern unsigned int camera_x;
extern unsigned int camera_y;

extern char camera_is_moving;

void update_camera();
void move_camera(signed int d_x, signed int d_y, unsigned char move_frame_duration);
void set_camera_position(char x, char y);

#endif