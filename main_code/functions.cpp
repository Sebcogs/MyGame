#ifndef FUNCTIONS_CPP
#define FUNCTIONS_CPP
//v5
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<map>
#include "GameMap.h"
#include<vector>
#include "Parser.h"
//#include "Actor.h"
#include "Hero.h"
#include "RoomDisplay.h"
	#include "Party.h"
#include "Dice.h"
#include "caste.h"


#include "loadfromDBtemplate.cpp"
using namespace std;

/*
const static string ARMOR_FILE = "inventory/Armor.txt";
const static string WEAPON_FILE = "inventory/Weapon.txt";
const static string THROWN_FILE = "inventory/Thrown.txt";
const static string POTION_FILE = "inventory/Potion.txt";
const static string AMMO_FILE = "inventory/Ammo.txt";
const static string ITEM_FILE = "inventory/Item.txt";
const static string SPELL_FILE = "Spell.txt";
*/

bool processCommand(Hero& champ, Parser& parser, GameMap& gamerooms, Command command);

// comment out for testing
bool processFightCommand(Party& party, Hero champ[], Parser& parser, GameMap& gamerooms, Command myCommand, RoomDisplay& thisRoom, int player);
void goRoom(GameMap& gamerooms, Command command, RoomDisplay& thisRoom, int players);
bool throwAt(Hero& attacker, Monster& defender, int distance, Thrown athrown);
bool fight(Hero& attacker, Monster& defender, int distance);
bool fight(Monster& attacker, Hero& defender, int distance);
void equip(Hero& champ);

int getEnemyTarget(int numberOfEnemies, RoomDisplay thisRoom);
int getHeroTarget(Party party, int player);
bool getIsTargetEnemy();

bool checkSpellSave(Monster& attacker, Hero& defender);
 
