#ifndef TURNUNDEAD_H
#define TURNUNDEAD_H
#pragma once
#include<iostream>
#include<string>
#include "Dice.h"
#include "Monster.h"

using namespace std;

class TurnUndead
{
protected:
	string name = "Turn Undead";
	string desc = "you channel positive energy to drive off undead.";
	int charMod=0;
	int clericLvl=1;
	int range = 12;		//60ft range, effect closest first
	int maxHD=-100;
	int totalHD=0;
	int duration = 10;		//10 rounds (1min)
	int turnDmg=0;
	int turnsRemaining=3;
	int perDayBase = 3;
public:
	TurnUndead();
	~TurnUndead();
	int getTurnCheck();	//Determine  and return maxHD
	int getTurnDmg();	//return total HD
	string getName();
	string getDesc();
	int getMaxHD();
	int getDmgRemaining();
	void setFields(int level, int mod);
	int getTurnsAvailable();
	void reset();	//reset daily during rest
	void finishTurn();
	bool turnMonster(Monster &amonster, int distance);
	void outputData();
};

class CantTurn : public TurnUndead
{
public:
	CantTurn() : TurnUndead()
	{
		perDayBase = 0;
		turnsRemaining = 0;
		desc = "you CAN'T channel energy to turn undead.";
	}
	/*bool turnMonster(Monster &amonster, int distance)
	{
		cout<<"Can't turn"<<endl;
		//cout<<desc<<endl;
		return false;
	}*/
};
#endif
