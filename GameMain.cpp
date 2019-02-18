//Base class for D+D game.  Actor with hero and monster child classes
//	g++ -Wall objectcode.cpp maincode.cpp -o nameofexe
//c++ -o MyProgram MyProgram.cpp
//v5
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include<vector>
//#include "loadfromDBtemplate.cpp"
//#include "Dice.h"
//#include "Actor.h"
#include "Hero.h"
#include "Monster.h"
//#include "GameMap.h"
#include "RoomDisplay.h"
#include "Parser.h"
#include "Party.h"
//#include "Race.h"
//#include "Item.h"
//#include "Weapon.h"
//#include "Armor.h"
#include <unistd.h>

using namespace std;
void createHeros(Hero& champ);
int load(Hero& myHero);
int save(Hero myHero);
int battle(Hero& myHero, Monster& aMonster);
int testLvlUp(Hero& myHero);
//Monster getMonster(int entryNum);

bool processCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom);
bool processFightCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom, int& player);
void goRoom(GameMap& gamerooms, Command command, RoomDisplay thisRoom, int players);
bool fight(Monster& attacker, Hero& defender, int distance);//new

int main()
{
    srand( time(0) );
    const int DELAY = 300000;
//cout<<"Start by creating some test rooms"<<endl;
	GameMap gamerooms;
	Parser parser;

	gamerooms.displayTitle();

	int heroNumber;
	cout <<"How many heros shall we make?"<<endl<<" enter a number: ";
	cin >> heroNumber;
	Hero champ[heroNumber];
	//const char QUIT = 'q';

	for(int i=0; i<heroNumber; i++)
		{
		createHeros(champ[i]);
		}

	cout<<"The "<<heroNumber<<" heros are : ";
	for(int i = 0; i<heroNumber; i++)
		{
		cout<< "#"<<i+1<<"-"<<champ[i].basicInfo()<<" ";
		}
	cout<<endl;


	string heronames[heroNumber];
	for(int i=0; i<heroNumber; i++)
		heronames[i] = champ[i].Actor::getName();

	Party ourParty(heronames, heroNumber);
		//ourParty.displayHeroNames();
	if(heroNumber != 1)
		{
try{
		ourParty.setMarchingOrder();
	}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	}
		}
	cout <<endl;
		//testLvlUp(champ[0]);

	gamerooms.displayIntro();


	cout <<endl<< gamerooms.getCurrentRoom().getLongDescription() <<endl;
	RoomDisplay thisRoom(gamerooms.getCurrentRoom(), heroNumber);
	string entrance = gamerooms.getEntrance();
	
	thisRoom.setPlayerPosition(entrance);

		cout <<"-Perhaps you should make sure you are equipped properly before entering"<<endl;
	bool finished = false;
int rounds = 1;
        while (! finished) 
			{
			if(gamerooms.getCurrentRoom().getHasEncounter() )
				{
				bool killed = gamerooms.getCurrentRoom().enemies.isDefeated();
 				if(!killed)
					{
cout <<"-----Round "<<rounds<<"-----"<<endl;
			cout <<"You are under Attack!!"<<endl;
			cout <<"By "<<gamerooms.getCurrentRoom().enemies.getRemaining();
			cout <<" out of initial total of ";
			cout <<gamerooms.getCurrentRoom().enemies.getNumberAppear() <<" monsters."<<endl;
	//find initiative for party here
				for(int x=0; x< heroNumber; x++)
						{ 
					cout << "What will "<<champ[x].getName()<<" do?"<<endl;
					parser.showFightCommands();
				
					Command myCommand = parser.getFightCommand();
					cout<<endl;
	finished = processFightCommand(ourParty, champ, parser, gamerooms, myCommand, thisRoom, x);
					killed = gamerooms.getCurrentRoom().enemies.isDefeated();

				if(finished || myCommand.getCommandWord() == FLEE || killed == true)
						x=heroNumber;
						
					if(killed)
							{
					int totalExp = gamerooms.getCurrentRoom().enemies.giveExp();
					int exp = totalExp/heroNumber;
						for(int i=0; i< heroNumber; i++)
								{ 
							champ[i].setExp(exp);
								}
rounds = 1;
						//cin.ignore(100, '\n');
							}	//if(killed)...
						}	//for hero loop

		//cycle thru the monsters here
				int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
						if(!finished  && !killed)
						{	
						for(int monster=0; monster< numberOfEnemies; monster++)
							{
							Monster aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monster);  	
							bool alive = aMonster.aliveOrDead();
							thisRoom.moveMonster(monster); //, x);	//monster moves number of steps
							cout << thisRoom.getTarget(monster)<<endl;		
							//find closest hero
							int nextto = thisRoom.heroTarget(monster);
							//attack that hero
							usleep(DELAY);
							bool success;
							if(nextto != -1 && alive)	
								{
								success = fight(aMonster, champ[nextto], 1);
								if(!success)
									cout <<"Error in monster fighting hero."<<endl;
								}
							}	//for monsters
						thisRoom.createRoom();
							rounds++;
						}	//if(!finished  && !killed)  cycle thru monsters
					}	//if(!killed)
				else 
					cout <<"Enemies defeated!!"<<endl;
				}
			else
				{
			
			parser.showNormalCommands();
            Command myCommand = parser.getCommand();
			cout<<endl;
	 finished = processCommand(ourParty, champ, parser, gamerooms, myCommand, thisRoom);
				}
          
     	   }
        cout<<"Thank you for playing.  Good bye."<<endl;

 /*
cout<<"Load a monster based on Lvl"<<endl;
int lvl = champ.getLevel();
int entry=0;
if(lvl == 1)
	{
	Dice dice(1,4);
	entry = dice.getValue();
	cout <<"Entry number = "<<entry<<endl;
	}
Monster monster = getMonster(entry);

cout <<endl<<"Try a battle"<<endl;

battle(champ, monster);
cout <<"battle over"<<endl;  */

/*
cout <<"Do another battle? y or q to quit ";
cin >>cmd;
 while(cmd != QUIT)
	{
	Dice dice1d4(1,4);     
	int value = dice1d4.getValue(); 
	cout<<"Make a Monster with 1d4: "<<value<<endl;
 	cout<<"Enter monster name: "<<endl;
	cin>>name;
   Monster monster(name, value);
	int temp = monster.Actor::getHP() + (monster.getLvl()/2)*dice1d4.getValue();
	monster.setHP(temp);

	battle(champ, monster);
	cout <<"battle over"<<endl;
	cout <<"Do another battle? y or q to quit ";
	cin >>cmd;
	}

*/

   return 0;
}
/*
int testLvlUp(Hero& myHero)
{
  char quitChar = 'n';
	char QUIT = 'y';
cout <<"Testing levelUp functions"<<endl;
cout<<"quit? y or n: (Enter "<<QUIT<<" to quit)";
cin >> quitChar;

 	while(quitChar != QUIT)
	{
cout <<"Test level up"<<endl;
myHero.setExp(500);
cout<<"quit? y or n: (Enter "<<QUIT<<" to quit)";
cin >> quitChar;
	}
	return 0;
} */
