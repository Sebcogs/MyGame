#ifndef MAGIC_H
#define MAGIC_H
//v4
#include<iostream>
#include <vector>
#include<string>
//#include <map>
//#include <unordered_map>
#include "Stats.h"
#include "spell.h"


using namespace std;

//int getFileline(string filename);
bool getSpellFromDB(Spell& x, int id);		//in loadfromDBtemplate.cpp

class Magic
{
protected:
   const static int spellLvlMax = 9;
   const static int spellLvlMaxRang = 4;
   const static int spellLvlMaxBrd = 6;
    string name;
    string desc;
    string user;
	bool hasMagic;
	unsigned int casterlevel;
		unsigned int highestSpellLvl;	//spell level max determined by ability score
	Stats abilityType;
	string abilityTypeStr;
	int abilityScore;	//from ability reference
	int abilityMod;		//from ability reference
	int maxbylevel[spellLvlMax+1] = {-1};	//9 possible levels, start with all -1
	int bonusbylevel[spellLvlMax+1] = {0};
	int availableSlots[spellLvlMax+1] = {-1};	//0th place is number of 0lvl spells, 1st place = number of 1lvl spells,etc
    vector<Spell> knownspellList;
	
public:
	Magic();
	virtual ~Magic() {};
	Stats getAbilitytype();
	string getAbilitytypeStr();
	virtual void bonusSpell();	//int mod);		//ability mod is loaded in setAbilityScore function
	int getmax(int level); 
	int getSlots(unsigned int level);
    Spell getSpell(unsigned int indexNum);
	virtual void levelUp(int lvl) {};
	void outputdata();
	void resetSpell();
	void addSpell(Spell aSpell);
	int getNumofKnown();
	int getNumofKnown(int spelllevel);
	bool getHasMagic();
	string getSpellList();
    void useSlot(unsigned int level);
    int getMaxSlotLevel();
    string casteableList();
	void setAbilityScore(int statScore, int mod);	//COUPLED! get ability score using abilityType to set 
	int getDC(int level);	//level is spell level
};

class WizMagic : public Magic
{
public:
	WizMagic();
	virtual ~WizMagic() { cout<<"Magic Deleted"<<endl;};
	void levelUp(int lvl);
};
class RangMagic : public Magic
{
public:
	RangMagic();
		virtual ~RangMagic() { cout<<"Magic Deleted"<<endl;};
	void levelUp(int lvl);
	//void bonusSpell();
};
class ClerMagic : public Magic
{
public:
	ClerMagic();
		virtual ~ClerMagic() { cout<<"Magic Deleted"<<endl;};
	void levelUp(int lvl);
};
class BardMagic : public Magic
{
public:
	BardMagic();
		virtual ~BardMagic(){ cout<<"Magic Deleted"<<endl;};
	void levelUp(int lvl);
};
class GnomMagic : public Magic
{
public:
	GnomMagic();
		virtual ~GnomMagic() { cout<<"Magic Deleted"<<endl;};
	void bonusSpell();	//int charmod);
	void levelUp(int lvl);
};

class MagicCreator
{
private:
	Magic * myMagic;
			
public:
	Magic * getMagic();
	//Race * getRace(string choice);
	//Race * getRace(unsigned int type);
};
#endif
