/*
 * This file holds all macros used in the code
 */

#pragma once

//snake's possible directions
enum direction
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
};

#define BOARD_DIM 35
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2
#define BOARD_MIDDLE BOARD_DIM/2

#define BLANK_ICON ' '
#define FRUIT_ICON 'a'
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'o'
