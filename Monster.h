//v4
#ifndef MONSTER_H
#define MONSTER_H

#include<iostream>
#include<string>
#include "Actor.h"

class Monster : public Actor
{
  friend ostream& operator<<(ostream&, Monster);
  friend istream& operator>>(istream&, Monster&);
   private:
      int AC, Init, Atk, DmgDie, DmgMult, DmgAdjust;
	bool Melee; //false for range attack
      double CR;
        int Exp;
		char size;
		int Id;
		int numDie;  //roll for number appearing
		//int morale;
public:
        Monster(string, double);
		Monster();
       // ~Monster();
		void setFields(int, string, int, double, int, int, int, int, int, int, char, bool, int);
		string getName();
        void outputData();
		void display();
        int giveExp();
		//int moraleCheck();
        double getCR(); 
		int getInit();
		int getDmgRoll();
		void receiveDamage(int);
		void receiveHealing(int);
  		int getAC();
		bool aliveOrDead();	//true is alive, false if dead
		int sizeMod();
		int meleeRoll();	//melee include 1d20 roll, STR and size mod
		//void createDatabase();
};
#endif
