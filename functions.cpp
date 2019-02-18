#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
//v5
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
//#include "GameMap.h"
#include<vector>
#include "Parser.h"
//#include "Actor.h"
#include "Hero.h"
#include "RoomDisplay.h"
#include "Party.h"
#include "Dice.h"
//#include "loadfromDBtemplate.cpp"
using namespace std;

string ARMOR_FILE = "Armor.txt";
string WEAPON_FILE = "Weapon.txt";
string THROWN_FILE = "Thrown.txt";
string POTION_FILE = "Potion.txt";
string AMMO_FILE = "Ammo.txt";
string ITEM_FILE = "Item.txt";

/*
bool processCommand(Hero& champ, Parser& parser, GameMap& gamerooms, Command command); */
bool processFightCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom, int player);
void goRoom(GameMap& gamerooms, Command command, RoomDisplay& thisRoom, int players);
bool throwAt(Hero& attacker, Monster& defender, int distance, Thrown athrown);
bool fight(Hero& attacker, Monster& defender, int distance);
bool fight(Monster& attacker, Hero& defender, int distance);
void equip(Hero& champ);
int extractIDs(vector<int>& ids, string input);
void fillInventory(Hero& champ);  //in loadfromDBtemplate file
void equip(Hero& champ);
//includes getweapondfromDB and getarmorfromDB for loading hero, use template?

