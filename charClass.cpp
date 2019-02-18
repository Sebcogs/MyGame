//v4
#ifndef CHARCLASS_CPP
#define CHARCLASS_CPP

#include<iostream>
#include<string>
#include<iomanip>
#include <map>
//#include <unordered_map>
#include <iterator>
//#include "Dice.h"
#include "charClass.h"


using namespace std;

charClass::charClass()
{	//set member variables to default
className = "None";
hitDice = 4;
Atk =0;
for(int i=0; i<3; i++)
  saveThrow[i]=0;

setMap();		//setup enum unordered_maps with proper names

	map<Saves, string>::iterator it = saves.begin();
	while(it != saves.end())  //set up savingthrow names
		{
		saveThrowName[it->first] = it->second;
		it++;
		}
}
void charClass::setFields(string name)
{
	setFields( getStyle(name));
}
void charClass::setFields()
{
string type;
    cout <<"Choose a Class";  
	map<string, Styles>::iterator it = styles.begin();
	// Iterate over the unordered_map using Iterator till end.
	while (it != styles.end())
	{	
		string word = it->first;  // Accessing KEY from element pointed by it.
 		cout << ", "<< word ;
		it++;
	}
		cout<<": ";

   cin >> type;
	try{
setFields( getStyle(type));
	}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	cout <<"I guess you won't have a specific class..."<<endl;
	cout<< "You entered "<<type<<endl;
	}

}

void charClass::setMap()
{
	/*styles[BARB] = "Barbarian";
	styles[BARD] = "Bard";
	styles[FIGH] = "Fighter";
	styles[RANG] = "Ranger";
	styles[CLER] = "Cleric";*/
	styles["Barbarian"] = BARB;
	styles["Bard"] = BARD;
	styles["Fighter"] = FIGH;
	styles["Cleric"] = CLER;
	styles["Ranger"] = RANG;
	
	saves[FORT] = "Fort";
	saves[REF] = "Reflex";
	saves[WIL] = "Will";


}
void charClass::setFields(Styles style)
{
	
const string MSG = "class input error";
switch(style) {
        case 0 : 
            className = "Barbarian";
           // classIndex = 0;
            hitDice = 12;
            Atk = 1;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 0;
        break;
        case 1:
            className = "Bard";
          //  classIndex = 1;
            hitDice = 6;
            Atk = 0;
			saveThrow[FORT] = 0;
			saveThrow[REF] = 2;
			saveThrow[WIL] = 2;
        break;
        case 2:
            className = "Fighter";
         //   classIndex = 2;
            hitDice = 10;
            Atk = 1;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 0; 
        break;
        case 3:  
            className = "Cleric";
          //  classIndex = 3;
            hitDice = 8;
            Atk = 0;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 0;
			saveThrow[WIL] = 2; 
        break;
        case 4:
            className = "Ranger";
         //   classIndex = 4;
            hitDice = 8;
            Atk = 1;
			saveThrow[FORT] = 2;
			saveThrow[REF] = 2;
			saveThrow[WIL] = 0; 
        break;
        default : cout<<"Invalid Race type"<<endl;
			throw(MSG);
    }

}
void charClass::outputData()
{
    cout <<"Class: " << className <<" with d"<< hitDice << " HitDice"<< endl;
	cout <<"Atk: "<<Atk;
		map< Saves,string>::iterator it = saves.begin();
	// Iterate over the unordered_map using Iterator till end.
	cout << ", Saving throws;";
	while (it != saves.end())
	{	
		// Accessing KEY from element pointed by it.
 		cout << " "<< it->second <<": "<<saveThrow[it->first];
		it++;
	}
	cout << endl;
}
int charClass::getAtk()
{
    return Atk;
}
int charClass::getHitDice()
{
    return hitDice;
}

void charClass::levelUp(int newlevel)
{
	const string MSG = "Error in finding correct Class to level up!!";
	//cout << "Class Name: " << className <<endl;
	switch(getStyle(className)){
        case 0 : 
           // className = "Barbarian";
         Atk++;
		if(!(newlevel % 2))
		{
		saveThrow[FORT]++;
		}
		if(!(newlevel % 3))
		{
		saveThrow[REF]++;
		saveThrow[WIL]++;
		}  
        break;
        case 1:
           // className = "Bard";  
		if(!(newlevel % 3))
			{
			saveThrow[FORT]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[REF]++;
			saveThrow[WIL]++;
			}       
        if(newlevel == 5 || newlevel == 9 || newlevel == 13 || newlevel == 17)
			{
			}
		else
	    	Atk++;
        break;
        case 2:
           // className = "Fighter";
            Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[REF]++;
			saveThrow[WIL]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			}       
        break;
        case 3:  
           //   className = "Cleric";
        if(newlevel == 5 || newlevel == 9 || newlevel == 13 || newlevel == 17)
			{
			}
		else
	    	Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[REF]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			saveThrow[WIL]++;
			}       
            
        break;
        case 4:
            //  className = "Ranger";           
            Atk++;
		if(!(newlevel % 3))
			{
			saveThrow[WIL]++;
			}
		if(!(newlevel % 2))
			{
			saveThrow[FORT]++;
			saveThrow[REF]++;
			}       
        break;
        default : cout<<"Invalid Race type"<<endl;
			throw(MSG);
    }
	outputData();
}
charClass::Styles charClass::getStyle(string input) 
{
	return styles.find(input) -> second;
}
charClass::Saves charClass::getSaves(string input)
{
		map<Saves,string>::iterator it = saves.begin();
	while(it!=saves.end() || it -> second != input)
	{
		
	it++;
	}
	return it -> first; //return saves.find(input) -> first;
}
string charClass::getClassName()
{
	return className;
}
int charClass::getSaveThrow(int saves)
{
	if(saves <= 0 || saves <= Saves::WIL)
   		 return saveThrow[saves];
	else {
    	cout <<"can't get SavingThrow value, out of range.  Must be: ";
		cout << Saves::FORT << ", " << Saves::REF;
		cout <<" and " << Saves::WIL <<endl;
   	 return 0;
		}
}
string charClass::getSaveName(unsigned int save)
{
	string name ="";
	if(save >=0 || save <= saves.size())
		{
		name = saveThrowName[save];
		}
	else
		{
		cout << "Something wrong in getSaveName, int out of range"<<endl;
		}
		return name;

}
#endif
