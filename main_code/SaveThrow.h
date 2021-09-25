#pragma once
#ifndef SaveThrow_H
#define SaveThrow_H

#include<iostream>
#include<string>
#include <map>
#include "Stats.h"
#include "SpecialAtk.h"


class SaveThrow
{
private:
	int saveThrow[4];
	map<specialType, int> specialTypeMod;	//for specific save bonuses against special attacks (sleep, fear, etc)
	string saveThrowName[4];
	int raceBonus[4];
	int tempBonus[4];	//how to implement from condition??
	int statMod[4];		//CON, DEX, WIS ability mod for fort, reflex and will saves
public:
	SaveThrow();
	~SaveThrow();
	void setFields(int fort, int reflex, int will);
	void setRaceFields(int fort, int reflex, int will);
	void updateTempBonus(int fort, int reflex, int will);
	void updateStatMod(int con, int dex, int wis);
	void setSpecialFields(int values[SPECIAL_TYPE_NUMBER]);
	int getSaveThrow(Saves save);
	int getSaveThrow(Saves save, specialType special);
	string getSaveName(Saves save);
	Saves intToSave(int input);
	void outputData();
};

#endif