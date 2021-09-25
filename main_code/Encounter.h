#ifndef ENCOUNTER_H
#define ENCOUNTER_H
//v4
#include<iostream>
#include<string>
#include<vector>
#include "Monster.h"
//#include "loadfromDBtemplate.cpp"

using namespace std;

class Encounter
{
	private:
		int numberAppearing;
		vector<Monster>monsters;
		bool defeated;
		string location;
		int treasure;  //use to assign some treasure to the corpse 
		
	public:
		Encounter();  //For testing, 1 kobold
		Encounter(int monsterID, int numbAppear, int rewards);  //basic encounter
		Encounter(int level);  //Set random encounter based on average character level
		bool isDefeated();
		Monster getMonster(int position);  //return a Monster at position in vector
		void updateMonster(Monster aMonster, int position);	//update monster stats in vector
		int getNumberAppear();
		string getLocation();
		void setLocation(string);
		int getRemaining();
		int getTreasureValue();
		int giveExp();
};
#endif		    		
