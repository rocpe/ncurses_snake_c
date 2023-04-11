#pragma once
#include"singly_linked_list.h"
#include"SnakeController.h"
#include"SnakeMacros.h"
#include<stdio.h>
#include<inttypes.h>

//FUNCTIONS
/*
 * Snake is just linked list which head and tail (tail is first node in the list) is stored in SnakeController.
 * So snake and lined list goes in the opposite order! But first has to be allocated head
 */

void createSnake(Node** YourSnake, const chtype SnakeHead, const uint8_t y,
                 const uint8_t x)
{
    //allocate linked list and create first node (id est head and then add tail to the beggining of the list)
    //y and x is snake's default location
    *YourSnake = malloc(sizeof(Node));
    if(YourSnake == NULL) exit(1);
    (*YourSnake)->next = NULL;
    (*YourSnake)->y = y;
    (*YourSnake)->x = x;
    (*YourSnake)->icon = SnakeHead;
}
//--
void deallocateSnake(Node** tail)
{
    Node* current = *tail;
    Node* previous;
    while(current != NULL)
    {
        previous = current;
        current = current->next;
        free(previous);
        previous = NULL;
    }
    *tail = NULL;
}
//--
void moveSnake(Node* SnakeTail, const uint8_t currMovementDir, Board* YourBoard)
{
    /*
     * To move whole snake firstly you need to put blank space to the tail
     * then move whole snake by reassiging coordinates of n-th piece to the n+1-th piece
     *(going from tail to head), lastly move snake's head based on currMovementDir
     */

    //put blank space to the tail
    mvwaddch( YourBoard->board_window, SnakeTail->y, SnakeTail->x, BLANK_ICON);

    //moving every piece
    Node* current = SnakeTail->next; //n+1-th piece
    Node* precurrent = SnakeTail; //n-th piece
    do
    {
        precurrent->y = current->y;
        precurrent->x = current->x;
        current = current->next;
        precurrent = precurrent->next;
    }
    while(current != NULL);//so do until precurrent is head

    //moving head, now precurrent is head
    switch(currMovementDir)
    {
        case UP://head goes UP
            --(precurrent->y);
            break;
        case DOWN://DOWN
            ++(precurrent->y);
            break;
        case LEFT://LEFT
            --(precurrent->x);
            break;
        case RIGHT://RIGHT
            ++(precurrent->x);
            break;
    }
}
//--
void lengthenSnake(Node** SnakeTail, const chtype SnakePiece, const uint8_t currMovementDir)
{
    Node* precurrent = (*SnakeTail)->next;
    Node* current = *SnakeTail;

    /*
     * based on the two first nodes it's possible to determine where to put 
     * new piece of the snake. y_p, x_p, x_e, y_e means pretail and tail
     * coordinates of the two first snake's pieces. On the board point 0,0
     * is in the left upper corner and y axis goes down, x goes right.
     *  +--------------> x
     *  |
     *  |
     *  |
     *  |
     *  v
     *  y
     */

    //tmp variables to make it more readable
    uint8_t y_p, x_p, x_e, y_e;
    y_p = precurrent->y;
    x_p = precurrent->x;
    y_e = current->y;
    x_e = current->x;

    if( x_p-x_e == 0 && y_p-y_e < 0 )//last pieces goes UP
        //put new piece below last piece
        addNodeHead(SnakeTail, y_e + 1, x_e, SnakePiece);

    else if( x_p-x_e == 0 && y_p-y_e > 0 )//last pieces goes DOWN
        //put new piece above last piece
        addNodeHead(SnakeTail, y_e - 1, x_e, SnakePiece);

    else if( x_p-x_e > 0 && y_p-y_e == 0 )//last pieces goes RIGHT
        //put new piece for the left side of the last piece
        addNodeHead(SnakeTail, y_e, x_e - 1, SnakePiece);

    else if( x_p-x_e < 0 && y_p-y_e == 0 )//last pieces goes LEFT
        //put new piece for the right side of the last piece
        addNodeHead(SnakeTail, y_e, x_e + 1, SnakePiece);
}
//--
void drawSnake(Node* SnakeTail, Board* YourBoard)
{
    Node* current = SnakeTail;
    while(current != NULL)
    {
        //put piece on the board
        mvwaddch( YourBoard->board_window, current->y, current->x, current->icon);
        current = current->next;
    } 
}
//--
//--
