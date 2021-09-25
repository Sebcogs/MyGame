//dice.h roll for D+D
#ifndef DICE_H
#define DICE_H
//v4
#include<iostream>
#include <cstdlib>
using std::rand;
using std::srand;

#include <ctime>
using std::time;


class Dice
{
public:
   Dice( int multipleValue, int diceValue );
   // ~Dice();
   void setdice( int multipleValue, int diceValue );
   int getValue();
private:
   int dice;
   int multiple;
};   
#endif
