//v4
#ifndef CHARCLASS_CPP
#define CHARCLASS_CPP

#include<iostream>
#include<string>
#include<iomanip>
#include <map>
#include <unordered_map>
#include <iterator>
//#include "Dice.h"
#include "charClass.h"


using namespace std;
map<Styles, string> create_Stylesmap()
{
	map<Styles, string> s;
	s[BARB] = "Barbarian";
	s[BARD] = "Bard";
	s[CLER] = "Cleric";
	s[FIGH] = "Fighter";
	s[RANG] = "Ranger";
	s[WIZ]  = "Wizard";
	return s;
}
map<string, Styles> create_StyleStringmap()
{
	map<string, Styles > sS;
	sS["Barbarian"] = BARB;
	sS["Bard"] = BARD;
	sS["Fighter"] = FIGH;
	sS["Cleric"] = CLER;
	sS["Ranger"] = RANG;
	sS["Wizard"] = WIZ;
	return sS;
	}

charClass::charClass()
{	//set member variables to default
className = "None";
hitDice = 4;
Atk =0;
for(int i=0; i<3; i++)
  saveThrow[i]=0;
  
//classmagic = new Magic();

setMap();		//setup enum unordered_maps with proper names

	map<Saves, string>::iterator it = saves.begin();
	while(it != saves.end())  //set up savingthrow names
		{
		saveThrowName[it->first] = it->second;
		it++;
		} 
}

void charClass::setMap()
{
	styles = create_StyleStringmap();
	/*styles["Barbarian"] = BARB;
	styles["Bard"] = BARD;
	styles["Fighter"] = FIGH;
	styles["Cleric"] = CLER;
	styles["Ranger"] = RANG; */
	
	saves[FORT] = "Fort";
	saves[REF] = "Reflex";
	saves[WIL] = "Will"; 


}

void charClass::outputData()
{
    cout <<"Class: " << className <<" with d"<< hitDice << " HitDice"<< endl;
	cout <<"Base Atk: "<<Atk;
		map< Saves,string>::iterator it = saves.begin();
	// Iterate over the unordered_map using Iterator till end.
	cout << ", Base Saving throws;";
	while (it != saves.end())
	{	
		// Accessing KEY from element pointed by it.
 		cout << " "<< it->second <<": "<<saveThrow[it->first];
		it++;
	}
	cout << endl;
	classmagic->outputdata();
	turning->outputData();
	
}
int charClass::getAtk()
{
    return Atk;
}
int charClass::getHitDice()
{
    return hitDice;
}
Styles charClass::getStyle(string input) 
{
	return styles.find(input) -> second;
}
/*
Saves charClass::getSaves(string input)
{
		map<Saves,string>::iterator it = saves.begin();
	while(it!=saves.end() || it -> second != input)
	{
		
	it++;
	}
	return it -> first; //return saves.find(input) -> first;
} */
string charClass::getClassName()
{
	return className;
}

int charClass::getSaveThrow(int saves)
{
	if(saves >= 0 || saves <= WIL) //Saves::WIL)
   		 return saveThrow[saves];
	else {
    	cout <<"can't get SavingThrow value, out of range.  Must be: ";
		//cout << Saves::FORT << ", " << Saves::REF;
		//cout <<" and " << Saves::WIL <<endl;
   	 return 0;
		}
}
/*
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

} */
string charClass::getStartingGear()
{
    return startingGear;
}



charClass * CharClassCreator::getClass()
	{
		//cout<<"in charClassCreator getClass()"<<endl;
	
	map<Styles, string> styles = create_Stylesmap();
	
		int type;
    cout <<"Choose a Class";  
	map<Styles, string >::iterator it = styles.begin();
	// Iterate over the unordered_map using Iterator till end.
	
	while (it != styles.end())
		{	
		string word = it->second;  // Accessing KEY from element pointed by it.
		int place = it->first;
 		cout << ", #"<<place<<": "<< word ;
		
		it++;
		}
		cout<<": ";

   cin >> type;
   charClass *temp = getClass(type);
		return temp;
	}
	
charClass * CharClassCreator::getClass(string choice)
{
	map<string, Styles > styles = create_StyleStringmap();
	/*styles["Barbarian"] = BARB;
	styles["Bard"] = BARD;
	styles["Fighter"] = FIGH;
	styles["Cleric"] = CLER;
	styles["Ranger"] = RANG; */
	int type;
		type = styles.find(choice) ->second; 
	charClass *temp = getClass(type);
		return temp;
}
charClass * CharClassCreator::getClass(unsigned int type)
{
	switch(type) {
		case 0:
			return new BarbClass;
			break;
		case 1:
			return new BardClass;
			break;
		case 2:
			return new FighterClass;
			break;
		case 3:
			return new ClericClass;
			break;
		case 4:
			return new RangerClass;
			break;
		case 5:
			return new WizardClass;
			break;
		case 6:
			return new NoClass;
			break;
		default:
			cout <<"invalid input, you will have no class"<<endl;
			return new NoClass;
		}
}
#endif