bool processCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom)
{
	int numberofHeros = party.getMemberNumber();
	int heroNumber;
	bool wantToQuit = false;
	switch(myCommand.getCommandWord()) {
	case GO: 
		{
		cout<< " You will go "<<myCommand.getSecondWord()<<endl;
		goRoom(gamerooms, myCommand, thisRoom, numberofHeros);
		}
	break;
	case LOOK: 
		{	
	//	RoomDisplay thisRoom(gamerooms.getCurrentRoom());
	//	string entrance = gamerooms.getEntrance();
	//	cout <<"entrance is "<<entrance<<endl;
	//	thisRoom.setPlayerPosition(entrance);
		thisRoom.createRoom();	
		 gamerooms.displayEntrance();
		cout<<"You look around and see: "<<endl;
		gamerooms.getCurrentRoom().display();
	//if has loot, open container and look. later make this a separate operation
		if(gamerooms.getCurrentRoom().getHasLoot())
			{
			for(unsigned int i=0; i<gamerooms.getCurrentRoom().chest.size(); i++)
				gamerooms.getCurrentRoom().chest[i].open();
		
			}
		
		//delete thisRoom;
		}
	break;
	case HELP: cout <<endl;
		{	
		parser.showCommands();
		cout <<"Type one of these command words followed by a second word iF necessary. Such as 'go north', or 'look'."<<endl;
		}		
	break;
	case CHAR : 
		{	
			string name;		
			cout <<"Show character info "<<endl;
		if(!myCommand.hasSecondWord())
			{
	heroNumber = party.whichPartyMember();
	name = party.getHero(heroNumber);
			}
		else
		name = myCommand.getSecondWord();
	//string name = party.getHero(heroNumber);
	//cout <<"checking Hero name: "<<name<<endl;
	bool found = false;
	for(int i=0; i<numberofHeros; i++)
		{
		//cout<<"i = "<<i<<", name is "<<champ[i].Actor::getName();
		if(name == champ[i].getName())
			{
			found = true;
			champ[i].outputData();	
			}
		}
		if(!found)
			cout<<"second word did not match character name"<<endl;
		
		}
	break;
	case EQUIP : 
		{
		string name;
		cout <<"Equip character "<<endl;
		if(!myCommand.hasSecondWord())
			{
	heroNumber = party.whichPartyMember();
	name = party.getHero(heroNumber);
			}
		else
			name = myCommand.getSecondWord();
	bool found = false;
	for(int i=0; i<numberofHeros; i++)
		{
		if(name == champ[i].Actor::getName())
			{
			cout << name <<endl;
			found = true;
			equip(champ[i]);
			}
		}
		if(!found)
			cout<<"second word did not match character name"<<endl;

		cin.ignore(100, '\n');
		}
	break;
	case UNEQUIP :
		{
			string name;	
		cout <<"Unequip Character "<<endl;
		if(!myCommand.hasSecondWord())
			{
		heroNumber = party.whichPartyMember();
		name = party.getHero(heroNumber);
			}
		else
		name = myCommand.getSecondWord();
	bool found = false;
	for(int i=0; i<numberofHeros; i++)
		{
		if(name == champ[i].Actor::getName())
			{
			cout << name <<endl;
			found = true;
			champ[i].inventory.unEquip();
			}
		}
		if(!found)
			cout<<"second word did not match character name"<<endl;

			cin.ignore(100, '\n');
		}
	break;
	case QUIT : 
		{
		cout<<"You want to quit"<<endl;
		wantToQuit = true;  //Want to add a quit function??
		}
	break;
	case UNKNOWN : 
		{
		cout <<" That command was unknown.  Your choices are:"<<endl;
		parser.showCommands();
		}
	break;
	case MARCH :
			{
			party.setMarchingOrder();
			cin.ignore(100, '\n');
			}
	break;
	case TAKE :  //for now no second word, later money or item etc
			{
			Room currentRoom = gamerooms.getCurrentRoom();
			string secWord = myCommand.getSecondWord();
		if(currentRoom.getHasLoot())
				{
	unsigned int choice;
	if(currentRoom.chest.size()>1)
		{

			cout<< " You will take "<< secWord <<"from the ";
	cout <<"which container?"<<endl;
		for(unsigned int i=0; i<currentRoom.chest.size(); i++)
			{
			cout <<"#"<<i<< " ";
			currentRoom.chest[i].showType();
			}
		cout <<"Enter desired #: ";

		cin>>choice;	
		}
	else if(currentRoom.chest.size() == 1)
			choice = 0;
		
	if(choice <= 0 || choice < currentRoom.chest.size())
		{		

			heroNumber = party.whichPartyMember();
			string name = party.getHero(heroNumber);

			for(int i=0; i<numberofHeros; i++)
					{
				if(name == champ[i].getName())
						{
				string money = "m ";
				currentRoom.chest[choice].open();
					if(secWord == "all")
							{
				money+= currentRoom.chest[choice].takeAllMoney();
				cout <<"money string: "<<money<<endl;
				vector<int>coins;
				extractIDs(coins, money);
				champ[i].inventory.receiveMoney(coins[0], coins[1], coins[2]);
							}
					if(secWord == "coins" || secWord == "money")
							{
				money+= currentRoom.chest[choice].takeMoney();
				cout <<"money string: "<<money<<endl;
				vector<int>coins;
				extractIDs(coins, money);
				//for(unsigned int i=0; i<coins.size(); i++)
				//	cout<<"i = "<<i<<" coins is = "<<coins[i]<<endl;
				champ[i].inventory.receiveMoney(coins[0], coins[1], coins[2]);
							}
					if(secWord == "item")	
							{
			cout <<" *** So far only removed items or potions, anything else hasn't been implemented yet *** "<<endl;
						if(currentRoom.chest[choice].bag.items.size()>0)
						{
				Item thing = currentRoom.chest[choice].takeItem();
				cout <<"Remove 1st item in container: "<< thing.getName() <<endl;
				champ[i].inventory.addItem(thing);
						}
						else if(currentRoom.chest[choice].bag.potions.size()>0)
						{
				Potion thing = currentRoom.chest[choice].takePotion();
				cout <<"Remove 1st potion in container: "<< thing.getName() <<endl;
				champ[i].inventory.addPotion(thing);
						}
				champ[i].inventory.showList();
							}
			//currentRoom.chest.open();
			gamerooms.updateRoom(currentRoom);
						}
		//			else 
		//		cout<<"Can't find hero"<<endl;
				
					}	//for hero
		}
	else
		cout <<"Your choice of containers doesn't exist"<<endl;
				}//if has loot
			else
				cout <<"Take what? Nothing here."<<endl;
		cin.ignore(100, '\n');
			}
	break;	
	case PARTY :
			{
			parser.showPartyCommands();
			}
	break;			
	case ITEM :
			{
			cout <<"not implemented yet"<<endl;
			}
	break;	
	
	default: 
		{		
		cout<<"something wrong with switch "<<endl;
		cout <<"These are the choices: "<<endl;
		parser.showCommands();
		}
			}
	return wantToQuit;
}

/*
Similar function to above but specfically to during an encounter
Only some normal commands are valid and new special fight commands become valid
*/

