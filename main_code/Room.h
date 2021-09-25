#ifndef ROOM_H
#define ROOM_H
//v4
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
#include "inventory/Container.h"
#include "Encounter.h"

using namespace std;
/**
 * Class Room - a room in an adventure game.
 *
 * This class is part of the "World of Zuul" application. 
 * "World of Zuul" is a very simple, text based adventure game.  
 *
 * A "Room" represents one location in the scenery of the game.  It is 
 * connected to other rooms via exits.  For each existing exit, the room 
 * stores a reference to the neighboring room.
 * 
 * @author  Michael Kolling and David J. Barnes
 * @version 2008.03.30
 */

class Room 
{
    private:
		string description;
		map<string, Room> exits;        // stores exits of this room.
		int width;
		int length;
		
		bool hasLoot;
		bool hasEncounter;
		

	public:
		vector<Container> chest;
		Encounter enemies;
		Room();
		Room(string);
		void setExit(string, Room);
		string getShortDescription();
		string getLongDescription();
		string getExitString();
		void display();
		Room getExit(string);	
		bool isExit(string);
		void setSize(int, int);
		int getWidth();
		int getLength();
		void setLoot(Container container);
		bool getHasLoot();
		void setEncounter(int level); //overloaded for random
		void setEncounter(int ID, int number, int reward, string position = "center"); //overloaded for defined
		bool getHasEncounter();
		void lookLoot();
};
#endif
