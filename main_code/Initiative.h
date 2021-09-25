#pragma once
#include<vector>
#include<string>
#include "Party.h"
#include "Encounter.h"
#include "Hero.h"

using namespace std;

class Initiative
{
private:
	int index =0;
	vector < pair< int, string> > initiativeList; 
public:
	Initiative();
	//~Initiative();
	void createList(Party heros, Hero champ[], Encounter monsters);
	string getNext();
	string getList();
	void sortList();

};

