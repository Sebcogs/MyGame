//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<vector>
//#include<map>
#include <math.h>
#include "RoomDisplay.h"

using namespace std;


RoomDisplay::RoomDisplay(Room current, int heroNumber)
{
	
//	cout <<"In constructor"<<endl;
	players = heroNumber;
	aRoom = current;
	yMAX = aRoom.getWidth()+2;
	xMAX = aRoom.getLength()+2;  //add 2, 1 for each wall
	//cout <<"xMAX and yMAX : "<<xMAX<<" "<<yMAX<<endl;
	grid.resize(xMAX, vector<char>(yMAX,'a'));
	//cout <<"Grid created"<<endl;
	
	for(int u = 1; u < xMAX-1; u++)
		{		
		for(int v = 1; v < yMAX-1; v++)
			{
		//cout << "assign space to the centre of the grid"<<endl;
			grid[u][v] = ' ';
			}
		}
	for(int u = 0; u < xMAX; u++)
		{
		//cout <<" assign '0' to the grid edges"<<endl;
		grid[u][0] = '0';
		grid[u][yMAX-1] = '0';
		for(int v = 0; v < yMAX; v++)
			{
			grid[0][v] = '0';
			grid[xMAX-1][v] = '0';
			}
		}
	// cout <<"Set player position"<<endl;
	//Set player position, should be from entrance
//	xPlayer = xMAX/2;
//	yPlayer = 1;
//	grid[xPlayer][yPlayer] = 'P';

	//create exits
	if(current.isExit("north"))
 	grid[0][yMAX/2]= ' ';
	if(current.isExit("south"))
	grid[xMAX-1][yMAX/2] = ' ';
	if(current.isExit("west"))
	grid[xMAX/2][0] = ' ';
	if(current.isExit("east"))
	grid[xMAX/2][yMAX-1] = ' ';

	if(aRoom.getHasLoot())
		grid[xMAX/2][yMAX/2] = 'C';
	if(aRoom.getHasEncounter())
		{
		monsters = aRoom.enemies.getNumberAppear();
		string location = aRoom.enemies.getLocation();
		setMonsterPosition(location);

		}
}
/*
RoomDisplay::~RoomDisplay()
{
	for (int i = 0; i < MAXsize; i++)
  	{
  		delete[]grid[i];
  	}
	delete[]grid;

} */

void RoomDisplay::createRoom()
{
//	cout<<"display the grid"<<endl;
	//cout <<"xMAX and yMAX : "<<xMAX<<" "<<yMAX<<endl;

	 for(int u=0; u < xMAX; u++) 
   { 
	//cout <<"in first for loop, ";
      for(int v=0; v < yMAX; v++) 
         cout << grid[u][v]<<" "; 
      cout << endl; 
   } 
}

