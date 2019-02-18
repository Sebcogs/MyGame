#ifndef GAMEMAP_CPP
#define GAMEMAP_CPP
//v4
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
#include "GameMap.h"
#include<vector>
#include<algorithm>
#include "Dice.h"
using namespace std;

GameMap::GameMap()
{	
	//introText = "Nothing yet";
	//mapTitle = "No title yet";
	createRooms();
	currentRoom = rooms[0];
	currentEntrance = "none";
}
void GameMap::createRooms()
{
	setTitle(" A DARK AND STORMY KNIGHT - A D&D adventure for 3-4 1st lv Characters");
	setIntro("Your party of adventurers find themselves on a long road in the wilderness when thunder claps and lightning flashes and dark clouds begin to roll in. You make haste to find shelter from the storm...");

// create the rooms
		Room entry("the wilderness faced with a massive tor which towers above the surrounding country. There is a massive, arched entryway set into the side of the hill. Maybe inside you will be safe and dry. Well dry at least.");
       Room main2("a stone chamber beyond the Tor entrance");
        Room longHall4("a long hallway between the stone chamber to the south and a smaller room to the north");
		Room prepChamber4("a cluttered stone chamber with old tables holding iron tools. Rain falls through a hole in the ceiling that goes to the top of the broken tower. A rope dangles from the hole");
		Room Hall5("a long narrow hallway");
		Room web5("a small chamber whose wooden door lies on the floor. Numerous body-shaped lumps are visible each wrapped like woven mummies");
		Room offering6("a empty room save for dust and a single, small, stone chest in the center of the floor");
		Room getAhead7("a chamber where the only object of interest is a statue at the far end");
		Room Hall8("a stone hallway with a narrow branch to one side");
		Room darkKnight8("a chamber dominated by a long, stone table. Upon the table lies the well-preserved corpse of a tall humanoid wearing the tabard and belts of a knight");
		Room upCamp("the ruins of the tor after climbing the rope to the top of the shaft. All that is left is the broken outer stone wall of the tower. Looks like there once was a hobgoblin camp. The shaft and rope lead down into the ruins");
        
        // initialise room exits
        entry.setExit("north", main2);
		entry.setSize(20,20);

        main2.setExit("south", entry);
		main2.setExit("north", longHall4);
       main2.setExit("west", getAhead7);
       main2.setExit("east", offering6);
        
			main2.setSize(18, 16);

       offering6.setExit("west", main2);
			offering6.setSize(7,10);
		getAhead7.setExit("east", main2);
			getAhead7.setSize(7,9);

		longHall4.setExit("south", main2);
		longHall4.setExit("north", prepChamber4);
			longHall4.setSize(2,30);
		
		prepChamber4.setExit("south", longHall4);
		prepChamber4.setExit("north", Hall8);
		prepChamber4.setExit("up", upCamp);
			prepChamber4.setSize(10,10);
		
		Hall8.setExit("south", prepChamber4);
		Hall8.setExit("north", darkKnight8);
		Hall8.setExit("east", Hall5);
			Hall8.setSize(2, 10);
		darkKnight8.setExit("south", Hall8);
			darkKnight8.setSize(9,6);
		Hall5.setExit("west", Hall8);
		Hall5.setExit("east", web5);
			Hall5.setSize(13,1);
		web5.setExit("west", Hall5);
			web5.setSize(4 ,4);
		upCamp.setExit("down", prepChamber4);
			upCamp.setSize(8,8);
		//create encounters
		main2.setEncounter(3,8, 0, "north");  //use 8 spiders
		prepChamber4.setEncounter(9,2, 20, "north");  //2 hobgoblins
		web5.setEncounter(11,1,0);	//med spider
		getAhead7.setEncounter(12,1, 60, "west");	//vargouille
		darkKnight8.setEncounter(13,1,100);		//zombie bugbear


		//create some loot
srand( time(0) );
//cout <<"Create a chest to hold loot"<<endl;
int level = 1;
Dice percent(1,100);
	int percentRoll = percent.getValue();
Container chest("Chest", "A strong wooden chest", level, percentRoll);

srand( time(0) +percentRoll);
	Dice percent2(1,100);
	percentRoll = percent2.getValue();
	//	percentRoll = 96;
Container barrel("barrel", "An old wooden barrel", level, percentRoll);
	offering6.setLoot(chest);
	prepChamber4.setLoot(barrel);
	main2.setLoot(barrel);

	rooms.push_back(entry);
	rooms.push_back(main2);
	rooms.push_back(offering6);
	rooms.push_back(getAhead7);
	rooms.push_back(longHall4);
	rooms.push_back(prepChamber4);
	rooms.push_back(Hall8);
	rooms.push_back(darkKnight8);
	rooms.push_back(Hall5);
	rooms.push_back(web5);
	rooms.push_back(upCamp);
	
}
Room GameMap::getCurrentRoom()
{
	return currentRoom;
}

void GameMap::setCurrentRoom(Room room)
{
	
	for(unsigned int i=0; i != rooms.size(); i++)
	{	
		if(rooms.at(i).getShortDescription() == room.getShortDescription() )
		{
		currentRoom = rooms.at(i);
		}
	}
	//	cout<<currentRoom.getLongDescription()<<endl;
}
void GameMap::updateRoom(Room room)
{
	for(unsigned int i=0; i != rooms.size(); i++)
	{	
		if(rooms.at(i).getShortDescription() == room.getShortDescription() )
		{
		rooms.at(i) = room;
		currentRoom = room;
		}
	}
	//	cout<<currentRoom.getLongDescription()<<endl;
}
void GameMap::displayEntrance()
{
	cout<<"----You entered by the exit on the  "<<currentEntrance<<endl;
}
void GameMap::setEntrance(string temp)
{
		if(temp == "north")
			currentEntrance = "south";
		if(temp == "south")
			currentEntrance = "north";
		if(temp == "west")
			currentEntrance = "east";
		if(temp == "east")
			currentEntrance = "west";
		if(temp == "none")
			 cout<<"--Can't determine used exit in GameMap"<<endl;
}
string GameMap::getEntrance()
{
	return currentEntrance;
}
void GameMap::setIntro(string intro)
{
	introText = intro;
}
void GameMap::setTitle(string title)
{
	mapTitle = title;
}
void GameMap::displayIntro()
{
	//cout <<"-----Welcome to the Game!------"<<endl;
	//cout <<"     by Seb C"<<endl;
	//cout <<"Press any key to continue ";
	//cin.ignore(100, '\n');
	//cout << mapTitle <<endl;
	cout << endl << introText <<endl;
	cout <<"    Press any key to continue ";
	cin.ignore(100, '\n');
	cin.ignore(100, '\n');
	cout << endl;
}
void GameMap::displayTitle()
{
	cout <<"-----Welcome to the Game!  by SebC------"<<endl;
	//cout <<"   "<<endl <<endl;
	//cout <<"    Press any key to continue ";
	//cin.ignore(100, '\n');
	cout <<"The currently loaded gamemap is:"<<endl;
	cout << mapTitle <<endl;
	cout <<"    Press any key to continue ";
	cin.ignore(100, '\n');
}

#endif
