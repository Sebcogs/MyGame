#include<iostream>
//#include<fstream>
#include<string>
#include<map>
#include "CommandWord.h"
using namespace std;
/*
* Holds a class to manage issued commands, 
*usually first of known CommandWord types, followed by a 
*second string word or null.
* (for example, if the command was "take map", then the two parts
* are TAKE and "map").
*
*/

class Command
{
    private:
		 CommandWord commandWord;
		string secondWord;
	public:
	//enum CommandWord{ GO, QUIT, HELP, UNKNOWN }
    // A value for each command word, plus one for unrecognised
    // commands.
		Command();
		Command(CommandWord, string);
		CommandWord getCommandWord();
		string getSecondWord();
		bool isUnknown();
		bool hasSecondWord();
		void setFields(CommandWord, string);
};
