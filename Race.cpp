#ifndef RACE_CPP
#define RACE_CPP
//v4
#include<iostream>
#include<string>
#include <map>
//#include <unordered_map>
#include <iterator>
#include "Race.h"

using namespace std;

Race::Race()
{
raceName = "Human";
for(int count=0; count<statNumber; count++)
    mod[count] = 0;
	size = 'm';
	setMap();
}
/* Race::~Race()
{
	//delete only works for pointer ? destructor kind of pointless in this case...	
	//delete raceName;
	//delete size;
	//delete mod[];
	//delete raceIndex;
} */
void Race::setMap()
{
	races["Human"] = HUM;
	races["Elf"] = ELF;
	races["Dwarf"] = DWA;
	races["Halfling"] = HAF;

}
void Race::setFields()
{
string type;
   cout <<"Choose a race";  //H for human, E for elf, D for dwarf, A for Halfling: "<<endl;
map<string,Races>::iterator it = races.begin();
	// Iterate over the map using Iterator till end.
	while (it != races.end())
	{	
		string word = it->first;  // Accessing KEY from element pointed by it.
 		cout << ", "<< word ;
		it++;
	}
		cout<<endl;

    cout<<"Don't forget the racial modes:"<<endl;
	cout<<" Elf->Dex+2,Con-2; Dwarf->Con+2,CHar-2; Halfling->Dex+2,STR-2  ";
   cin >> type;
	try{
setFields( getRace(type));
	}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	cout <<"I guess you have to be Human..."<<endl;
	cout<< "You entered "<<type<<endl;
	}


}
void Race::setFields(string name)
{
	setFields( getRace(name));
}
void Race::setFields(Races race)
{
   const string MSG = "Race input error"; 
    switch(race){  
        case 0 : 
            raceName = "Human";
        //    raceIndex = 0;
            size = 'm';
        break;
        case 1:
            raceName = "Elf";
         //   raceIndex = 1;
            size = 'm';
            mod[DEX] = 2;
            mod[CON] = -2;
        break;
        case 2:
            raceName = "Dwarf";
         //   raceIndex = 2;
            size = 'm';
            mod[CON] = 2;
            mod[CHA] = -2;
        break;
        case 3:
            raceName = "Halfling";
          //  raceIndex = 3;
            size = 's';
            mod[DEX] = 2;
            mod[STR] = -2;
        break;
        default : cout<<"Invalid Race type"<<endl;
			throw(MSG);
    }
} 
void Race::outputData()
{
    cout<< "You are: " << raceName << " and are size: "<<size <<endl;
}

int Race::getMod(int stat)
{
    return mod[stat];
}
char Race::getSize()
{
    return size;
}

int Race::getsizeMod()
{
	int mod;
	if(getSize() == 's')
		mod = 1;
	else
		mod=0;
	return mod;
}
Race::Races Race::getRace(string input)
{
	return races.find(input) -> second;
}
string Race::getRaceName()
{
	return raceName;
}
#endif


