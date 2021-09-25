#ifndef ACTOR_H
#define ACTOR_H
//v4
#include<iostream>
#include<string>
#include "Condition.h"
#include "SaveThrow.h"


using namespace std;
class Actor
{
   protected:
      string actorName;
	  
      bool alive;
      int HP, maxHP;
		int speed = 6;  //speed of 30ft - 6 (30ft/5) steps per round
		int slowspeed = 4;
		
   public:
		Actor();
        Actor(string);
		Condition condition;  //replace with ConditionList  to hold multiple conditions
		SaveThrow aSavethrow;
		// ~Actor();
        void setName(string);
        string getName();
        void setHP(int);
        void setHP();
        int getHP();
        int getMaxHP();
        bool aliveOrDead();
        void outputData();  
		void revive();  
		void receiveDamage(int);
		void receiveHealing(int);
		int getSpeed();
		int getSpeedSlow();
		void setSpeed(int, int);
		int getSaveThrow(Saves save);
		int getSaveThrow(Saves save, specialType special);
}; 
#endif
