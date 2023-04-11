#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<inttypes.h>

/***************NODE******************************/
typedef struct Node
{
    uint8_t y,x;
    chtype icon;
    struct Node *next;
} Node;
/***************DEFINITIOS************************/
void listNodes(Node** root)
{
    Node *current = *root;
    int i = 0;
    puts("List:");
    while(current != NULL)
    {
        printf("[%d] x:%d y:%d icon:%c\n",i,current->x, current->y, current->icon);
        current = current->next;
        i++;
    }
    printf("Number of Nodes = %d\n", i);
}
//----------------------------//
void addNodeEnd(Node** root, const uint8_t y, const uint8_t x, const chtype ch)
{
    //creating new Node
    Node* new_Node = malloc(sizeof(Node));
    if(new_Node == NULL) exit(1);
    new_Node->next = NULL;
    new_Node->y = y;
    new_Node->x = x;
    new_Node->icon = ch;
    //handle when root is NULL
    if(*root == NULL)
    {
        *root = new_Node;//assume new_Node is a root
        return;
    }
    //going to the end of the list
    Node* current = *root;
    while(current->next != NULL) current = current->next;
    //attaching new_Node to the current
    current->next = new_Node;
}
//----------------------------//
void addNodeHead(Node** root, const uint8_t y, const uint8_t x, const chtype ch)
{
    //creating new Node and attaching new_Node to the beggining
    Node* new_Node = malloc(sizeof(Node));
    if(new_Node == NULL) exit(1);
    new_Node->y = y;
    new_Node->x = x;
    new_Node->icon = ch;
    new_Node->next = *root;
    //replacing root with new_Node
    *root = new_Node;
}
//----------------------------//
void insertAfter(Node* insert_node, const uint8_t y, const uint8_t x, const chtype ch)
{
    //creating new Node
    Node* new_Node = malloc(sizeof(Node));
    if(new_Node == NULL) exit(1);
    new_Node->y = y;
    new_Node->x = x;
    new_Node->icon = ch;

    new_Node->next = insert_node->next;
    insert_node->next = new_Node;
}
//----------------------------//
void removeNode(Node* root, Node* del_Node)
{
    Node* previous = NULL;
    Node* current = root;

    while(current != del_Node)
    {
        previous = current;
        current = current->next;
    }
    Node* temp = previous->next;
    previous = current->next;
    free(temp);
}
//----------------------------//
void invertList(Node** root)
{
    Node* previous = NULL;
    Node* current = *root;

    while(current != NULL)
    {
        Node* following = current->next;
        current->next = previous;//reversing pointers
        previous = current;
        current = following;//step forward

    }
    *root = previous;
}
//----------------------------//
void deallocate(Node** root)
{
    Node* current = *root;
    Node* previous;
    while(current != NULL)
    {
        previous = current;
        current = current->next;
        free(previous);
    }
    *root = NULL;
}
/***************END****************************/
