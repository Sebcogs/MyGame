#include "Combatant.h"
#include <string>
#include "Dice.h"
//Maybe useless, depends too much on equipment

using namespace std;
Combatant::Combatant(): Actor ()
{
	setZero();
}
Combatant::Combatant(string name): Actor (name)
{
	setZero();
}
void Combatant::setZero()
{
	Atk = 0;
	AC = 10;
	Initiative = 0;
	Dmg = 3;
	Crit = false;
	Multi = 1;
	MinCrit = 20;
}
/*
Combatant::~Combatant()
{
} */
void Combatant::setFields(int ac, int atk, int dmg)
{
	AC = ac;
	Atk = atk;
	Dmg = dmg;
}
void Combatant::setWeapon(int dmg, int multi, int minCrit)
{
	Dmg = dmg;
	Multi = multi;
	MinCrit = minCrit;
	
}
int Combatant::getAC()
{
	return AC;
}
int Combatant::getAtkRoll()
{
	Crit = false;
	srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue();
	return roll + Atk;
}

int Combatant::getInit()
{
	return Initiative;
}
int Combatant::getDmg()
{
	return Dmg;
}
/*
string Combatant::getDmgDie()
{
	
} */
int Combatant::getAtk()
{
	return Atk;
}
;