bool processFightCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom, int& player)
{
	int numberofHeros = party.getMemberNumber();
	//string name = party.getHero(player);
//	int heroNumber;
	bool wantToQuit = false;
	switch(myCommand.getCommandWord()) {
	case QUIT : 
		{
		cout<<"You want to quit"<<endl;
		wantToQuit = true;  //Want to add a quit function??
		}
	break;
	case UNKNOWN : 
		{
		cout <<" That command was unknown.  Because you are in battle, your choices are:"<<endl;
		parser.showFightCommands();
		cout <<"Try again"<<endl;
		player--;
		}
	break;
		case ATTACK :
			{
			//cout <<"not implemented yet"<<endl;
		Room currentRoom = gamerooms.getCurrentRoom();
		int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
		Monster aMonster = currentRoom.enemies.getMonster(0);  //choose monster
			int monsterNumber = 0;
		while(!aMonster.aliveOrDead() && monsterNumber < numberOfEnemies)  //dead
		{
	//	cout <<"Monster # "<<monsterNumber <<" is dead, ";
		monsterNumber ++;
	//	cout <<"using monster # "<<monsterNumber<<endl;
		aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monsterNumber);
		}
	
			int dis = thisRoom.getDistance(player,monsterNumber);
		bool success = fight(champ[player], aMonster, dis);

		if(success)
			{
			//	cout <<"Monster is alive "<< aMonster.aliveOrDead()<<endl;
		currentRoom.enemies.updateMonster(aMonster, monsterNumber);
	/*bool badguys = */	currentRoom.getHasEncounter();
		//	cout<<"In function attack, getHasEncounter: "<<badguys<<", then update room"<<endl;
		gamerooms.updateRoom(currentRoom);
		thisRoom.updateRoom(currentRoom);
			}
		else 
			player--;

		// cin.ignore(100, '\n');
			}
	break;		
		case MOVE :
			{		
		int STEPS = champ[player].getCurrentSpeed();
		int dis;
			thisRoom.createRoom();	
		dis = thisRoom.getDistance(player,0);
		cout <<"Distance is: "<< dis <<endl;
			cout <<"enter direction: w,a,s,or d "<<endl <<"Make 5 moves ";
		for(int x=0; x<STEPS; x++)
				{
		char dir;
		cin >>dir;
		thisRoom.move(dir, player);
		//thisRoom.updateRoom();
		thisRoom.createRoom();
	 dis = thisRoom.getDistance(player,0);
		cout <<"Distance is: "<< dis <<endl;
				}
		cin.ignore(100, '\n');
			}
	break;	
		case FLEE :
			{
			cout <<"you run back the way you came!"<<endl;
			string entrance = gamerooms.getEntrance();
			Room currentRoom = gamerooms.getCurrentRoom();
			if(currentRoom.isExit(entrance))
				{
        Room nextRoom = gamerooms.getCurrentRoom().getExit(entrance);
		gamerooms.setEntrance(entrance);
         gamerooms.setCurrentRoom(nextRoom);
		currentRoom = gamerooms.getCurrentRoom();
      //    gamerooms.displayEntrance();
		currentRoom.display();
		string entrance = gamerooms.getEntrance();
			RoomDisplay newRoom(gamerooms.getCurrentRoom(), numberofHeros);
			thisRoom = newRoom;
			thisRoom.setPlayerPosition(entrance);
	
    	 		 }
		else
				{
		cout<<"Can't go that way, try again. Something wrong with FLEE"<<endl;
		player--;			
				}
		}
	break;	
		case ITEM :
			{
			//cout <<"not implemented yet"<<endl;
		cout<<"Throw or drink something? 't' or 'd': ";
		char choice;
		cin>> choice;
			bool found = false;	
			if(choice == 'd')
				{	
				int id;
				Potion apotion;
				cout <<" Which potion ID do you want to drink?" <<endl;
				cout << "Choices are : "<< champ[player].inventory.getPotionIDs();
 					cin>> id;
			for(int i=0; i<champ[player].inventory.getPotionNum(); i++)
					{
				if(id == champ[player].inventory.getPotionID(i))
						{
					found = true;
					champ[player].inventory.potions[i].display();
				int healDie =  champ[player].inventory.potions[i].getHealDie();
				int healmult = champ[player].inventory.potions[i].getHealMult(); 
				Dice dice(healmult, healDie);
				int healpts = dice.getValue();
				champ[player].receiveHealing(healpts);
			champ[player].inventory.potions[i].removePotion();
				cout <<"You drink the potion and heal yourself for "<<healpts<<"."<<endl;
						}
					}
				player--;
				}
			else if(choice == 't')
		{
				int id;
				//bool found = false;	
				Thrown athrown;
				cout <<" Which projectile ID do you want to throw?" <<endl;
				cout << "Choices are : "<< champ[player].inventory.getThrownIDs();
 					cin>> id;
			for(int i=0; i<champ[player].inventory.getThrownNum(); i++)
			{
				if(id == champ[player].inventory.getThrownID(i))
				{
					found = true;
					athrown = champ[player].inventory.dropThrown(i);
				
					Room currentRoom = gamerooms.getCurrentRoom();
					int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
					Monster aMonster = currentRoom.enemies.getMonster(0);  //choose monster
					int monsterNumber = 0;
					while(!aMonster.aliveOrDead() && monsterNumber < numberOfEnemies)  //dead
						{
					monsterNumber ++;
				//	cout <<"using monster # "<<monsterNumber<<endl;
					aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monsterNumber);
						}
	
					int dis = thisRoom.getDistance(player,monsterNumber);
					bool success = throwAt(champ[player], aMonster, dis, athrown);

					if(!success)
						champ[player].inventory.addThrown(athrown);
					if(success)   //in case out of range
						{
				//	cout <<"Monster is alive "<< aMonster.aliveOrDead()<<endl;
				currentRoom.enemies.updateMonster(aMonster, monsterNumber);
					for(int y=0; y<numberOfEnemies; y++)
							{
						if(y != monsterNumber)	
								{	//check that they are all close to target
						aMonster = gamerooms.getCurrentRoom().enemies.getMonster(y);
						aMonster.receiveDamage(1);
						currentRoom.enemies.updateMonster(aMonster, y);
								}
							}
				/*bool badguys = */	currentRoom.getHasEncounter();
			//	cout<<"In function attack, getHasEncounter: "<<badguys<<", then update room"<<endl;
				gamerooms.updateRoom(currentRoom);
				thisRoom.updateRoom(currentRoom);
						}	
				}	
			cin.ignore(100, '\n');		
			}
		if(!found)
			{
			cout<<" Error! entered ID was not found or did not match choices available.  Try again"<<endl;
			player--;
			}

		}
			else
				{
				cout<<" Didnt understand. try again."<<endl;
				player--;
				}
			}
	break;	
	case EQUIP : 
		{
		cout <<"Equip character "<<endl;
		//	cout <<"Confirm character: "<< champ[player].Actor::getName()<<endl;
			equip(champ[player]);
		player--;
		cin.ignore(100, '\n');
		}
	break;
	case UNEQUIP :
		{
		cout <<"Unequip Character "<<endl;

			champ[player].inventory.unEquip();
		player--;
			cin.ignore(100, '\n');
		}
	break;	
	default: 
		{		
		cout<<"something wrong with switch "<<endl;
		cout <<"These are the choices: "<<endl;
		parser.showCommands();
		cout <<"  Try again "<<endl;
		player--;
		}
			}
	return wantToQuit;
}
	
