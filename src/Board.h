/*
 * This header holds functions to setup display for snake game
 */
#pragma once
#include"SnakeMacros.h"
#include<stdio.h>
#include<ncurses.h>
#include<inttypes.h>
#include<stdlib.h>

//BOARD_STRUCT
/*
 *This struct holds basic display values
 */
typedef struct Board
{
    uint8_t height;
    uint8_t width;
    WINDOW* board_window;
}Board;

//FUNCTIONS
void setupDisplay(Board* YourBoard, const uint8_t height, const uint8_t width)
{
    uint8_t xMax, yMax;
    //get window size
    getmaxyx(stdscr, yMax, xMax);


    //make new widow
    YourBoard->board_window = newwin(height, width, (yMax/2) - (height/2),
                                    (xMax/2) - (width/2) );

    //remember size of the board
    YourBoard->height = height;
    YourBoard->width = width;
}
//--
void startScreen()
{
    clear();
    refresh();

    //disable typing on screen
    noecho();
    nodelay(stdscr, true);
    //keypad(stdscr, true);
    curs_set(0);
}
//--
void addAt(WINDOW* board_window, const uint8_t y, const uint8_t x, chtype ch)
{
    //put 'ch' at y and x
    mvwaddch(board_window, y, x, ch);
}
//--
//--
void addBorder(Board* YourBoard)
{
    box(YourBoard->board_window, 0, 0);
}
//--
chtype getInput(Board* YourBoard)
{
    return wgetch(YourBoard->board_window);
}
//--
void clearDisplay(Board* YourBoard)
{
    wclear(YourBoard->board_window);
    addBorder(YourBoard);
}
//--
void refreshDisplay(Board* YourBoard)
{
    wrefresh(YourBoard->board_window);
}
//--
/*
 * finds empty place to put new apple
 */
void findEmptyCoordinates(Board* YourBoard, uint8_t* y, uint8_t* x)
{
    //do util randomly found place (y,x) is empty, when empty exit
    while( (mvwinch(YourBoard->board_window,
                    *y = rand()%YourBoard->height,
                    *x = rand()%YourBoard->width  ) != BLANK_ICON ) );
}
