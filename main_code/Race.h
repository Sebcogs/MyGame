#ifndef RACE_H
#define RACE_H
//v4
#include <iostream>
#include <string>
#include <map>
//#include <unordered_map>
#include <iterator>
#include "Ability.h"
#include "Stats.h"
#include "magic.h"
#include "Monster.h"

enum Races {HUM=0, ELF, DWA, HAF, GNO};

using namespace std;
extern map<Races, string> create_Racesmap();
extern map<string, Races> create_RaceStringmap();


class Race
{
   protected:
      // const static int statNumber = 6;
       const static int MAX_ENEMY = 3;	//number of favoured enemy types
        string raceName;
        char size;
        int mod[statNumber];
        monsterType favouredEnemy[MAX_ENEMY] = {NOTMonster, NOTMonster, NOTMonster}; // = {-1,-1,-1};
monsterType dodgeEnemy[MAX_ENEMY] = {NOTMonster, NOTMonster, NOTMonster}; // = {-1,-1,-1};
		int specialAtksaves[SPECIAL_TYPE_NUMBER];	//some races have bonus saves against certain attacks
		int raceSaveBonus[4];	//some races have save throw bonuses.
   public:
       Race();  //set all mod to 0
		virtual ~Race() {};

			map<string, Races> races;
			Magic *racemagic;	//should be private?
		void setMap();
        virtual void outputData();
        int getMod(int);
        char getSize();
		int getRaceIndex();
		int getsizeMod();
		Races getRace(string);
		string getRaceName();
        monsterType getFavouredEnemy(int index);
        monsterType getDodgeEnemy(int index); 
        void addFavouredEnemy(monsterType amonster);
        void addDodgeEnemy(monsterType amonster);
        int getMaxFavoured();
		int getRaceSave(Saves save);
		int getSpecialSave(int special);
}; 

class Human : public Race
{
public:
	Human();
	virtual ~Human() {delete racemagic; cout<<"race deleted"<<endl;};
};

class Elf : public Race
{
public:
	Elf();
	virtual ~Elf() {delete racemagic; cout<<"race deleted"<<endl;};
};

class Dwarf : public Race
{
public:
	Dwarf();
	virtual ~Dwarf() {delete racemagic; cout<<"race deleted"<<endl;};
};

class Halfling : public Race
{
public:
	Halfling();
	virtual ~Halfling() {delete racemagic; cout<<"race deleted"<<endl;};
};
class Gnome : public Race
{
public:
	Gnome();
	virtual ~Gnome() {delete racemagic; cout<<"race deleted"<<endl;};
	void outputData();
};

class RaceCreator
{
private:
	Race * myRace;
			
public:
	Race * getRace();
	Race * getRace(string choice);
	Race * getRace(unsigned int type);
};
#endif
