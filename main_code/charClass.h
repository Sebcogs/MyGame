#ifndef CHARCLASS_H
#define CHARCLASS_H
//v4
#include<iostream>
#include<string>
#include <map>
#include <unordered_map>
#include "Stats.h"
#include "magic.h"
#include "TurnUndead.h"


enum Styles {BARB=0, BARD, FIGH, CLER, RANG, WIZ};
using namespace std;

extern map<Styles, string> create_Stylesmap();
extern map<string, Styles> create_StyleStringmap();


class charClass
{
   protected:
        string className;  
        int hitDice;     
        int Atk;
        int saveThrow[3];
   string saveThrowName[3]; // = {"FORT", "REFLEX", "WILL"};
   string startingGear;

   public:
       charClass();  //set all mod to 0
	virtual ~charClass() {};
			map<string, Styles> styles;
			map<Saves, string> saves;
		Magic *classmagic;	//should be private?  needs to be pointer for virtual method to work
		TurnUndead *turning;
		void setMap();
		Styles getStyle(string);
        void outputData();
        int getAtk();
        int getHitDice();
		string getClassName();
	virtual void levelUp(int) {};  //does virtual work for this? need to use pointer
        int getSaveThrow(int);   
        string getStartingGear();
		
}; 


class BarbClass : public charClass
{
public:
	BarbClass() : charClass() 
	{
		className = "Barbarian";
		hitDice = 12;
		Atk = 1;
		saveThrow[FORT] = 2;
		saveThrow[REF] = 0;
		saveThrow[WIL] = 0;
		classmagic = new Magic();
		turning = new CantTurn();
        startingGear = "W: 7, 13, 5\nA: 3\n";   //Armor: stud leather 3(4-s), W: greataxe 7, shortbow13(14-s), dagger 5(6-s)
	};
	virtual ~BarbClass() 
	{
		delete classmagic;
		delete turning;
		cout<<"   ---Barb destructor----  "<<endl;
	};
	void levelUp(int newlevel) //const override
	{
		cout<<className<<" class specific level up"<<endl;
		Atk++;
		if(!(newlevel % 2))
		{
		saveThrow[FORT]++;
		}
		if(!(newlevel % 3))
		{
		saveThrow[REF]++;
		saveThrow[WIL]++;
		}  
	};
};

class BardClass : public charClass
{
public:
	BardClass() : charClass()
	{
			className = "Bard";
            hitDice = 6;
            Atk = 0;
			saveThrow[FORT] = 0;
			saveThrow[REF] = 2;
			saveThrow[WIL] = 2;
			//BardMagic temp;
			//classmagic = &temp;
			classmagic = new BardMagic();
			turning = new CantTurn();
        startingGear = "W: 1, 15\nA: 3\n";   //Armor: stud leather 3(4-s), W: shortsword 1(2-s), light crossbow 15(16-s)
	};
	virtual ~BardClass() 
	{
		delete classmagic;
		delete turning;
		cout<<"   ----Bard destructor---   "<<endl;
	};
	void levelUp(int newlevel) //const override
	{
		   // className = "Bard";  
		if(!(newlevel % 3))
			{
			saveThrow[FORT]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[REF]++;
			saveThrow[WIL]++;
			}       
        if(newlevel == 5 || newlevel == 9 || newlevel == 13 || newlevel == 17)
			{
			}
		else
	    	Atk++;
			classmagic->levelUp(newlevel);
			classmagic->bonusSpell();
	};
};

class FighterClass : public charClass
{
public:
	FighterClass() : charClass()
	{
			className = "Fighter";
            hitDice = 10;
            Atk = 1;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 0; 
			classmagic = new Magic();
			turning = new CantTurn();
            startingGear = "W: 8, 13, 5\nA: 7\n";   //Armor: scale mail 7(8-s) W: greatsword 8, shortbow13(14-s), dagger 5(6-s)
	};
	virtual ~FighterClass() 
	{
		delete classmagic;
		delete turning;
		cout<<"  ---Fighter destructor---- "<<endl;
	};
	void levelUp(int newlevel) //const override
	{
		 // className = "Fighter";
            Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[REF]++;
			saveThrow[WIL]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			}      
	}
};

