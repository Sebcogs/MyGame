#ifndef PARTY_H
#define PARTY_H
//v4
#include<iostream>
#include<string>
#include<vector>
//#include "Actor.h"

using namespace std;
class Party
{
	private:
		int memberNumber;  //number of members ie size
		vector<string> marchingOrder;
	public:
		Party(string names[], int size);   
		string getMarchingOrderStr();
		void displayHeroNames();
		void setMarchingOrder();
		string getHero(int position);
		int heroPosition(string name);
		int getMemberNumber();
		int whichPartyMember();
		
};
#endif
