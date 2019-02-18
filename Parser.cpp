//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<sstream>
#include<map>
//#include "CommandWord.h"
//#include "Command.h"
#include "Parser.h"
using namespace std;

/*  Reads input from user and interperets it */


    /**
     * Create a parser to read from the terminal window.
     */
    Parser::Parser() 
    {
         CommandMap commands;
      //  reader = new Scanner(System.in);
    }

    /**
     * @return The next command from the user.
     */
Command Parser::getCommand() 
    {
        Command myCommand;
           string word1 = "";
        string word2 = "";
 		char space = ' ';
		string inputstream;
//string blank;

	//cout<<"left over input: "<<blank<<endl;

        cout << "	(Enter Command )>: ";    
	getline(cin, inputstream); 
	
		istringstream iss(inputstream);
	getline(iss, word1, space);
	
	string::size_type position = inputstream.find (' ');

	if(position!=string::npos)
		word2 = inputstream.substr(position+1);
		
	//else
		//cout<<"there is no second word"<<endl;
   		if(commands.isCommand(word1))
		{//	cout <<"normal command entered: "<< word1 <<endl;
	myCommand.setFields(commands.getCommandWord(word1), word2);
		}
		 else if(commands.isParty(word1))
		{//	cout <<"party commmand entered: "<<word1 <<endl;
	myCommand.setFields(commands.getPartyWord(word1), word2);
		}
	else //(!commands.isCommand(word1))
	{ /*
	Command myCommand(commands.getCommandWord(word1), word2);
	return myCommand;	
	}
	else
	{*/
	//cout<< "Parser getCommand() .isCommand failed.  using myCommand.isUnknown()"<<endl;
//	Command myCommand(commands.getCommandWord(word1), word2);
//	myCommand.isUnknown();
       //return myCommand; 
	 }
   return myCommand;
}

    /**
     * Print out a list of valid command words.
     */
void Parser::showCommands()
    {
        commands.showAll();
    }
void Parser::showNormalCommands()
    {
        commands.showNormal();
    }
void Parser::showPartyCommands()
    {
        commands.showParty();
    }
void Parser::showFightCommands()
	{
		commands.showFight();
	}

Command Parser::getFightCommand() 
    {
        Command myCommand;
           string word1 = "";
        string word2 = "";
 		char space = ' ';
		string inputstream;

	//showFightCommands();
        cout << "	(Enter Fight Command )>: ";    
	getline(cin, inputstream); 
	
		istringstream iss(inputstream);
	getline(iss, word1, space);
	
	string::size_type position = inputstream.find (' ');

	if(position!=string::npos)
		word2 = inputstream.substr(position+1);
		
	//else
		//cout<<"there is no second word"<<endl;
   		if(commands.isFight(word1))
		{//	cout <<"normal command entered: "<< word1 <<endl;
	myCommand.setFields(commands.getFightWord(word1), word2);
		}
	else 
	{
	//cout<< "Parser getCommand() .isCommand failed.  using myCommand.isUnknown()"<<endl;

	 }
   return myCommand;
}