/*
function to control fight.
*/
bool throwAt(Hero& attacker, Monster& defender, int distance, Thrown athrown)
{  //throwAt(champ[player], aMonster, dis, athrown);
	bool success = false;
	int hitRoll, range;
	range = athrown.getRange();
		cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
	if(distance < (5*range))
			{
		cout <<"Range throw attack"<< endl;	
		cout<<"Weapon range is "<<range<<" and enemy is "<<distance<<" away."<<endl;
		//determine range penelty -2 to attack for every range increment
		hitRoll = attacker.meleeRoll();	
		int rangeIncrem = distance / range;
		//	cout <<"RangeIncrem is "<<rangeIncrem<<endl;
			if(rangeIncrem >= 1)
				{
			int penalty = 2*rangeIncrem;
			cout <<" -"<<penalty<< " range penalty "<<endl;
		hitRoll = hitRoll - penalty;
		//	cout <<"New hit is: "<<hitRoll<<endl;
				}
		success = true;
			}
			else
			cout <<"You are out of range. Maximum distance of throw is "<<5*range<<" but the monster is "<<distance<<"away. Try something else"<<endl;
	if(success)	
	{
	int MonsterAC = defender.getAC(); //

		cout << "hitRoll "<< hitRoll << " vs monster AC " <<MonsterAC<<endl;
	if(hitRoll >= MonsterAC)
		{		
		cout <<" You hit the monster "<< defender.getName() <<"! "<<endl;
		int dmg = athrown.getDmg();
		Dice dice(1,dmg);
		int dmgRoll = dice.getValue() + attacker.getMod(STR);
		cout <<" Damage for "<<dmgRoll<<endl;
		defender.receiveDamage(dmgRoll);
		}
	else
		{
		cout <<" Missed, but lands close by and splashes the target."<<endl;
		defender.receiveDamage(1);	
		}
	}

	return success;
}
bool fight(Hero& attacker, Monster& defender, int distance)
{
	bool success = false;
	int hitRoll;
	bool ranged = attacker.inventory.myEquip.hasRange();
//	cout <<"Ranged is "<<ranged<<endl;
	cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
		if(distance == 1) //also need to check for equipped weapon
		{
			if(!ranged)
			{
		cout <<"Melee attack"<<endl;
		hitRoll = attacker.meleeRoll();
		success = true;
			}
			else
			cout <<"You are too close, change to melee weapon."<<endl;
		}
		else 
		{
			if(ranged)
			{
		if(attacker.inventory.getAmmoNum() && attacker.inventory.ammo[0].getName() == "Arrows")
		{
		cout <<"Range attack"<< endl;	
	int weapPos = attacker.inventory.myEquip.getHandPosition();
		int range = attacker.inventory.weapons[weapPos].getRange();
	cout<<"Weapon range is "<<range<<" and enemy is "<<distance<<" away."<<endl;
		//determine range penelty -2 to attack for every range increment
		hitRoll = attacker.rangeRoll();	
		
	int rangeIncrem = distance / range;
	//	cout <<"RangeIncrem is "<<rangeIncrem<<endl;
		if(rangeIncrem >= 1)
			{
			int penalty = 2*rangeIncrem;
			cout <<" -"<<penalty<< " range penalty "<<endl;
		hitRoll = hitRoll - penalty;
		//	cout <<"New hit is: "<<hitRoll<<endl;
			}
		success = true;
		attacker.inventory.dropAmmo(0);
			}
			else
			cout <<"You have no ammo to shoot!"<<endl;
		}
			else
			cout <<"you are out of range. Try a different"<<endl;
		}
	if(success)	
	{
	int MonsterAC = defender.getAC(); //

		cout << "hitRoll "<< hitRoll << " vs monster AC " <<MonsterAC<<endl;
	if(hitRoll >= MonsterAC)
		{
		int dmg;		
		cout <<" You hit the monster "<< defender.getName() <<"! "<<endl;
		dmg = attacker.getDmgRoll();
		cout <<" Damage for "<<dmg<<endl;
		defender.receiveDamage(dmg);
		}
	else
		cout <<" Missed "<<endl;
	}
	return success;
}

