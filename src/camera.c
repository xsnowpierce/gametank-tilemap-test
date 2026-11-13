#include "camera.h"
#include "gt/feature/text/text.h"

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))  

signed int camera_x = 0;
signed int camera_y = 0;

void move_camera(signed int d_x, signed int d_y){
    camera_x += d_x;
    camera_y += d_y;
    
    // camera_x = CLAMP(camera_x + d_x, 0, 127);
    // camera_y = CLAMP(camera_y + d_y, 0, 127);
}

void set_camera_position(char x, char y){
    camera_x = x;
    camera_y = y;
}

void print_camera_position(){
    char number_text[8];

    text_cursor_x = 0;
    text_cursor_y = 8;
    text_color = TEXT_COLOR_WHITE;

    text_print_string("x = ");
    text_sprint_int(number_text, camera_x);
    text_print_string(number_text);

    text_cursor_x = 0;
    text_cursor_y = 16;
    text_print_string("y = ");
    text_sprint_int(number_text, camera_y);
    text_print_string(number_text);
}