int extractIDs(vector<int>& ids, string input);
//void fillInventory(Hero& champ);  //in loadfromDBtemplate file
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
		gamerooms.getCurrentRoom().lookLoot();
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
			try{
	heroNumber = party.whichPartyMember();
			}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
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
    case CASTE :
    {
        //cout<<"Not implemented yet"<<endl;
        //which hero to caste?
        		string name;
		//cout <<"Equip character "<<endl;
		if(!myCommand.hasSecondWord())
			{
			try{
	heroNumber = party.whichPartyMember();
			}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
	name = party.getHero(heroNumber);
			}
		else
			name = myCommand.getSecondWord();
	bool found = false;
    int checkheroNumer;
	for(int i=0; i<numberofHeros; i++)
		{
		if(name == champ[i].getName())
			{
			cout << name <<endl;
			found = true;
			checkheroNumer = i;
			}
		}
		if(!found)
			cout<<"second word did not match character name"<<endl;
        if(found)
        {
        //which hero, caste on which other hero
        int target = getHeroTarget(party, checkheroNumer);	//what about caste on self??
            //assume they are close enough
            int dis=1;
        //Spell aspell;
        //aspell = caste(champ[checkHeroNumer], champ[target], dis);
		Caste* caste3 = new Caste(&champ[checkheroNumer], &champ[target], dis);  //, aspell);
		caste3->casteSpell();
		//what about area effect??
		if(caste3->getAreaRange()>0)
		{
			cout<<"Check for area effect on Friends"<<endl;
			//how to find distance among heros?
			for(int x = 0; x<numberofHeros; x++)
			{
				if(x != checkheroNumer && x!= target)
				{
					cout<<champ[x].getName()<<" is close and gets area effect"<<endl;
					caste3->setNextTarget(&champ[x]);
					caste3->casteSpell();
				}
			}
		}
		delete caste3;
   //     caste(champ[checkheroNumer], champ[target], dis);
        /* if(!aspell.getIsSingleTarget())
            {
            cout<<"implement area effect later..."<<endl;
            } */
        }
		cin.ignore(100, '\n');

    }
    break;
	case EQUIP : 
		{
		string name;
		cout <<"Equip character "<<endl;
		if(!myCommand.hasSecondWord())
			{
			try{
	heroNumber = party.whichPartyMember();
			}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
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
			try{
		heroNumber = party.whichPartyMember();
			}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
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
		cout <<"Press any button to continue."<<endl;
	cin.ignore(100, '\n');
		}
	break;
	case MARCH :
			{
	try{
			party.setMarchingOrder();
	}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	}
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
			try{
			heroNumber = party.whichPartyMember();
				}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
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
	try{
				Item thing = currentRoom.chest[choice].takeItem();
				cout <<"Remove 1st item in container: "<< thing.getName() <<endl;
				champ[i].inventory.addItem(thing);
		}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	}
						}
						else if(currentRoom.chest[choice].bag.potions.size()>0)
						{
	try{
				Potion thing = currentRoom.chest[choice].takePotion();
				cout <<"Remove 1st potion in container: "<< thing.getName() <<endl;
				champ[i].inventory.addPotion(thing);
		}
	catch(string msg)
	{
	cout <<"An exception was thrown"<<endl;
	cout <<msg<<endl;
	}
						}
			//	champ[i].inventory.showList();
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
		
			cout <<"not implemented yet. use character name as second word, will want to include give and use."<<endl;
			//	if(secWord == "give")
			//	{
			//	}
			//	if(secWord == "use")
			//	{
			//	} 
			string name;		
			
		if(!myCommand.hasSecondWord())
			{
			try{
	heroNumber = party.whichPartyMember();
			}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				heroNumber = 1;
				}
	name = party.getHero(heroNumber);
			}
		else
		name = myCommand.getSecondWord();
		
	bool found = false;
	for(int i=0; i<numberofHeros; i++)
		{
		if(name == champ[i].getName())
			{
			found = true;
			int player = i;
			char doChar;
			cout <<"What does "<<name<<" want to do with items? 'u'-Use (drink) or 'g'-give?"<<endl;
			cin>>doChar;
			cin.ignore(100, '\n');
			if(doChar == 'u')
				{
					// should check that current HP != max HP otherwise don't need to heal 
			if(champ[player].getHP() != champ[player].getMaxHP())
			{
				bool itemFound = false;	
					int id;
					Potion apotion;
					cout <<" Which potion ID do you want to drink?" <<endl;
					cout << "Choices are : "<< champ[player].inventory.getPotionIDs();
						cin>> id;
					for(int i=0; i<champ[player].inventory.getPotionNum(); i++)
						{
						if(id == champ[player].inventory.getPotionID(i))
							{
					itemFound = true;
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
						if(!itemFound)
							{
							cout<<" Error! entered ID was not found or did not match choices available.  Try again"<<endl;
							}
				}
			else
				cout<<"You already have max HP so don't need to drink the potion"<<endl;
			}
			else if(doChar == 'g')
				{
				cout<<"What does "<<name<<" want to give?"<<endl;
	bool itemFound = false;	
					int id;
					Potion apotion;
					cout << "Choices are : "<< champ[player].inventory.getPotionIDs();
						cin>> id;
					for(int i=0; i<champ[player].inventory.getPotionNum(); i++)
						{
						if(id == champ[player].inventory.getPotionID(i))
							{
					itemFound = true;
					champ[player].inventory.potions[i].display();
					//champ[player].inventory.potions[i].removePotion();
				apotion = champ[player].inventory.dropPotion(i);
				//apotion.display();
							}
						}
						if(!itemFound)
							{
							cout<<" Error! entered ID was not found or did not match choices available.  Try again"<<endl;
							}
						else if(itemFound)
						{
						cout <<"Who will receive the "<<apotion.getName()<<"?"<<endl;
				int receiveheroNumber;
				try{
			receiveheroNumber = party.whichPartyMember();
					}
			catch(string msg)
				{
				cout <<"An exception was thrown"<<endl;
				cout <<msg<<endl;
				cout <<"Use hero number 1"<<endl;
				receiveheroNumber = 1;
				}
	string receiveName;
	receiveName = party.getHero(receiveheroNumber);
	int champNum;
	for(int j=0; j < party.getMemberNumber(); j++)
	{
		if(receiveName == champ[j].getName())
			champNum = j;
	}
	//cout <<"check champ name: "<<champ[champNum].getName()<<endl;
	
	cout<<name<<" will give "<<apotion.getName()<<" to "<<receiveName<<endl;
		champ[champNum].inventory.addPotion(apotion);
				}
			else
				cout <<"Did not understand, try again"<<endl;
			}
		}
		if(!found)
			cout<<"second word did not match character name"<<endl;
		
			}
			cin.ignore(100, '\n');
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
	const string MSG = "input error";
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
		cout <<"Press any button to continue."<<endl;
	cin.ignore(100, '\n');
		player--;
		}
	break;
		case ATTACK :
			{
		//	cout <<"not implemented yet"<<endl;
	Room currentRoom = gamerooms.getCurrentRoom();
		int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
        int monsterNumber;
	try{
	monsterNumber = getEnemyTarget(numberOfEnemies, thisRoom);
	}
	catch(string msg){
		cout<<"Caught error"<<endl;
		cout<<msg<<endl;
		player--;
		break;
	}

		Monster aMonster = currentRoom.enemies.getMonster(monsterNumber);  //choose monster
			
		while(!aMonster.aliveOrDead() && monsterNumber < numberOfEnemies)  //dead
		{
		cout <<"Monster # "<<monsterNumber <<" is dead, ";
		monsterNumber ++;
		cout <<"using monster # "<<monsterNumber<<endl;
		aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monsterNumber);
		}
	
			int dis = thisRoom.getDistance(player,monsterNumber);
		bool success = fight(champ[player], aMonster, dis);

		if(success)
			{
			//	cout <<"Monster is alive "<< aMonster.aliveOrDead()<<endl;
		currentRoom.enemies.updateMonster(aMonster, monsterNumber);
	//bool badguys = 	currentRoom.getHasEncounter();
		//	cout<<"In function attack, getHasEncounter: "<<badguys<<", then update room"<<endl;
		gamerooms.updateRoom(currentRoom);
		thisRoom.updateRoom(currentRoom);
			}
		else 
			player--;

		// 
			}
	break;		
     case CASTE :
    {
        bool targetEnemy = true;    //false if target a hero.
        if(champ[player].getHasMagic())
        {
            targetEnemy = getIsTargetEnemy();
            if(targetEnemy)
            {
        //find enemy
        Room currentRoom = gamerooms.getCurrentRoom();
		bool success = false;
		int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
        int monsterNumber;
	try{
	monsterNumber = getEnemyTarget(numberOfEnemies, thisRoom);
	}
	catch(string msg){
		cout<<"Caught error"<<endl;
		cout<<msg<<endl;
		player--;
		break;
	}
			
			Monster aMonster = currentRoom.enemies.getMonster(monsterNumber);  
			
            while(!aMonster.aliveOrDead() && monsterNumber < numberOfEnemies)  //dead
            {
            cout <<"Monster # "<<monsterNumber <<" is dead, ";
            monsterNumber ++;
            cout <<"using monster # "<<monsterNumber<<endl;
            aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monsterNumber);
            }
	
			int dis = thisRoom.getDistance(player, monsterNumber);
            Caste* caste = new Caste(&champ[player], &aMonster, dis);
			success = caste->casteSpell();
			//}
//	delete caste;
        //    Spell aspell;
        //    bool success =false;
        //    aspell = caste(champ[player], aMonster, dis, success);
         //   cout<<"Finished caste function, success is: "<<success<<endl;
            if(success)     //spell can be caste
                {
                cout<<"Finished casting spell, update monster"<<endl; 
                currentRoom.enemies.updateMonster(aMonster, monsterNumber);
                cout<<"Checking for area effect."<<endl;
                if(caste->getAreaRange() > 0)    //check is has area effect.
                    {
                    for(int i=0; i<numberOfEnemies; i++)
                        {
                        if(i!=monsterNumber)
                            {
                            //bool temp = false;  //dumby success variable.
                            cout<<"  !!!!Area affect spell, hits other targets too!!!!"<<endl;

                            int dis = thisRoom.getMonsterDistance(monsterNumber, i);   //distance from first monster
                            if(dis<=caste->getAreaRange())
								{
								Monster bMonster;
								bMonster = gamerooms.getCurrentRoom().enemies.getMonster(i);
								caste->setNextTarget(&bMonster);
								caste->casteSpell();
								 
                            currentRoom.enemies.updateMonster(bMonster, i);
								}
                            }
                        }
                    } 

                gamerooms.updateRoom(currentRoom);
                thisRoom.updateRoom(currentRoom);
                }
            else            //what if spell is unsuccessful??
                {   
                cout<<"Reduce player number since can't caste"<<endl;
                player--;
                }
				delete caste;
            }
            else    //target Hero 
            {
                //choose hero number
                int targetHero = getHeroTarget(party, player);
                cout<<"You chose hero "<<champ[targetHero].getName()<<endl;
                //caste spell
                //Spell aspell;
                int dis = thisRoom.getPlayerDistance(player, targetHero);   //check this
				Caste* caste3 = new Caste(&champ[player], &champ[targetHero], dis);  //, aspell);
				bool success = caste3->casteSpell();
				//delete caste3;
                //bool success;
                //success = caste(champ[player], champ[targetHero], dis);
                if(!success)
                    player--;
				else if(success)
				{
					//check for area effect on other heros
					if(caste3->getAreaRange()>0)
					{
					cout<<"Check for area effect on Friends"<<endl;
					//how to find distance among heros?
					for(int x = 0; x<numberofHeros; x++)
						{
						if(x != player && x!= targetHero)
							{
								dis = thisRoom.getPlayerDistance(targetHero, x);
								if(dis<caste3->getAreaRange())
								{
							cout<<champ[x].getName()<<" is close and gets area effect"<<endl;
							caste3->setNextTarget(&champ[x]);
							caste3->casteSpell();
								}
							}
						}
					}
				}
				delete caste3;
            }
        }
        else    //player has magic
        {
            cout<<"You don't know magic, try a different action"<<endl;
            player--;
        }
    //    if(player<0)
    //        player=0;
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
					
				
					Room currentRoom = gamerooms.getCurrentRoom();
					int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
				bool success = false;
				int monsterNumber;  //choose monster
			try{
				monsterNumber = getEnemyTarget(numberOfEnemies, thisRoom);
				}  //getEnemyTarget has a throw for some cases
				catch(string msg){
				//cout<<"Caught error"<<endl;
				cout<<msg<<endl;  //error exit code
				player--;
				break;  
				}

					Monster aMonster = currentRoom.enemies.getMonster(monsterNumber);  //choose monster
					athrown = champ[player].inventory.dropThrown(i);
					while(!aMonster.aliveOrDead() && monsterNumber < numberOfEnemies)  //dead
						{
					monsterNumber ++;
				//	cout <<"using monster # "<<monsterNumber<<endl;
					aMonster = gamerooms.getCurrentRoom().enemies.getMonster(monsterNumber);
						}
	
					int dis = thisRoom.getDistance(player,monsterNumber);
					success = throwAt(champ[player], aMonster, dis, athrown);
		//}
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
				//bool badguys = 
				currentRoom.getHasEncounter();
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
	case TURN :
		{
		bool success = false;
			cout<<"In processFightCommand turning case."<<endl;
			Room currentRoom = gamerooms.getCurrentRoom();
			int numberOfEnemies = gamerooms.getCurrentRoom().enemies.getNumberAppear();
			for(int y=0; y<numberOfEnemies; y++)
			{
			Monster amonster = currentRoom.enemies.getMonster(y);
				if(amonster.aliveOrDead())
				{	//should sort by closest first
				int dis = thisRoom.getDistance(player,y);
				bool turned;
				turned = champ[player].myClass->turning->turnMonster(amonster, dis);
				currentRoom.enemies.updateMonster(amonster, y);
					if(turned)
					success = true;
				}
			}
		champ[player].myClass->turning->finishTurn();
				gamerooms.updateRoom(currentRoom);
				thisRoom.updateRoom(currentRoom);
			if(!success)
				{
				player--;
				cout<<"You can't turn so choose something else."<<endl;
				}
				
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
         //   cin.ignore(100, '\n');
	return wantToQuit;
}

	