bool fight(Monster& attacker, Hero& defender, int distance)
{
		bool success = false;
	int hitRoll;
	cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
		if(distance == 1) //also need to check for equipped weapon
		{
		cout <<"Melee attack"<<endl;
		hitRoll = attacker.meleeRoll();
				success = true;
		}
		else
		{
		cout <<"Range attack"<< endl;
		// hitRoll = attacker.rangeRoll();
			cout <<"Monster range attack not set up yet"<<endl;
		}

	if(success)	
	{		
	int MonsterAC = defender.getAC(); //

		cout << "Monster hitRoll "<< hitRoll << " vs your AC " <<MonsterAC<<endl;
	if(hitRoll >= MonsterAC)
		{
		int dmg;		
		cout <<" the monster hits "<< defender.getName() <<"! "<<endl;
		dmg = attacker.getDmgRoll();
		cout <<" Damage for "<<dmg<<endl;
		defender.receiveDamage(dmg);
		}
	else
		cout <<" Missed "<<endl;
	}
	return success;
}
/*
Function used in the normal processCommand GO
used to move the party to the desired room
*/

void goRoom(GameMap& gamerooms, Command command, RoomDisplay& thisRoom, int players) 
    {
        if(!command.hasSecondWord()) {
            // if there is no second word, we don't know where to go...
            cout <<"Go where?"<<endl;
            return;
        }
	Room currentRoom = gamerooms.getCurrentRoom();
        string direction = command.getSecondWord();
	//	cout<<"You leave: "<<currentRoom.getShortDescription()<<endl;
        // Try to leave current room.
		if(currentRoom.isExit(direction))
	{
        Room nextRoom = gamerooms.getCurrentRoom().getExit(direction);
		gamerooms.setEntrance(direction);
	//cout<<"You enter the: ";
	//cout<<nextRoom.getShortDescription()<<endl;

         gamerooms.setCurrentRoom(nextRoom);
		currentRoom = gamerooms.getCurrentRoom();
      //    gamerooms.displayEntrance();
		currentRoom.display();
		string entrance = gamerooms.getEntrance();
	//	cout <<"entrance is "<<entrance<<endl;
			RoomDisplay newRoom(gamerooms.getCurrentRoom(), players);
			thisRoom = newRoom;
			thisRoom.setPlayerPosition(entrance);
	
      }
		else
		{
		cout<<"Can't go that way, try again."<<endl;
		cout <<"Choose: "<< gamerooms.getCurrentRoom().getExitString()<<endl;
		}
    }

