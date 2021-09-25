#ifndef HERO_H
#define HERO_H

//v4

#include<iostream>
#include<string>
#include<vector>
//#include<map>
//#include <unordered_map>
#include "Race.h"
#include "charClass.h"
//#include "Item.h"
//#include "Weapon.h"
//#include "Armor.h"
//#include "Ability.h"
#include "inventory/Inventory.h"
#include "Actor.h"
//#include "factory.h"
#include "SpecialAtk.h"

class Hero : public Actor
{
	//friend ostream& operator<<(ostream&, Hero);
    friend istream& operator>>(istream&, Hero&);
   protected:
		const static long expLvlIncrement = 1000;        
		const static int statNumber = 6;
	
	int AC, init, Atk, Dmg;
	int Lvl;
	long Exp;
	bool Crit;
	int statMod[statNumber];
		Ability myAbilities;
     
	
   public:
			Inventory inventory;
            charClass *myClass;
            Race *myRace;
		Hero();
		~Hero();
        Hero(string);  
  		int getStat(int stat);
		//void setName(string);
		void setFields();   
	 	void outputData();
		void outputStats();
		void outputShortData();
        void setExp(int);
        long getExp();
        void levelUp();
        int getLevel();
			//void setMod(Stats);
		void setMod(int);
		void setMod();
    	    int getMod(Stats stat);
		int getMod(int);
		long getExpForNext();
		void updateHP();  
		int getAC();  //AC after DEX, condition and size mod
		//bool aliveOrDead();
		int meleeRoll(); //melee include 1d20 roll, STR and size mod
		int rangeRoll();
		int getInit();
		string getDmgDie();
		int getDmgRoll();	
		string basicInfo();  
		void setAtk();
		int getAtk(); 
        bool getCrit();
		string getStatName(int);
		void setSpeed();
		int getMaxLightWeight();
		int getCurrentSpeed();
	//int getSpeed();	//in Actor class
	//int getSpeedSlow();	//in Actor class
	void adjustStats(Race*);
	void checkMagicBonus();
	void setCondition(int bitcode);
	void setCondition(int bitcode, int mod);
	string getSpellList();
    string saveData();
    char getHasMagic(); //return: b for both, r for race, c for class, n for none
    string getStartingGear();
		int getSaveThrow(Saves save);
		int getSaveThrow(Saves save, specialType special);
		void updateAll();	//updates the savethrow temp and other variables
};
#endif
