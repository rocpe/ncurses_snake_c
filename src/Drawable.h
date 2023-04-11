//NOT USED AT ALL!!!
/*
 * This header contains struct which makes drawing models on the board
 */
#pragma once
#include<stdio.h>
#include<inttypes.h>

//DRAWABLE_STRUCT
/*
 * It holds position and icon of the model
 */
typedef struct Drawable
{
    uint8_t y, x;
    chtype icon;
}Drawable;
