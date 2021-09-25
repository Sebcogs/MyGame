#include<iostream>
#include<string>
#include "Initiative.h"
#include "Dice.h"

using namespace std;

Initiative::Initiative()
{
	initiativeList.clear();
}
/*
Initiative::~Initiative()
{
} */
void Initiative::createList(Party heros, Hero champ[], Encounter monster)
{
	int initiative;
	string playerstring;
	
	for(int x=0; x<heros.getMemberNumber(); x++)
	{
			srand( time(0)+x );
			Dice dice1d20(1,20);   
			int roll = dice1d20.getValue();
		playerstring = "H" + to_string(x);
		initiative = champ[x].getInit()+roll;
		cout<<playerstring<<" roll of "<<roll<<endl;
	//pair is <initiative , Hero# or Monster#>
	initiativeList.push_back( make_pair(initiative, playerstring) );
	}
	for(int y=0; y<monster.getNumberAppear(); y++)
	{
			srand( time(0)+y+initiative );
			Dice dice1d20(1,20);   
			int roll = dice1d20.getValue();
		playerstring = "M" + to_string(y);
		initiative = monster.getMonster(y).getInit()+roll;
				cout<<playerstring<<" roll of "<<roll<<endl;
		initiativeList.push_back( make_pair(initiative, playerstring) );
	}
	sortList();
	index = initiativeList.size()-1;
}
string Initiative::getNext()
{	//list is ascending order so index from back to front
	if(index<0)
		index = initiativeList.size()-1;
	int oldindex = index;
	index--;
	return initiativeList[oldindex].second;
}
string Initiative::getList()
{
	string infolist;
	for (unsigned int i=0; i<initiativeList.size(); i++) 
    { 
		//cout<<"count "<<i<<" out of "<<initiativeList.size()<<endl;

			//cout << initiativeList[i].first << " "<< initiativeList[i].second << endl; 
		infolist = infolist + to_string(initiativeList[i].first) + " " + initiativeList[i].second + "\n";
    } 
		//cout<<"Done list"<<endl;
	return infolist;
}
void Initiative::sortList()
{
	sort(initiativeList.begin(), initiativeList.end()); 
}

