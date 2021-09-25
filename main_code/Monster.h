//v4
#ifndef MONSTER_H
#define MONSTER_H

#include<iostream>
#include<string>
#include <map>
#include "Actor.h"
#include "Stats.h"
#include "SpecialAtk.h"

enum monsterType {NOTMonster = -1, ANIMAL, VERMIN, UNDEAD, GOBLIN, GIANT, HUMANOID, ORC, KOBOLD, CONSTRUCT, OUTSIDER};
class Monster : public Actor
{
  friend ostream& operator<<(ostream&, Monster);
  friend istream& operator>>(istream&, Monster&);
   private:
      int AC, init, Atk, DmgDie, DmgMult, DmgAdjust;
	bool Melee; //false for range attack
      double CR;
        int Exp;
		char size;
		int Id;
		int numDie;  //roll for number appearing
        int touch;
        float hitDie;      //to add later, for spells and turning etc
     //   int saveThrow[3];
      //  string saveThrowName[3]; // = {"FORT", "REFLEX", "WILL"};
        monsterType mType;
        bool firstAtk = true;
        bool atkIsSpecial = false;
        //special attack below, separate class??
protected:
        SpecialAtk special;
 
		//int morale;
public:
        Monster(string, double);
		Monster();
        map<Saves, string> saves;
       // ~Monster();
       void setmap();
		void setFields(int, string, int, double, int, int, int, int, int, int, char, bool, int);
		//string getName();
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
        int getTouchAC();
		bool aliveOrDead();	//true is alive, false if dead
		int sizeMod();
		int meleeRoll();	//melee include 1d20 roll, STR and size mod
		//void createDatabase();
     //   int getSaveThrow(int);
     //   int getSaveThrow(Saves save);
	//	string getSaveName(int);
        monsterType intToType(int);
        monsterType getType();
        bool useSpecial();
        Saves intToSave(int);
        int getEffectCode();
        int getDuration();
        Saves getSpecialSaveType();
        int getSpecialDC();
        specialType getSpecialType();
        bool useSpecialDmg();
		float getHitDice();
};
#endif
