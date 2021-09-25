#ifndef ENCOUNTER_CPP
#define ENCOUNTER_CPP
//v4
#include<iostream>
#include<string>
#include<vector>
#include "Encounter.h"
#include "Dice.h"
#include "loadfromDBtemplate.cpp"

using namespace std;

//int getFileline(string);
//template<class T>
//bool getFromDB(T&, int);
//template<class T>
//string getItemFilename(T& x); 


Encounter::Encounter()
{
	numberAppearing = 1;
	Monster aMonster("temp", 1);
	getFromDB(aMonster, 1);	//load a single kobold	
		monsters.push_back(aMonster);	//load into vector
	/*else
		cout<<"error loading kobold"<<endl; */
	
	defeated = false;
	treasure = 0;

}

Encounter::Encounter(int monsterID, int numbAppear, int reward)
{
	numberAppearing = numbAppear;
	if(reward >= 0 && reward <=100)
		treasure = reward;
		else
			{
			cout <<"entered reward value in encounter is not between 0-100, use 0"<<endl;
			treasure = 0;
			}
	defeated = false;
	Monster aMonster("temp", 1);;
	getFromDB(aMonster, monsterID);	//load a monster
		
		for(int x=0; x < numbAppear; x++)
			monsters.push_back(aMonster);	//load into vector
			location = "center";
	/*	}
	else
		cout<<"error loading Monster ID:"<<monsterID<<endl; */
}

Encounter::Encounter(int level)		//average player level based on 4 characters
{
	string filename = "Monster.txt";	
	int maxentries = getFileline(filename);
	int ID;
	double cr;

	Dice roll(1, maxentries);
	ID = roll.getValue();
	Monster aMonster;
	if(getFromDB(aMonster, ID))		//load a monster
	{
	cr = aMonster.getCR();
		if(cr < level +1)
		{
		numberAppearing = level / cr;
		for(int x=0; x < numberAppearing; x++)
			monsters.push_back(aMonster);	//load into vector
		location = "center";
		Dice percent(1,100);
		treasure = percent.getValue();
		}
		else
			cout <<"Monster CR level too high. Not loaded"<<endl;
	}
	else
		cout<<"error loading Monster"<<endl;  
}

bool Encounter::isDefeated()
{
	defeated = true;
	for(int x=0; x < numberAppearing; x++)
			if(monsters[x].aliveOrDead())
				{
				defeated = false;
			//	cout <<"At least one monster is still alive."<<endl;
				}
	return defeated;
}

Monster Encounter::getMonster(int position)
{
	return monsters.at(position);
}

void Encounter::updateMonster(Monster aMonster, int position)
{
	monsters.at(position) = aMonster;
}
int Encounter::getNumberAppear()
{
	return numberAppearing;
}
string Encounter::getLocation()
{
	return location;
}
void Encounter::setLocation(string position)
{
	location = position;
}
int Encounter::getRemaining()
{
	int remaining = 0;
	if(!defeated);
	{
	for(int x=0; x < numberAppearing; x++)
		{
			if(monsters[x].aliveOrDead())
				{
				remaining++;			
				}
		}
	}
	return remaining;
}
int Encounter::getTreasureValue()
{
	return treasure;
}
int Encounter::giveExp()
{
	int exp = 0;
	if(defeated);
	{
	for(int x=0; x < numberAppearing; x++)
		{
		exp = exp + monsters[x].giveExp();
		}
	}
	return exp;
}
#endif
