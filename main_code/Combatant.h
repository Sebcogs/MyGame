#pragma once
#include <string>
#include "Actor.h"
//Maybe useless, depends too much on equipment

class Combatant : public Actor
{
private:
	int Atk;
	int AC;
	int Initiative;
	int Dmg;
	int Multi;
	int MinCrit;
	bool Crit;
public:
	Combatant();
	Combatant(std::string name);
	//~Combatant();	
	void setZero();
	void setFields(int ac, int atk, int dmg);
	void setWeapon(int dmg, int multi, int minCrit);
	int getAC();
	int getAtkRoll();
	int getInit();
	int getDmg();
	//std::string getDmgDie();
	int getAtk();

};

