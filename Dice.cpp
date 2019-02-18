//dice.cpp dice definitions for D+D
#ifndef DICE_CPP
#define DICE_CPP
//v4
#include<iostream>
#include <cstdlib>
using std::rand;
using std::srand;

#include <ctime>
using std::time;

using namespace std;
#include "Dice.h"


Dice::Dice( int multipleValue, int diceValue)
   {
   setdice( multipleValue, diceValue );
   }
/*Dice::~Dice()
{
	//delete multiple;
	//delete dice;
} */

void Dice::setdice( int multipleValue, int diceValue )
   {
   dice = diceValue;
   multiple = multipleValue;
   }
   
int Dice::getValue()
   {
 //srand( time(0));
   //cout<<"random number: "<<rand()<<endl;
   int result = multiple * ( 1 + rand() % dice );
   return result;
   }   
#endif
