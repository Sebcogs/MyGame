#include<string>
#include "Hero.h"
#include "Monster.h"
#include "spell.h"
#include "Dice.h"
//still need to work on this function
using namespace std;

class Caste
{
private:
	Spell aspell;
	bool classMagic;
	bool raceMagic;
	bool hasAreaEffect;
	bool isOffence;
	bool healUndead;
	Hero* attacker;
	Monster* defender;
	Hero* receiver;
	int distance;
	
public:
	Caste(Hero* attacker, Monster* defender, int distance);		//caste against enemy
	Caste(Hero* attacker);	//caste against oneself
	Caste(Hero* attacker, Hero* defender, int distance);	//caste against friend
	~Caste();
	void chooseMagicType();		//use race or class magic -used in constructor
	void chooseSpell();		//choose spell  -used in constructor
	int getSaveDC();		//used in getSpellSaveMod -in casteSpell
	bool checkRange();		//confirm chosen spell is in range  -used in constructor
	bool checkSpellHit();		//--in casteSpell
	float getSpellSaveMod();	//--in casteSpell  returns mod to dmg is save succeeds or not
	bool casteSpell();	//return true if can caste, false if can't caste
	int getAreaRange();
	void setNextTarget(Monster* defender);
	void setNextTarget(Hero* receiver);
};
bool checkSpellSave(Monster& attacker, Hero& defender);
/*
void chooseMagicType(Hero& attacker, bool& classMagic, bool& raceMagic);
Spell chooseSpell(Hero& attacker, bool useClassMagic, bool useRaceMagic, string& statName);
int getSaveDC(Hero& attacker, Spell aspell, string statName);
bool checkSpellHit(Hero& attacker, Monster& defender, Spell& aspell, int& hitRoll, int& MonsterAC, int& dmgCrit);
bool checkRange(int range, int distance);
bool checkSpellSave(Hero& attacker, Monster& defender, Spell aspell, int DC, Saves saveType, float& dmgMod);


Spell caste(Hero& attacker, Monster& defender, int distance,  bool& success);
bool caste(Hero& attacker, Hero& defender, int distance);
bool caste(Hero& attacker, Monster& defender, int distance, Spell& aspell);
*/