void RoomDisplay::move(char direct, int hero)
{
	int closest = -1;
	for(unsigned int x=0; x < xMonster.size(); x++)
		{
		if(getDistance(hero, x) == 1)
		closest = x;
		}	
	grid[xPlayer[hero]][yPlayer[hero]] = ' ';
	switch(direct){
		case 'w' : if(xPlayer[hero] != 1 && xMonster[closest] != xPlayer[hero]-1)
					xPlayer[hero]--;
					else
						cout <<"Can't move there"<<endl;
			break;
		case 's' : if(xPlayer[hero] != xMAX-2 && xMonster[closest] != xPlayer[hero]+1)
					xPlayer[hero]++;
					else
						cout <<"Can't move there"<<endl;
			break;
		case 'a' : if(yPlayer[hero] != 1 && yMonster[closest] != yPlayer[hero]-1)
					yPlayer[hero]--;
					else
						cout <<"Can't move there"<<endl;
			break;
		case 'd' : if(yPlayer[hero] != yMAX-2 && yMonster[closest] != yPlayer[hero]+1)
					yPlayer[hero]++;
					else
						cout <<"Can't move there"<<endl;
			break;
		case 'q' :
			break;
		default: cout <<"Didn't understand your input; move by 'w', 'a', 's' and 'd' or 'q' to quit";
		}
			char playerChar;
	for(int unsigned x=0; x < xPlayer.size(); x++)
		{
		if(x == 0)
			playerChar = '1';
		if(x == 1)
			playerChar = '2';
		if(x == 2)
			playerChar = '3';
		if(x == 3)
			playerChar = '4';

	grid[xPlayer[x]][yPlayer[x]] = playerChar;
		}

}	
void RoomDisplay::updateRoom(Room current)
{
	aRoom = current;
	// cout <<"Updating room display"<<endl;
	for(int u = 1; u < xMAX-1; u++)
		{
		for(int v = 1; v < yMAX-1; v++)
			{
			grid[u][v] = ' ';
			}
		}
		char playerChar;
	for(int unsigned x=0; x < xPlayer.size(); x++)
		{
		if(x == 0)
			playerChar = '1';
		if(x == 1)
			playerChar = '2';
		if(x == 2)
			playerChar = '3';
		if(x == 3)
			playerChar = '4';

	grid[xPlayer[x]][yPlayer[x]] = playerChar;
		}

	if(aRoom.getHasLoot())
		grid[xMAX/2][yMAX/2] = 'C';

	if(aRoom.getHasEncounter() && !aRoom.enemies.isDefeated())
		{
	//	monsters = aRoom.enemies.getNumberAppear();
	//	string location = aRoom.enemies.getLocation();
	//	setMonsterPosition(location);
	for(int unsigned x=0; x< xMonster.size(); x++)
		grid[xMonster[x]][yMonster[x]] = 'M';
		}
}
void RoomDisplay::setPlayerPosition(string entrance)
{
	//grid[xPlayer][yPlayer] = ' ';
	int xpos, ypos;
	if(entrance == "north")
		{
 	xpos = 1;
	ypos = yMAX/2;
		}
	if(entrance == "south")
		{
	xpos = xMAX-2;
	ypos = yMAX/2;
		}
	if(entrance == "west")
		{
	xpos = xMAX/2;
	ypos = 1;
		}
	if(entrance == "east")
		{
	xpos = xMAX/2;
	ypos = yMAX-2;
		}
	if(entrance == "none")
		{
	xpos = xMAX/2;
	ypos = yMAX/2;
		}
	for(int i=0; i< players; i++)
			{ //cout<<"x and y player position set for player "<< i <<" are "<<xpos<<endl;
			xPlayer.push_back(xpos);
			yPlayer.push_back(ypos);
			}
	grid[xPlayer[0]][yPlayer[0]] = 'P';
}
void RoomDisplay::setMonsterPosition(string entrance)
{
	//grid[xPlayer][yPlayer] = ' ';
	int xpos, ypos;
	if(entrance == "north")
		{
 	xpos = 1;
	ypos = yMAX/2;
		}
	if(entrance == "south")
		{
	xpos = xMAX-2;
	ypos = yMAX/2;
		}
	if(entrance == "west")
		{
	xpos = xMAX/2;
	ypos = 1;
		}
	if(entrance == "east")
		{
	xpos = xMAX/2;
	ypos = yMAX-2;
		}
	if(entrance == "centre" || entrance == "center")
		{
	xpos = xMAX/2;
	ypos = yMAX/2;
		}
	for(int i=0; i< monsters; i++)
			{ //cout<<"x and y player position set for player "<< i <<" are "<<xpos<<endl;
			xMonster.push_back(xpos);
			yMonster.push_back(ypos);
			}
	grid[xMonster[0]][yMonster[0]] = 'M';
	// cout <<"Monster position set!"<<endl;
}		
int RoomDisplay::getDistance(int player, int monster)
{
	int xdif, ydif;
	// cout <<"player x position "<<xPlayer[player]<<endl;
	// cout <<"monster x position "<<xMonster[player] <<endl;
		xdif = xPlayer[player] - xMonster[monster];
		ydif = yPlayer[player] - yMonster[monster];
	
	// cout << "The player and monster separated by "<<xdif<<" on the x-axis and "<<ydif<< "on the y-axis."<<endl;
	
	double result = sqrt( (xdif*xdif) + (ydif*ydif) );
	// cout << "They are "<<result<<" squared apart"<<endl;
	
	return result;
} 
