#ifndef PARSER_H
#define PARSER_H

//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
//#include "CommandWord.h"
//#include "Command.h"
#include "CommandMap.h"

using namespace std;


/*  Reads input from user and interperets it */

class Parser
{
	private:
		 CommandMap commands;
		//input reader...
	public:
		Parser();
		Command getCommand();	//Command is either normal command or party commands
		Command getFightCommand();
		void showCommands();
		void showNormalCommands();
		void showPartyCommands();
		void showFightCommands();

};

#endif
