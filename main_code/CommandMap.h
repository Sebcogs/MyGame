#ifndef COMMANDMAP_H
#define COMMANDMAP_H

//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
//#include "CommandWord.h"
#include "Command.h"
using namespace std;

class CommandMap
{
    // A mapping between a command word and the CommandWord
    // associated with it.
    private:
		map<string, CommandWord> validCommands;
		map<string, CommandWord> partyCommands;
		map<string, CommandWord> fightCommands;
	public:
		 CommandMap();
		CommandWord getCommandWord(string);
		CommandWord getPartyWord(string);
		CommandWord getFightWord(string);
		bool isCommand(string);
		bool isParty(string);
		bool isFight(string);
		void showAll();
		void showNormal();
		void showParty();
		void showFight();

};
#endif
