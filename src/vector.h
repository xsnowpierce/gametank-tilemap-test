#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    signed char x;
    signed char y;
} vector_s8b;

typedef struct {
    unsigned char x;
    unsigned char y;
} vector_u8b;

typedef struct {
    signed int x;
    signed int y;
} vector_s16b;

typedef struct {
    unsigned int x;
    unsigned int y;
} vector_u16b;

#endif