class ClericClass : public charClass
{
public:
	ClericClass() : charClass()
	{
			className = "Cleric";
			turning = new TurnUndead();
            hitDice = 8;
            Atk = 0;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 2; 
			//ClerMagic temp;
			//classmagic = &temp;
			classmagic = new ClerMagic();
            startingGear = "W: 9, 15\nA: 7, 13\n";   //Armor: scale mail 7(8-s), heavy shield 13(14-s) W: heavy mace 9(10-s), light crossbow 15(16-s)
	}
	virtual ~ClericClass() 
	{
				delete classmagic;
				delete turning;
				cout<<"   ---Cleric destructor----  "<<endl;
				};
	void levelUp(int newlevel) //const override
	{
		           //   className = "Cleric";
        if(newlevel == 5 || newlevel == 9 || newlevel == 13 || newlevel == 17)
			{
			}
		else
	    	Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[REF]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			saveThrow[WIL]++;
			}  
			classmagic->levelUp(newlevel);
			classmagic->bonusSpell();
	}
};

class RangerClass : public charClass
{
public:
	RangerClass() : charClass()
	{
			className = "Ranger";
            hitDice = 8;
            Atk = 1;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 2;
			saveThrow[WIL] = 0; 
			//RangMagic temp;
			//classmagic = &temp;
			classmagic = new RangMagic();
			turning = new CantTurn();
            startingGear = "W: 3, 17, 5\nA: 3\n";   //Armor: stud leather 3(4-s) W: longsword 3(4-s), longbow17(18-s), dagger 5(6-s)
	}
	virtual ~RangerClass() 
	{
				delete classmagic;
				delete turning;
		cout<<"   ---Ranger destructor----  "<<endl;
		};
	void levelUp(int newlevel) //const override
	{
		  //  className = "Ranger";           
            Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[WIL]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			saveThrow[REF]++;
			}     
		classmagic->levelUp(newlevel);
		classmagic->bonusSpell();
	}
};

class WizardClass : public charClass
{
public:
	WizardClass() : charClass()
	{
			className = "Wizard";
            hitDice = 4;
            Atk = 0;
			saveThrow[FORT] = 0;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 2; 
			//WizMagic temp;
			//classmagic = &temp;
			classmagic = new WizMagic();
			turning = new CantTurn();
            startingGear = "W: 11, 15\nA: \n";   //Armor: none W: quarterstaff 11(12-s), light crossbow 15(16-s)
	}
	virtual ~WizardClass()
	{
				delete classmagic;
				delete turning;
		cout<<"   ---Wizard destructor----  "<<endl;};
	void levelUp(int newlevel) //const override
	{
		bool isOdd = newlevel%2;
		if(!isOdd)	//even levels Atk and Will increas
		{
			Atk++;
			saveThrow[WIL]++; 
			//WizMagic temp;
		}
		if(isOdd)
		{
			saveThrow[FORT]++;
			saveThrow[REF]++;
		}
		classmagic->levelUp(newlevel);
		classmagic->bonusSpell();
	}
}; 
class NoClass : public charClass
{
public:
	NoClass() : charClass()
	{
			className = "No class";
            hitDice = 4;
            Atk = 0;
			saveThrow[FORT] = 0;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 0; 
		classmagic = new Magic();
		turning = new CantTurn();
        startingGear = "W: 5\nA: \n";     //just a dagger
	}
	virtual ~NoClass() 
	{
				delete classmagic;
				delete turning;
		cout<<"   ---No Class destructor----  "<<endl;};
	void levelUp(int newlevel) //const override
	{
		cout<<"You have no class so nothing to level up"<<endl;
	}
}; 

class CharClassCreator
{
private:
	charClass * myClass;
			//map<Styles, string> styles;
public:
	charClass * getClass();
	charClass * getClass(string choice);
	charClass * getClass(unsigned int type);
};

#endif