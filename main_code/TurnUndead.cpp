#ifndef TURNUNDEAD_CPP
#define TURNUNDEAD_CPP

#include<iostream>
#include<string>
#include "Dice.h"
#include "TurnUndead.h"

using namespace std;

TurnUndead::TurnUndead()
{
	turnsRemaining=3;
}

TurnUndead::~TurnUndead()
{
}
int TurnUndead::getTurnCheck()
{
	int roll, check;
	Dice dice1d20(1, 20);
	roll = dice1d20.getValue();
	check = roll + charMod;
	maxHD = clericLvl+(check - 10)/3;
		cout<<"Max HD of undead is "<<maxHD<<": turn check result = "<<check<<endl;
		getTurnDmg();
	return maxHD;
}
int TurnUndead::getTurnDmg()
{
	int roll;
	Dice dice2d6(2,6);
	roll = dice2d6.getValue();
	totalHD = roll + clericLvl + charMod;
	turnDmg = totalHD;
		cout<<"You can turn "<<totalHD<<" worth of creature hit dice."<<endl;
	return totalHD;
}
string  TurnUndead::getName()
{
	return name;
}
string  TurnUndead::getDesc()
{
	return desc;
}
int TurnUndead::getMaxHD()
{
	if(maxHD == -100 && turnsRemaining > 0)
	{
		getTurnCheck();
		turnsRemaining--;
	}
	return maxHD;
}
int TurnUndead::getDmgRemaining()
{
	return turnDmg;
}
void TurnUndead::setFields(int level, int mod)
{
	charMod=mod;
	clericLvl=level;
}
int TurnUndead::getTurnsAvailable()
{
	return turnsRemaining;
}
void TurnUndead::reset()
{
	turnsRemaining = perDayBase + charMod;
	maxHD = -100;
	totalHD = 0;
	turnDmg = 0;
	cout<<"You can attempt to turn undead a total of "<<turnsRemaining<<" times today."<<endl;
}
bool TurnUndead::turnMonster(Monster &amonster, int distance)
{
	float monsterHD = amonster.getHitDice();
	if(amonster.getType()!=UNDEAD)
		return false;
	else if(distance <= range)
	{
		//cout<<desc<<endl;
		if(monsterHD <= getMaxHD())
		{	//monster can be turned
			if(monsterHD <= turnDmg)
			{	//enough turn damage to affect creature
				if(clericLvl >= 2*monsterHD)
					amonster.receiveDamage(200);	//destroy
				else
				{
					amonster.condition.setCondition(8);	//turn
					amonster.condition.setDuration(10);
				}
				
				turnDmg = turnDmg - monsterHD;
					cout<<"Remaining turning Dmg of "<<turnDmg<<" out of "<<totalHD<<endl;
				return true;
			}
		}
		
	}
	else 
		cout<<"Turn is out of range."<<endl;
	return false;
}
void TurnUndead::finishTurn()
{
	maxHD = -100;
	totalHD = 0;
	turnDmg = 0;
}
void TurnUndead::outputData()
{
	cout<<getName()<<": "<<desc;
	if(perDayBase >0)
		cout<<" Turn per day: "<<getTurnsAvailable();
	cout<<endl;
}
#endif