//function to control fight.

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
				int weapPos = attacker.inventory.myEquip.getHandPosition();
				int ammoPos;
		string weapname = attacker.inventory.weapons[weapPos].getName();
		bool hasAmmo=false;
		if(weapname == "Short_bow" || weapname == "Long_bow")
		{
			for(int x = 0; x < attacker.inventory.ammo.size(); x++)
				if(attacker.inventory.ammo[x].getName()=="Arrows")
				{
					hasAmmo = true;
					ammoPos = x;
				}
		}
		else if(weapname == "Crossbow_light")
		{
			for(int x = 0; x < attacker.inventory.ammo.size(); x++)
				if(attacker.inventory.ammo[x].getName()=="Bolts")
				{
					hasAmmo = true;
					ammoPos = x;
				}
		}
		else if(weapname == "Sling")
		{
			for(int x = 0; x < attacker.inventory.ammo.size(); x++)
				if(attacker.inventory.ammo[x].getName()=="Bullets")
				{
					hasAmmo = true;
					ammoPos = x;
				}
		}
		if(hasAmmo)
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
		attacker.inventory.dropAmmo(ammoPos);
			}
			else
			cout <<"You have no ammo to shoot!"<<endl;
		}
			else
			cout <<"you are out of range. Try a different action."<<endl;
		}
	if(success)	
	{
	int MonsterAC = defender.getAC(); //
    for(int index = 0; index<attacker.myRace->getMaxFavoured(); index++)  //check for atk bonus against favoured enemies
    {
        if(defender.getType() == attacker.myRace->getFavouredEnemy(index))
        {
            hitRoll++;
            cout<<"You have a bonus +1 on attack rolls due to your special training."<<endl;
        }
    }

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
		bool alive = attacker.aliveOrDead();
        bool useSpecial = attacker.useSpecial();

		bool success = false;
	int hitRoll;
	if(alive)
    {
	cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
 
		if(distance == 1 ) //also need to check for equipped weapon
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
        for(int index = 0; index<defender.myRace->getMaxFavoured(); index++)  //check if there is a bounus to AC from favoured enemies
            {
            if(attacker.getType() == defender.myRace->getDodgeEnemy(index))
                {
            MonsterAC = MonsterAC +4;
            cout<<"Special training gives the defender +4 to dodge AC."<<endl;
                }
            }
        

 		cout << "Monster hitRoll "<< hitRoll << " vs your AC " <<MonsterAC<<endl;
	if(hitRoll >= MonsterAC)
		{
            if(attacker.useSpecialDmg() || !useSpecial)
            {
		int dmg;		
		cout <<" the monster hits "<< defender.getName() <<"! "<<endl;
		dmg = attacker.getDmgRoll();
		cout <<" Damage for "<<dmg<<endl;
        defender.receiveDamage(dmg);
            }
        //check is using special attack
        if(useSpecial)
        {
            //save throw
            bool saveSuccess = checkSpellSave(attacker, defender);
            //if fail set condition and duration
            if(!saveSuccess)
            {
            defender.condition.setCondition(attacker.getEffectCode());
            Dice dice(1,attacker.getDuration());
            defender.condition.setDuration(dice.getValue());
            }
        }
		
		}
	else
		{
		cout <<" Missed "<<endl;
		
		}
	//cin.ignore(100, '\n');
	}
    }
	return success;
}