/*
function used during load to extract ID numbers from file
*/
int extractIDs(vector<int>& ids, string input)
{
	string wOrA;
	char space = ' ';
	// char separator = ':';
	istringstream iss(input);
	string temp;
	int tempID;

	getline(iss, wOrA, space);
	//string::size_type position = input.find (' ');
	while(!iss.eof()) //position!=string::npos)
		{
		//string tempID;	
		//getline(iss, tempID, separator);
		iss >> temp;
		if(stringstream(temp) >> tempID )
		ids.push_back(tempID);
		temp = "";
		}
	cout << "Extracted ->: "<<wOrA <<" ";
		for(unsigned int count = 0; count < ids.size(); ++count)
		{
		cout << ids[count] <<" ";
		}
		cout << endl;

	return 0;
}

int load(Hero& myHero)  
{
  	
char fileName[10];

cout <<endl<< "Enter a filename or path and filename (such Hero.txt)"<<endl<<": ";
cin >> fileName;
		ifstream inFile;
   inFile.open(fileName);
   if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
	}   
	else 
	{
	cout << "  ...Loading data"<< endl;
	inFile >> myHero;
	cout <<endl << "Data loaded" <<endl;
	}
	inFile.close();
//myHero.outputData();
	
return 0;
}


//For saving Hero data
int save(Hero myHero)
{
	cout << "Save Hero data: "<<endl;
	myHero.outputData();
	char filename[10];
	cout << "Enter filename: ";
	cin >> filename;

	ofstream outFile;
	outFile.open(filename);
  		 if(!outFile.good())
     		 cout << "File could not be opened" << endl;
  	 	else
   			{
		outFile << myHero;
		cout << "Saved"<< endl;
			}
	return 0;
}

void createHeros(Hero& champ)
{
	string name;
	char cmd;
	cout <<"Do you want to create a new Hero or load your saved hero?, 'n' or 'l':";
	cin >>cmd;
	if(cmd == 'n')
		{
		cout<<"Make a Hero!"<<endl;
 		cout<<"Enter Character name: "<<endl;
		cin>>name;
  		 //Hero champ(name);
		champ.setName(name);
		champ.setFields();
   
   		cout <<endl<< "A hero: ";
   		champ.outputData();
  		 cout << endl; 

		fillInventory(champ);

		cout <<" keep and save? y or n? ";
		char keep;
		cin >> keep;
			if(keep == 'y')
			{
			cout<<"save function here"<<endl;
			save(champ);
			}
		} 
		else if(cmd == 'l')
			{
			cout<<"load function here"<<endl;
			load(champ);
			champ.outputShortData();	
			}
		else
			 cout<<"Invalid cmd"<<endl;
		

}



