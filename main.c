#include"src/SnakeController.h"
#include<stdio.h>
#include<ncurses.h>
#include<stdlib.h>

int main()
{
    initscr();
    refresh();

    //setup the game
    SnakeController* GameSnake = (SnakeController*) malloc( sizeof(SnakeController) );
    initializeSnakeGame(GameSnake, BOARD_ROWS, BOARD_COLS);

    while( !(GameSnake->gameOver) )
    {

        //get input from the player
        processInput(GameSnake);
        
        //update the game
        updateState(GameSnake);

        //redraw display
        refreshDisplay(GameSnake->board);
    }

    endwin();
    printf("Score: %d\n",GameSnake->score);
    //deallocates memory
    endSnakeGame(&GameSnake);
    return 0;
}
