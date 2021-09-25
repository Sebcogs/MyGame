#ifndef COMMANDMAP_CPP
#define COMMANDMAP_CPP
//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
//#include "CommandWord.h"
//#include "Command.h"
#include "CommandMap.h"
using namespace std;


    /**
     * Constructor - initialise the command words.
     */
CommandMap::CommandMap()
    {
        //validCommands = new HashMap<String, CommandWord>();
        validCommands["party"] = PARTY;
		validCommands["go"] = GO; //CommandWord.GO;
        validCommands["help"] = HELP; //CommandWord.HELP;
        validCommands["quit"] = QUIT;  //CommandWord.QUIT;
		validCommands["take"] = TAKE;
		validCommands["look"] = LOOK;
        validCommands["caste"] = CASTE;

		partyCommands["info"] = CHAR; //PartyCommand.CHAR;
		partyCommands["equip"] = EQUIP;
		partyCommands["unequip"] = UNEQUIP;
		partyCommands["order"] = MARCH;
		partyCommands["item"] = ITEM;
    
		//validCommands[] = UNKNOWN; //CommandWord.UNKNOWN;
		
		fightCommands["attack"] = ATTACK;
		fightCommands["flee"] = FLEE;
		fightCommands["item"] = ITEM;
		fightCommands["move"] = MOVE;
		fightCommands["quit"] = QUIT;
		fightCommands["equip"] = EQUIP;
		fightCommands["unequip"] = UNEQUIP;
        fightCommands["caste"] = CASTE;
		fightCommands["turn"] = TURN;
		
    }

    /**
     * Find the CommandWord associated with a command word.
     * @param commandWord The word to look up.
     * @return The CommandWord correspondng to commandWord, or UNKNOWN
     *         if it is not a valid command word.
     */
CommandWord CommandMap::getCommandWord(string word)
    {
      return validCommands.find(word) -> second;
      
    }

CommandWord CommandMap::getPartyWord(string word)
   {
      return partyCommands.find(word) -> second;
      
    }  
CommandWord CommandMap::getFightWord(string word)
   {
      return fightCommands.find(word) -> second;
      
    }  
    /**
     * Check whether a given String is a valid command word. 
     * @return true if it is, false if it isn't.
     */
bool CommandMap::isCommand(string aString)
    {	
		bool found = false;

		if(validCommands.find(aString)!= validCommands.end())
			found = true;
			
        return found;
    }

bool CommandMap::isParty(string aString)
	{
		bool found = false;
		if(partyCommands.find(aString)!= partyCommands.end())
			found = true;

       return found;
    }
bool CommandMap::isFight(string aString)
	{
		bool found = false;
		if(fightCommands.find(aString)!= fightCommands.end())
			found = true;

       return found;
    }

    /**
     * Print all valid commands to System.out.
     */
void CommandMap::showAll() 
{
	showNormal();
	showParty();
}

void CommandMap::showNormal()
{
	cout<<"	Normal commands: ";      
	  map<string, CommandWord>::iterator it = validCommands.begin();
	// Iterate over the map using Iterator till end.
	while (it != validCommands.end())
	{	
		string word = it->first;  // Accessing KEY from element pointed by it.
 		cout << " "<< word ;
		it++;
	}
		cout<<": "<<endl;
}
void CommandMap::showParty()
{
	cout<<"	Party or characters commands: ";      
	  map<string, CommandWord>::iterator iter = partyCommands.begin();
	// Iterate over the map using Iterator till end.
	while (iter != partyCommands.end())
	{	
		string word = iter->first;  // Accessing KEY from element pointed by it.
 		cout << " "<< word ;
		iter++;
	}
		cout<<": "<<endl;

}
void CommandMap::showFight()
{
	cout<<"	Battle commands: ";      
	  map<string, CommandWord>::iterator iter = fightCommands.begin();
	// Iterate over the map using Iterator till end.
	while (iter != fightCommands.end())
	{	
		string word = iter->first;  // Accessing KEY from element pointed by it.
 		cout << " "<< word ;
		iter++;
	}
		cout<<": "<<endl;

}
#endif


