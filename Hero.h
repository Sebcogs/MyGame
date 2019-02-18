#ifndef HERO_H
#define HERO_H

//v4

#include<iostream>
#include<string>
#include<vector>
#include <map>
//#include <unordered_map>
#include "Race.h"
#include "charClass.h"
//#include "Item.h"
//#include "Weapon.h"
//#include "Armor.h"
//#include "Ability.h"
#include "Inventory.h"
#include "Actor.h"

class Hero : public Actor, public Race
{
	friend ostream& operator<<(ostream&, Hero);
    friend istream& operator>>(istream&, Hero&);
   private:
		const static long expLvlIncrement = 1000;        
		const static int statNumber = 6;
	
      int AC, Init, Atk, Dmg;
      int Lvl;
      long Exp;
    	bool Crit;
      int statMod[statNumber];
		Ability myAbilities;
      charClass myClass;
	
   public:
		enum Saves {FORT=0, REF, WIL};
		Inventory inventory;
		Hero();
        Hero(string);  
  		int getStat(int stat);
		void setName(string);
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
    	    //int getMod(Stats);
		int getMod(int);
		long getExpForNext();
		void updateHP();  
		int getAC();  //AC after DEX and size mod
		bool aliveOrDead();
		int meleeRoll(); //melee include 1d20 roll, STR and size mod
		int rangeRoll();
		int getInit();
		string getDmgDie();
		int getDmgRoll();
		string basicInfo();
		void setAtk();
		int getAtk();
		int getSaveThrow(int);
		string getSaveName(int);
		string getStatName(int);
		void setSpeed();
		int getMaxLightWeight();
		int getCurrentSpeed();
	//int getSpeed();
	//int getSpeedSlow();

};
#endif
