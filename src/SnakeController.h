/*
 * Main snake game controller: contains all logic etc.
 */
#pragma once
#include"Board.h"
#include"SnakeModel.h"
#include"SnakeMacros.h"
#include"FruitModel.h"
#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>
#include<stdbool.h>
#include<time.h>

//SNAKECONTROLLER_STRUCT
/*
 * SnakeController holds all significant information of the game
 */
typedef struct SnakeController
{
    Board* board;
    Node* SnakeHead;
    Node* SnakeTail;
    FruitModel* fruit;
    uint8_t SnakeDirection;
    bool gameOver;
    uint8_t score;
}SnakeController;

//FUNCTIONS
/*
 * This function sets up everything: display, models etc.
 */
void initializeSnakeGame(SnakeController* YourSnakeGame, const uint8_t height,
                         const uint8_t width)
{
    //initialize the screen
    YourSnakeGame->board = (Board*) malloc( sizeof(Board) );
    setupDisplay(YourSnakeGame->board, height, width);

    //start screen and draw border and refresh screen
    startScreen();
    addBorder(YourSnakeGame->board);
    refreshDisplay(YourSnakeGame->board);

    //set score to zero and game isn't over
    YourSnakeGame->gameOver = false;
    YourSnakeGame->score = 0;

    //create your snake. Snake and linked list goes in the opposite order so snake's head is list's end
    createSnake( &YourSnakeGame->SnakeTail, SNAKE_HEAD, BOARD_MIDDLE, 2*BOARD_MIDDLE);//create actual head
    YourSnakeGame->SnakeDirection = UP;//default snake's direction
    addNodeHead( &YourSnakeGame->SnakeTail, BOARD_MIDDLE+1 ,2*BOARD_MIDDLE, SNAKE_BODY);//create tail
    
    YourSnakeGame->SnakeHead = YourSnakeGame->SnakeTail->next;//remember head's node
    drawSnake(YourSnakeGame->SnakeTail, YourSnakeGame->board);//draw your snake

    //create random numbers generator
    srand(time(NULL));

    //create fruit and put it on the board
    YourSnakeGame->fruit = (FruitModel*) malloc( sizeof(FruitModel) );
    initializeFruit(YourSnakeGame->fruit, FRUIT_ICON);
    findEmptyCoordinates(YourSnakeGame->board, &YourSnakeGame->fruit->y,
                                               &YourSnakeGame->fruit->x);
    addAt(YourSnakeGame->board->board_window, YourSnakeGame->fruit->y,
                                              YourSnakeGame->fruit->x,
                                              YourSnakeGame->fruit->icon);
    //print score in upper right corner
    mvprintw(BOARD_DIM/3,BOARD_DIM/2,"Score: %d",YourSnakeGame->score);
    refresh();
}
//--
bool snakeOnFruit(Node* SnakeHead, uint8_t prevFruitY, uint8_t prevFruitX)
{
    return (SnakeHead->y == prevFruitY  && SnakeHead->x == prevFruitX)? true : false;
}
//--
bool snakeOnBorder(Node* SnakeHead, Board* board)
{
    return ( SnakeHead->x == 0 || SnakeHead->x == board->width-1 ||
             SnakeHead->y == 0 || SnakeHead->y == board->height-1 )? true : false;
}
//--
void processInput(SnakeController* YourSnakeGame)
{
    switch( getInput(YourSnakeGame->board) )
    {
        case 'k':
            YourSnakeGame->SnakeDirection = UP;
            break;
        case 'j':
            YourSnakeGame->SnakeDirection = DOWN;
            break;
        case 'h':
            YourSnakeGame->SnakeDirection = LEFT;
            break;
        case 'l':
            YourSnakeGame->SnakeDirection = RIGHT;
            break;
    }
}
//--
void updateState(SnakeController* YourSnakeGame)
{
    //move snake
    moveSnake(YourSnakeGame->SnakeTail, YourSnakeGame->SnakeDirection, YourSnakeGame->board);

    if( snakeOnFruit(YourSnakeGame->SnakeHead, YourSnakeGame->fruit->y, YourSnakeGame->fruit->x) )
    {
        //delete previous apple
        addAt(YourSnakeGame->board->board_window, YourSnakeGame->fruit->y,
              YourSnakeGame->fruit->x, BLANK_ICON );
    
        //find empty place for the next fruit
        findEmptyCoordinates(YourSnakeGame->board, &YourSnakeGame->fruit->y,
                                                   &YourSnakeGame->fruit->x);
        //display the fruit in the new place
        addAt(YourSnakeGame->board->board_window, YourSnakeGame->fruit->y,
                                                  YourSnakeGame->fruit->x, FRUIT_ICON);

        //make snake longer
        lengthenSnake(&YourSnakeGame->SnakeTail, SNAKE_BODY, YourSnakeGame->SnakeDirection);

        ++YourSnakeGame->score;
        
        //print score
        mvprintw(BOARD_DIM/3,BOARD_DIM/2,"Score: %d",YourSnakeGame->score);
        refresh();
    }

    drawSnake(YourSnakeGame->SnakeTail, YourSnakeGame->board);

    if( snakeOnBorder(YourSnakeGame->SnakeHead, YourSnakeGame->board) )
        YourSnakeGame->gameOver = true;
}
/*
 * Deallocates all used memory
 */
void endSnakeGame(SnakeController** YourSnakeGame)
{
    deallocateSnake( &(*YourSnakeGame)->SnakeTail);
    (*YourSnakeGame)->SnakeHead = NULL;
    free( (*YourSnakeGame)->board);
    free( (*YourSnakeGame)->fruit);
    free(*YourSnakeGame);
}