//Function used in the normal processCommand GO
//used to move the party to the desired room

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


//function used during load to extract ID numbers from file

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
		cout << "File -"<<fileName<<"- could not be opened" << endl;
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
void save(string data)
{
	cout << "Save Hero data: "<<endl;
	//myHero.outputData();
    
	char filename[10];
	cout << "Enter filename: ";
	cin >> filename;

	ofstream outFile;
	outFile.open(filename);
  		 if(!outFile.good())
     		 cout << "File -"<<filename<<"- could not be opened" << endl;
  	 	else
   			{
				
		//outFile << myHero.saveData();      //for some reason the race and class pointers are deleted
        outFile << data;
		//cout << "Saved"<< endl;
		//myHero.outputData();
			}
			
			outFile.close();
			//cout<<"closing file"<<endl;
	//return 0;
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
            //how to implement starting gear? charClass::getStartingGear() returns string
		fillInventory(champ);

		cout <<" keep and save? y or n? ";
		char keep;
		cin >> keep;
			if(keep == 'y')
			{
			//cout<<"save function here"<<endl;
			//Hero temp = champ;
			save(champ.saveData());
			cout<<"Save complete"<<endl;
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
		bool found = false;
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
				found = true;
				//champ.inventory.armor[i].wield();
				champ.inventory.equipArmor(i);
				cout << "New AC is "<<champ.getAC()<<endl;
				//cout << "Equipped " << champ.inventory.armor[i].Item::getName() <<endl;
						}
					} //for
			if(!found)
				{
			cout << "Can't equip that! Something went wrong "<<endl;
			wOrA = QUIT;
				}
					
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
			found = true;
			//champ.inventory.weapons[i].wield();
			champ.inventory.equipWeapon(i);
			//cout << "Equipped " << champ.inventory.weapons[i].Item::getName() <<endl;
				}
			} //for
			if(!found)
				{
				cout << "Can't equip that! Something went wrong "<<endl;
				wOrA = QUIT;
				}

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
/*
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
		cout << "File -"<<WEAPON_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<WEAPON_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<ARMOR_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<ARMOR_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<THROWN_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<THROWN_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<AMMO_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<AMMO_FILE<<"- could not be opened" << endl;
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
		cout <<"File -"<<POTION_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<POTION_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<ITEM_FILE<<"- could not be opened" << endl;
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
		cout << "File -"<<ITEM_FILE<<"- could not be opened" << endl;
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

bool getSpellFromDB(Spell& spell, int cmd)  //Monster &aMonster)
{
//get Spell from data base
//cout <<"Reading General item from the Database"<<endl;


bool success=0;
ifstream inFile;
int filelines=0;

inFile.open(SPELL_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File -"<<SPELL_FILE<<"- could not be opened" << endl;
		success = 0;
	}   
	else 
	{

	while(inFile>>spell && !inFile.eof())
		filelines++;
	//cout << "filelines = "<<filelines<<endl;
	}
	inFile.close();

	//cout <<"-----id entered = " <<cmd<<endl;

	//cout <<"in while loop"<< endl<<"opening file "<<endl;	
inFile.open(SPELL_FILE, ios::in);// | ios::binary);
if(!inFile.good())
	{      
		cout << "File -"<<SPELL_FILE<<"- could not be opened" << endl;
//		cmd = QUIT;
		success = false;
	}   
	else 
	{
	while(cmd > filelines)
			{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
			}
		
int linenumber = 1;
	while( inFile>>spell && linenumber != cmd && !inFile.eof())
				{	
	//cout <<"Line "<<linenumber<<endl;
	linenumber++;
				}
success = true;
//spell.outputData();	//	.display();
cout <<endl;

			}  //else
inFile.close();
	
	return success;
}
 * */
