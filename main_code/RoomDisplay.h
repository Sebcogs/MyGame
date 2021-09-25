#ifndef ROOMDISPLAY_H
#define ROOMDISPLAY_H

//v5

#include<iostream>
//#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include "GameMap.h"

using namespace std;

class RoomDisplay
{
	private:
		
		Room aRoom;
	int RANDOMMOVE = 85;		//for random moves
		int xMAX;
		int yMAX;
		int players;
		int monsters;
		vector<int> xPlayer;
		vector<int> yPlayer;
		vector<int> xMonster;
		vector<int> yMonster;
		//char grid[10][10];  //hope a room is not bigger then 50by50
		//vector <char> ycols;
		vector <vector<char> > grid;
		//vector<char>ygrid;
	public:
		RoomDisplay(Room, int heroNumber);
		void createRoom();
		void move(char direct, int hero);
		void updateRoom(Room);
		void setPlayerPosition(string entrance);
		void setMonsterPosition(string entrance);
		//void updatePlayerPosition();
		double getDistance(int player, int monster=0);
		double getMonsterDistance(int monster1, int monster2=0);
        double getPlayerDistance(int player1, int player2);
		void moveMonster(int monster); //, int seed);
		string getTarget(int monster);
		void getTarget();
		int heroTarget(int monster);

};
#endif
