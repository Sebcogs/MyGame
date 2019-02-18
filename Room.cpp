#ifndef ROOM_CPP
#define ROOM_CPP

//v5
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include "Room.h"
//#include "Container.h"
    /**
     * Create a room described "description". Initially, it has
     * no exits. "description" is something like "a kitchen" or
     * "an open court yard".
     * @param description The room's description.
     */
Room::Room()
{
	description = "Nothing here yet";
	width = 0;
	length = 0;
	//Container container;
	chest.clear(); // = container;
	hasLoot = false;
	hasEncounter = false;
	Encounter aEncounter;
	enemies = aEncounter;
	
}
Room::Room(string desc) 
    {
        description = desc;
		width = 0;
	length = 0;
	//Container container;
	chest.clear(); // = container;
	hasLoot = false;
hasEncounter = false;
	Encounter aEncounter;
	enemies = aEncounter;
	
	//	cout<<"Room created with desc: "<<description<<endl;
        //map<string, Room> exits;
    }

    /**
     * Define an exit from this room.
     * @param direction The direction of the exit.
     * @param neighbor  The room to which the exit leads.
     */
void Room::setExit(string direction, Room neighbor) 
    {
	//	cout<< "direction: "<<direction<<" added"<<endl;
        exits[direction] = neighbor;
    }

    /**
     * @return The short description of the room
     * (the one that was defined in the constructor).
     */
string Room::getShortDescription()
    {
        return description;
    }

    /**
     * Return a description of the room in the form:
     *     You are in the kitchen.
     *     Exits: north west
     * @return A long description of this room
     */
string Room::getLongDescription()
    {
        return "You are in " + description + ".\n" + getExitString() + ".\n";
    }

void Room::display()
{
	cout <<"You are in "<<getShortDescription()<<"."<<endl;
	if(hasLoot)
		{
		cout <<"You also see a ";
		for(unsigned int i=0; i<chest.size(); i++)
			chest[i].getDesc();
		}
		cout << getExitString()<<endl;
	if(hasEncounter)
		{
		Monster aMonster = enemies.getMonster(0);
		cout <<"There are "<<enemies.getNumberAppear() <<" "<< aMonster.getName() <<" ready to attack here!"<<endl;
		}
} 

    /**
     * Return a string describing the room's exits, for example
     * "Exits: north west".
     * @return Details of the room's exits.
     */
string Room::getExitString()
    {
	string val = "Exits:";
		map<string,Room>::iterator it = exits.begin();
	while(it!=exits.end() )
	{
		val += " " + it->first;	
	it++;
	}

	return val;

     /*   string returnString = "Exits:";
        Set<String> keys = exits.keySet();
        for(string exit : keys) {
            returnString += " " + exit;
        }
        return returnString;
	*/
    }

    /**
     * Return the room that is reached if we go from this room in direction
     * "direction". If there is no room in that direction, return null.
     * @param direction The exit's direction.
     * @return The room in the given direction.
     */
Room Room::getExit(string direction) 
    {	
		
        return exits.find(direction) -> second;
    }
bool Room::isExit(string direction)
{	
	bool exists = false;
	map<string, Room>::iterator it = exits.begin();
		it = exits.find(direction);
		if( it != exits.end())
		{
	//	cout << "exit that direction exists" <<endl;
		exists = true;
		}
	return exists;
}
void Room::setSize(int wide, int len)
{
	width = wide;
	length = len;
}
int Room::getWidth()
{
	return width;
}
int Room::getLength()
{
	return length;
}
void Room::setLoot(Container container)
{
	//Container container(type, desc, level, percentRoll);
	chest.push_back(container);
	hasLoot = true;
}
bool Room::getHasLoot()
{
	return hasLoot;
}

void Room::setEncounter(int level)
{
	Encounter aEncounter(level);
	enemies = aEncounter;
	hasEncounter = true;
}

void Room::setEncounter(int ID, int number, int reward, string position )
{
	Encounter aEncounter(ID, number, reward);
	enemies = aEncounter;
	hasEncounter = true;
	enemies.setLocation(position);
}

bool Room::getHasEncounter()
{
	bool killed = enemies.isDefeated();
	string name = enemies.getMonster(0).getName();
	//cout<<"In Room.cpp; test hasEncounter: "<<hasEncounter<<" and isDefeated(): "<<killed<<endl;
	if(hasEncounter && killed)
		{
		cout <<"Monster defeated!!"<<endl;
		hasEncounter = false;
	//	cout <<"hasEncounter set to "<< hasEncounter<<endl;
		string desc = "The dead body of the " + name;
		int treasure = enemies.getTreasureValue();
		Container corpse("Corpse", desc, 1, treasure);
		
		setLoot(corpse);
		}
	//	cout <<"Room::getHasEncounter returns: "<<hasEncounter<<endl; 
	return hasEncounter;
}
#endif

