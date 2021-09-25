#ifndef SPELL_H
#define SPELL_H

#include<iostream>
#include<string>
#include "Stats.h"
#include <map>

enum Schools {Univ = 0, Abju, Conj, Divi, Ench, Evoc, Illu, Necro, Tran};
enum Component {None = 0, Verb, Soma, Mate, Focu};
enum SpellType {Effect = 0, Attack, Heal};
enum offOrDef {OFFENSE = 0, DEFENSE}; 
using namespace std;

extern map<Schools, string> create_Schoolmap();

class Spell
{
	friend ostream& operator<<(ostream&, const Spell&);
	friend istream& operator>>(istream&, Spell&);
	
	const static int totalCompNum = 5;
protected:
   int idNum;
    string name;
    string desc = "A magic trick";
    Schools school = Univ;
	int casteTime = 1;
	unsigned int minlevel = 0;  //minimum level to caste
	int duration = 1;
	int range = 1;
	int effectDice = 0;     //damage or heal dice
    int level = 0;
    bool hasTouch = false;          //yes if must make touch attack roll 
	unsigned effectCode = 0;    //condition code
	int effectMod = 1;			//usually 1 but some effects (such as mage armour) are +4
	bool isSingleTarget = true;	//or area effect.
	int area = 0;
	string availableClass = "W";	//B - bard, C-cleric, W-wizard, R-ranger, G-gnome
	SpellType spellType = Effect;	//Effect, Attack or Heal
    Component component[3] = {Verb, Soma, None};
    Saves saveType = NONE;      //type of saving throw to avoid
    float saveEffect = 1;             //effect of successful saving throw
    offOrDef oD_type;   //offense or defense spell
public:
	Spell();
	Spell(string name, Schools school, SpellType spellType);
	map<Schools, string> Schoolmap;
	void setMap();
	//void setField(int id, string n, string descr, int lvl, Schools sch, SpellType sType, Component comp[3], )
	string getName();
	string getSchool(Schools key);
	void outputData();
	unsigned getEffectCode();	//code related to bit for Condition class
	int getEffectMod();
	bool operator<(Spell&);
	Schools intToSchool(int);
	Component intToComponent(int);
	SpellType intToSpellType(int);
    SpellType getEffectType();
	string getAvailableClass();
	void setSpellLvl(int lv);
    int getMinLevel();
    int getLevel();
	int getID();
    int getEffectDice();    //heal or damage
    bool getIsSingleTarget();
    int getRange();
    Saves getSaveType();
    float getSaveEffect();
    bool getHasTouch();
    int getDuration();
    offOrDef getOD();       //return if offense or defense
    offOrDef charToOD(char input);    //convert char o or d to offOrDef type
	int getArea();
};


#endif
