#ifndef ABILITY_H
#define ABILITY_H
//v4
#include<iostream>
#include<string>
#include<vector>
#include <map>
#include "Stats.h"

using namespace std;

class Ability
{
	protected:
		const static int statNumber = 6;
		const static int statIncrease = 1;
		int statScore[statNumber];
		
	public:
		Ability();  //set abilities to 10
		map<string,Stats> stats;
		map<string, Stats>::iterator it; // = stats.begin();
		Stats getStats(string);
		int getStat(int);
		void setStat(int);  //roll abilities
		void setStat(int, int);
		 string getStatName(int);
		void outputData();
		void levelUp(int);
		int carryMaxLight();
};
#endif		    		
		
	
