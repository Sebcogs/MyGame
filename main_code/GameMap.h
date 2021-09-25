#ifndef GAMEMAP_H
#define GAMEMAP_H
//v4
#include<iostream>
//#include<fstream>
#include<string>
#include<map>
#include "Room.h"
#include<vector>
using namespace std;

class GameMap
{
	private:
		Room currentRoom;
		vector<Room>rooms;
		string introText;
		string mapTitle;
		string currentEntrance;
	public:
		GameMap();
		void createRooms();
		Room getCurrentRoom();
		void setCurrentRoom(Room);
		void updateRoom(Room);
		void displayEntrance();
		void setEntrance(string direction);
		string getEntrance();
		void setIntro(string);
		void setTitle(string);
		void displayIntro();
		void displayTitle();
};
#endif
