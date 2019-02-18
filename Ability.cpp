#ifndef ABILITY_CPP
#define ABILITY_CPP
//v4
#include<iostream>
#include<string>
#include<vector>
#include <map>
#include<iomanip>
#include <iterator>
#include <math.h> 
#include "Ability.h"
#include "Dice.h"

using namespace std;

Ability::Ability()
{		//Set Map...
		stats["STR"] = STR;
		stats["DEX"] = DEX;
		stats["CON"] = CON;
		stats["INT"] = INT;
		stats["WIS"] = WIS;
		stats["CHA"] = CHA;

	it = stats.begin();
while(it!=stats.end())
	{
	setStat(it->second,10);   //Set all to default 10 value
//	cout <<"stat : "<<it->first <<" : "<<it->second<< " = "<<getStat(it->second)<<endl;
	it++;
	} 
}
Stats Ability::getStats(string input) 
{
	return stats.find(input) -> second;
}
void Ability::setStat(int stat, int value) //Stats stat, int value)
{
	statScore[stat] = value;
}
//This is the main function for assigning random ability scores
void Ability::setStat(int stat) //Stats stat)  //choose higher of two
{
    srand( time(0)+stat );
   Dice dice3d6A(3,6);   
int a = dice3d6A.getValue();
   srand( time(0)+stat +10);
   Dice dice3d6B(3,6);   
int b = dice3d6B.getValue(); 
      //  cout<<"stat choice: "<<a<<", "<<b;
    if(a>=b)
        statScore[stat] = a;
    else
        statScore[stat] = b;
    //        cout<<"Choose: "<<statScore[stat]<<endl;
    //statScore[stat]=10;
}

//USE enum easy naming
int Ability::getStat(int stat) //Stats stat)
{
    return statScore[stat];
}
string Ability::getStatName(int stat) //Stats stat)
{
	string val = "none";
		it = stats.begin();
	while(it!=stats.end() )
	{
	if(it -> second == stat)
		val = it->first;	
	it++;
	}

	return val;
}
void Ability::outputData()
{
 	cout<<"Stats are: "<<endl;
	int x;
	for(x = STR; x <= CHA; ++x)
	{
	cout <<getStatName(x)<<" = "<<getStat(x)<<endl;
	}

}
void Ability::levelUp(int Lvl)
{
//cout << "Lvl % 4 = " << Lvl %4 << ", so !this = "<<!(Lvl%4)<<endl;
	if(!(Lvl % 4)) //Ever 4 levels, increase Ability Score
	{
	int newStat;// statIndex;
	outputData();
	cout << "You can increase an Ability of your choice!"<< endl << "Which would you like to increase by 1? "; // STR, DEX, CON, INT, WIS, or CHA?";
	//map<string,Stats>::iterator it = stats.begin();
	// Iterate over the unordered_map using Iterator till end.
it = stats.begin();
	while (it != stats.end())
	{	
		string word = it->first;  // Accessing KEY from element pointed by it.
 		cout << ", "<< word ;
		it++;
	}
		cout<<": ";
	string ability;
bool found=false;
	while(!found)
	{
	cin >> ability;	

 		it = stats.begin();
		while(it!=stats.end() && !found)	//check input string is correct
		{
		string word = it->first;
		if(word == ability)
			{
			found = true;
			cout <<"ability found"<<endl;
			}
		it++;
		}
		if(!found)
			cout <<"Incorrect entry, try again."<<endl;
	}
	//cout << "entering ability adjustment phase"<<endl;
		newStat = getStat(getStats(ability)) + statIncrease;
		cout<<getStatName(getStats(ability))<<" was = "<< getStat(getStats(ability)) << endl;
		setStat(getStats(ability), newStat);

  } 	
}
int Ability::carryMaxLight()
{
	int weight = 7.83653* exp (0.1421202* getStat(STR));
	return weight;
}
	
	
#endif
