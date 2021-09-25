#include "SaveThrow.h"
#include <map>
//#include <unordered_map>
#include <iterator>

SaveThrow::SaveThrow()
{
	//set everything to 0
	for(int x=FORT; x<=Saves::NONE; ++x)
	{
		saveThrow[x] = 0;
		raceBonus[x]=0;
		tempBonus[x]=0;
		statMod[x] = 0;
	}
		//create map
	specialTypeMod[GENERIC] = 0;
	specialTypeMod[POISON] = 0;
	specialTypeMod[FEAR] = 0;
	specialTypeMod[SLEEP] = 0;
	specialTypeMod[ILLUSION] = 0;
	specialTypeMod[ENCHANTMENT] = 0; 
	
	saveThrowName[FORT] = "Fort";
	saveThrowName[REF] = "Reflex";
	saveThrowName[WIL] = "Will";
	saveThrowName[Saves::NONE] = "None";
}

SaveThrow::~SaveThrow()
{
}

void SaveThrow::setFields(int fort, int reflex, int will)
{
		saveThrow[FORT] = fort;
		saveThrow[REF] = reflex;
		saveThrow[WIL] = will;
}
void SaveThrow::setRaceFields(int fort, int reflex, int will)
{
	raceBonus[FORT] = fort;
	raceBonus[REF] = reflex;
	raceBonus[WIL] = will;
}

void SaveThrow::updateTempBonus(int fort, int reflex, int will)
{
	tempBonus[FORT] = fort;
	tempBonus[REF] = reflex;
	tempBonus[WIL] = will;
} 
void SaveThrow::updateStatMod(int con, int dex, int wis)
{
	statMod[FORT] = con;
	statMod[REF] = dex;
	statMod[WIL] = wis;
}
void SaveThrow::setSpecialFields(int values[SPECIAL_TYPE_NUMBER])
{
	
		int x=0;
		map<specialType, int>::iterator it = specialTypeMod.begin();
	// Iterate over the unordered_map using Iterator till end.
	while (it != specialTypeMod.end())
	{	
		// Accessing KEY from element pointed by it.
 		specialTypeMod[it->first]=values[x];
		it++;
		x++;
	} 
}
int SaveThrow::getSaveThrow(Saves save)
{
	return saveThrow[save]+raceBonus[save] +tempBonus[save]+statMod[save];
}
int SaveThrow::getSaveThrow(Saves save, specialType special)
{
	int value;
	value = getSaveThrow(save) + specialTypeMod.find(special) -> second;
	return value;
}
string SaveThrow::getSaveName(Saves save)
{
	return saveThrowName[save];
}
Saves SaveThrow::intToSave(int input)
{
	   		Saves i_Enum;
		switch (input){
		case 0:
			i_Enum = FORT;
			break;
		case 1:
			i_Enum = REF;
			break;
		case 2:
			i_Enum = WIL;
			break;
		case 3:
			i_Enum = NONE;
            break;
        default:
            i_Enum = NONE;
        }
    return i_Enum;
}
void SaveThrow::outputData()
{
	cout<<"Save throws are: "<<endl;
	for(int x=FORT; x<=WIL; x++)
	{
		cout<<getSaveName(intToSave(x))<<": "<<getSaveThrow(intToSave(x));
		if(raceBonus[x]!=0)
			cout<<" (race bonus: "<<raceBonus[x]<<")";
		if(tempBonus[x]!=0)
			cout<<" (temp bonus: "<<tempBonus[x]<<")"; 
		if(statMod[x]!=0)
			cout<<" (stat mod: "<<statMod[x]<<")";
		cout<<", ";
	}
	map<specialType, string> specialAtkNames = create_SpecialsMap();
	cout<<endl;
	
	map<specialType, int>::iterator it = specialTypeMod.begin();
	map<specialType, string>::iterator iter = specialAtkNames.begin();
	while (it != specialTypeMod.end())
	{	
		// Accessing KEY from element pointed by it.
		if(specialTypeMod[it->first]!=0)
		{
			cout<<specialAtkNames[iter->first]<<": "<<specialTypeMod[it->first]<<endl;
		}
 		//specialTypeMod[it->first]=values[x];
		it++;
		iter++;
	} 
}