int getEnemyTarget(int numberOfEnemies, RoomDisplay thisRoom)
{
    int monsterNumber;
    const string MSG1 = "input error - not interger-, exiting";
	const string MSG2 = "exit code entered";
    thisRoom.getTarget();
		cout <<"Choose target # or -1 to exit: ";
		cin >> monsterNumber;
	cin.ignore(100, '\n');	
		if(!cin)
			throw(MSG1);  //for try and catch where this function is called.
		if(monsterNumber <0){
			throw(MSG2);
			//monsterNumber=-1;
		}

		if(monsterNumber>numberOfEnemies-1){
			cout<<"Your chose is more then the number of enemies, set to first enemy"<<endl;
			monsterNumber = 0;
		}
			
    return monsterNumber;
}
int getHeroTarget(Party party, int player)
{
    cout<<"Choose the hero you want to caste on."<<endl;
    cout<<"     -- player number used is: "<<player+1<<endl;
	int hero = party.whichPartyMember();
//    int hero = party.whichPartyMember(player);
   // cout<<"You chose "<<champ[hero].getName();
    return hero;
}
bool getIsTargetEnemy()
{
    cout<<"Caste the spell on Enemy (e) or Hero (h)?: "<<endl;
            char enemyOrHero;
            cin>>enemyOrHero;
            cin.ignore(100, '\n');
            if(enemyOrHero == 'e')
                return true;
            else if(enemyOrHero == 'h')
                return false;
            else
            {
                cout<<"Error, wrong input type.  Enter char 'e' or 'h'."<<endl;
                return getIsTargetEnemy();
            }
}

#endif

