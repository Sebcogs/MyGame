#ifndef COMMAND_CPP
#define COMMAND_CPP


#include<iostream>
//#include<fstream>
#include<string>
#include<map>
//#include "CommandWord.h"
#include "Command.h"
using namespace std;
/*
* Holds a class to manage issued commands, 
*usually first of known CommandWord types, followed by a 
*second string word or null.
* (for example, if the command was "take map", then the two parts
* are TAKE and "map").
*
*/
Command::Command()
{
		commandWord = UNKNOWN;
        secondWord = "";
}

Command::Command(CommandWord comdWord, string secWord)
    {
        commandWord = comdWord;
        secondWord = secWord;
    }

    /**
     * Return the command word (the first word) of this command.
     * @return The command word.
     */
CommandWord Command::getCommandWord()
    {
        return commandWord;
    }

    /**
     * @return The second word of this command. Returns null if there was no
     * second word.
     */
string Command::getSecondWord()
    {
        return secondWord;
    }

    /**
     * @return true if this command was not understood.
     */
bool Command::isUnknown()
    {
		bool test = false;
 	if(commandWord == UNKNOWN)
		{
		commandWord = UNKNOWN;
		test = true;
		}		
        return test; //assign the commandWord to enum UNKNOWN
    }

    /**
     * @return true if the command has a second word.
     */
bool Command::hasSecondWord()
    {
	bool isword = false;
	if( secondWord.length() > 1)
		isword=true;
	//cout<<"Second Word "<<secondWord<<" is "<<secondWord.length()<<" long and will return bool "<<isword<<endl;
        return isword;
    }

void Command::setFields(CommandWord comdWord, string secWord)
    {
        commandWord = comdWord;
        secondWord = secWord;
	//	cout <<"fields set in Command.cpp"<<endl;
    }

#endif

