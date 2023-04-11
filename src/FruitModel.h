/*
 *  This model holds information and function of fruit model
 */
#pragma once
#include"SnakeMacros.h"
#include<stdio.h>
#include<inttypes.h>

//FRUITMODEL_STRUCT
/*
 * It holds position and icon of the fruit
 */
typedef struct FruitModel
{
    uint8_t y, x;
    chtype icon;
}FruitModel;

//FUNCTIONS
void initializeFruit(FruitModel* YourFruit, const chtype fruit_icon)
{
    YourFruit->icon = fruit_icon;
}
