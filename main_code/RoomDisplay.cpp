//v5
#include<iostream>
//#include<fstream>
#include<string>
#include<vector>
//#include<map>
#include <math.h>
#include "RoomDisplay.h"
#include "Dice.h"
#include <unistd.h>
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

	if(aRoom.getHasEncounter()) // && !aRoom.enemies.isDefeated())
		{
	//	monsters = aRoom.enemies.getNumberAppear();
	//	string location = aRoom.enemies.getLocation();
	//	setMonsterPosition(location);
	for(int unsigned x=0; x< xMonster.size(); x++)
			{
			bool alive = aRoom.enemies.getMonster(x).aliveOrDead();
			if(alive)
			grid[xMonster[x]][yMonster[x]] = 'M';
			if(!alive)
			grid[xMonster[x]][yMonster[x]] = 'c';
			}
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
double RoomDisplay::getDistance(int player, int monster)
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
double RoomDisplay::getPlayerDistance(int player1, int player2)
{
    int xdif, ydif;
	// cout <<"player x position "<<xPlayer[player]<<endl;
	// cout <<"monster x position "<<xMonster[player] <<endl;
		xdif = xPlayer[player1] - xPlayer[player2];
		ydif = yPlayer[player1] - yPlayer[player2];
	
	// cout << "The player and monster separated by "<<xdif<<" on the x-axis and "<<ydif<< "on the y-axis."<<endl;
	
	double result = sqrt( (xdif*xdif) + (ydif*ydif) );
	// cout << "They are "<<result<<" squared apart"<<endl;
	
	return result;
}
double RoomDisplay::getMonsterDistance(int monster1, int monster2)
{
	    int xdif, ydif;
	// cout <<"player x position "<<xPlayer[player]<<endl;
	// cout <<"monster x position "<<xMonster[player] <<endl;
		xdif = xMonster[monster1] - xMonster[monster2];
		ydif = yMonster[monster1] - yMonster[monster2];
	
	// cout << "The player and monster separated by "<<xdif<<" on the x-axis and "<<ydif<< "on the y-axis."<<endl;
	
	double result = sqrt( (xdif*xdif) + (ydif*ydif) );
	// cout << "They are "<<result<<" squared apart"<<endl;
	
	return result;
}
void RoomDisplay::moveMonster(int monster) //, int seed)
{
	//move the monster of vector[monster] towards closest hero with a small chance of random movement.
	//What happens to a monster or hero in the vector when it is dead??
	bool alive = aRoom.enemies.getMonster(monster).aliveOrDead();
		int STEPS = aRoom.enemies.getMonster(monster).getSpeed();
		unsigned int scared = aRoom.enemies.getMonster(monster).condition.getCondition();
		int direction = 1;	//1 is normal, -1 is scared and flip direction move
		if(scared == 8)
			direction = -1;
	usleep(30000);
	if(alive)
	{
	//	cout <<"Monster is going to move"<<endl;
		for(int x=0; x<STEPS; x++)	
		{
	int closest = -1;
	double distance = 100;
	double newclosest;
		for(unsigned int x=0; x < xPlayer.size(); x++)
			{
	//	cout <<"Check " << x <<"th player proximity"<<endl;
		newclosest = getDistance(x, monster);
			if(newclosest < distance)
				{
			distance = newclosest;
			closest = x;
				}
			}	

	Dice randomMove(1,100);
		//	cout <<"Player number "<< closest <<" is the closest at a distance of "<<distance<<endl;
		//	cout <<"Theres a total of "<<players <<" characters and "<<monsters <<" monsters"<<endl;
		if(distance !=1)
			{
		int xdif = (xPlayer[closest] - xMonster[monster])*direction;	//direction either 1 or -1
		int ydif = (yPlayer[closest] - yMonster[monster])*direction;
		grid[xMonster[monster]][yMonster[monster]] = ' ';

	int diceRoll = randomMove.getValue();
	//	cout <<"dice roll of "<< diceRoll<<endl;
			if(diceRoll <= RANDOMMOVE )		//move randomly if roll is >85
				{
				if(xdif != 0)
					{
			//	cout <<"the xdif is not 0 so will move in this direction first"<<endl;
					if(xdif > 0 && xMonster[monster] != xMAX-2 )
						{
					xMonster[monster]++;
				//	cout <<"xMonster ++ updated"<<endl;
						}
					else if(xdif < 0 && xMonster[monster] != 1)
						{
					xMonster[monster]--;
				//	cout <<"xMonster -- updated"<<endl;
						}
					else
					cout <<"Error, monster can't move in xdirection"<<endl;
					}
				else if(ydif != 0)
					{
		//	cout <<"the ydif is not 0 so will move in this direction first"<<endl;
					if(ydif > 0 && yMonster[monster] != yMAX-2 )
						{
					yMonster[monster]++;
				//	cout <<"yMonster ++ updated"<<endl;
						}
					else if(ydif < 0 && yMonster[monster] != 1)
						{
					yMonster[monster]--;
				//	cout <<"yMonster -- updated"<<endl;
						}
					else
					cout <<"Error, monster can't move in ydirection"<<endl;
					}	
			else
				cout <<"Something wrong with monster movement"<<endl;
				}
		else if(diceRoll > RANDOMMOVE )
				{
//			srand( time(0) + seed);
		usleep(30000);
		Dice randomPlace(1,4);
		int diceRoll2 = randomPlace.getValue();
		//	cout <<"   diceRoll2 : "<<diceRoll2<<endl;
			if(diceRoll2 == 1 && xMonster[monster] != xMAX-2)
				xMonster[monster]++;
			else if(diceRoll2 == 2 && xMonster[monster] != 1)
				xMonster[monster]--;
			else if(diceRoll2 == 3 && yMonster[monster] != yMAX-2)
				yMonster[monster]++;
			else if(diceRoll2== 4 && yMonster[monster] != 1)
				yMonster[monster]--;
			else
				cout <<"Something wrong with random movement. Roll was: "<<diceRoll2<<endl;
				}		//else if(diceRoll >...
			}				//if(distance !=1)...
//	else if (distance == 1)
	//	cout <<"The monster is next to the closest hero and will not move."<<endl;


		}	//Steps
	}	//if(alive)
	else if(!alive)
	{
		grid[xMonster[monster]][yMonster[monster]] = 'c';
		cout <<"That monster # "<<monster<<" is dead."<<endl;
	}
	else
		cout <<"Roomdisplay can't determine if monster is alive or not"<<endl;
		//	cout<<"update grid with monster position"<<endl;		
	for(int unsigned x=0; x< xMonster.size(); x++)
		{
		bool alive = aRoom.enemies.getMonster(x).aliveOrDead();
		if(alive)
			grid[xMonster[x]][yMonster[x]] = 'M';
		else if(!alive)
			grid[xMonster[x]][yMonster[x]] = 'c';
		else
			cout <<"in move, can't determine alive or dead status"<<endl;
		}
}
string RoomDisplay::getTarget(int monster)
{
	bool alive = aRoom.enemies.getMonster(monster).aliveOrDead();
	string status =aRoom.enemies.getMonster(monster).condition.getStatus();
	string aliveordead;
	if(alive)
		aliveordead = "alive";
	else
		aliveordead = "dead";

	string output;
	output = "Monster #" + to_string(monster) + " is " + aliveordead +" " + status +" at (" + to_string(xMonster[monster]) + ", " + to_string(yMonster[monster]) + ")";
	return output;
}
void RoomDisplay::getTarget()
{
	string output;
	for(unsigned int monster=0; monster<xMonster.size(); monster++)
	{
	bool alive = aRoom.enemies.getMonster(monster).aliveOrDead();
	if(alive)
		cout<<getTarget(monster)<<endl;
	//output = output + getTarget(monster) + "\n";
	}
	//cout<<output;
}
int RoomDisplay::heroTarget(int monster)
{	//looks for a hero in an adjacent position for melee attack
	int nextto = -1;
	for(int hero=0; hero< players; hero++)
		{ 	
	double distance = getDistance(hero, monster);
		if(distance == 1)
			nextto = hero;
		}
			//returns the player index number or -1 if not adjacent
	return nextto;
}