void equip(Hero& champ)
{
	//cout <<"Start equip function"<<endl;
	char wOrA = 't';
		int id;
		const char QUIT = 'q';	
//	cout <<"about to enter while "<<endl;
while(wOrA != 'q'){
	//champ.outputShortData();
	//champ.inventory.showList();
	cout <<"Do you want to equip weapon 'w' or armor 'a' or '"<<QUIT<<"' to quit? "; 
	cin >> wOrA;
		switch (wOrA) {
 			case 'a' : 
				{				
				cout <<" Which armor ID do you want to equip?" <<endl;
				cout << "Choices are : "<< champ.inventory.getArmorIDs();
 					cin>> id;
				for(int i=0; i<champ.inventory.getArmorNum(); i++)
					{
					if(id == champ.inventory.getArmorID(i))
						{
				//champ.inventory.armor[i].wield();
				champ.inventory.equipArmor(i);
				cout << "New AC is "<<champ.getAC()<<endl;
				//cout << "Equipped " << champ.inventory.armor[i].Item::getName() <<endl;
						}
	
					else
				cout << "Can't equip that! Something went wrong "<<endl;
					} //for
		
				}
		break;
		case 'w' : 
			{
			cout <<" Which weapon ID do you want to equip?" <<endl;
			cout << "Choices are : "<<champ.inventory.getWeaponIDs();
 					cin>> id;
			for(int i=0; i<champ.inventory.getWeapNum(); i++)
			{
			if(id == champ.inventory.getWeaponID(i))
				{
			//champ.inventory.weapons[i].wield();
			champ.inventory.equipWeapon(i);
			//cout << "Equipped " << champ.inventory.weapons[i].Item::getName() <<endl;
				}
			//else
				//cout << "Can't equip that! Something went wrong "<<endl;
			} //for
		cout << "New damage is "<<champ.getDmgDie()<<endl;
		}
		break;
		case 'q' :
			{
				cout <<"Finished equipping hero"<<endl;
			}
		break;
		default: cout <<"Error"<<endl;
				wOrA = QUIT;
		} //switch
	}//while
}	

//weapon and armor from database.  template may work better...
int getWeaponFromDB(Weapon& weapon, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading a Weapon from the Database"<<endl;

int success=0;
ifstream inFile;
//const int QUIT = 0;

int filelines=0;

inFile.open(WEAPON_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>weapon && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(WEAPON_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		//cmd = QUIT;
		success = 0;
	}   
	else 
	{

	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>weapon && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
weapon.display();


			}  //else
inFile.close();

	return success;
}

int getArmorFromDB(Armor& armor, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading Armor from the Database"<<endl;


int success=0;
ifstream inFile;
int filelines=0;

inFile.open(ARMOR_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>armor && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(ARMOR_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
//		cmd = QUIT;
		success = 0;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>armor && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
armor.displayLong();

			}  //else
inFile.close();
	
	return success;
}
int getThrownFromDB(Thrown& thrown, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading Thrown item from the Database"<<endl;


int success=0;
ifstream inFile;
int filelines=0;

inFile.open(THROWN_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>thrown && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(THROWN_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
//		cmd = QUIT;
		success = 0;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>thrown && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
thrown.display();

			}  //else
inFile.close();
	
	return success;
}
int getAmmoFromDB(Consumable& ammo, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading Ammo item from the Database"<<endl;


int success=0;
ifstream inFile;
int filelines=0;

inFile.open(AMMO_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>ammo && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(AMMO_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
//		cmd = QUIT;
		success = 0;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>ammo && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
ammo.display();
cout <<endl;

			}  //else
inFile.close();
	
	return success;
}

int getPotionFromDB(Potion& potion, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading Potion item from the Database"<<endl;


int success=0;
ifstream inFile;
int filelines=0;

inFile.open(POTION_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>potion && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(POTION_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
//		cmd = QUIT;
		success = 0;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>potion && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
potion.display();
cout <<endl;

			}  //else
inFile.close();
	
	return success;
}
int getItemFromDB(Item& item, int cmd)  //Monster &aMonster)
{
//get Weapon from data base
cout <<"Reading General item from the Database"<<endl;


int success=0;
ifstream inFile;
int filelines=0;

inFile.open(ITEM_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>item && !inFile.eof())
		filelines++;
	cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(ITEM_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File could not be opened" << endl;
//		cmd = QUIT;
		success = 0;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>item && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = 1;
item.display();
cout <<endl;

			}  //else
inFile.close();
	
	return success;
}
#endif

