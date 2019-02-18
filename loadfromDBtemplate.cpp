//v4
#ifndef LOADFROMDBTEMPLATE_CPP
#define LOADFROMDBTEMPLATE_CPP

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<typeinfo>
#include "Item.h"
#include "Armor.h"
#include "Weapon.h"
#include "Thrown.h"
#include "Potion.h"
//#include "Actor.h"
#include "Monster.h"
#include "Hero.h"
//Includes:
// int getFileline(string filename), string getItemFilename(T& x), bool getFromDB(T& x, int cmd), bool getFromDB(T& x), 

using namespace std;

int getFileline(string filename)
{
	string x;
	int filelines=0;
	ifstream inFile;
	inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
		}   
	else 
	{
	while(getline(inFile,x) && !inFile.eof())
		filelines++;
	}
	inFile.close();
	return filelines;
}


template<class T>
string getItemFilename(T& x)
{	
	Item item;
	Thrown thrown;
	Weapon weapon;
	Armor armor;
	Potion potion;
	Consumable ammo;
	Monster monster("temp", 1);
	string filename;
	ifstream inFile;

	if(typeid(x) == typeid(item))
		 filename = "Items.txt";
	else if(typeid(x) == typeid(thrown))
		 filename = "Thrown.txt";
else if(typeid(x) == typeid(potion))
		 filename = "Potion.txt";
else if(typeid(x) == typeid(ammo))
		 filename = "Ammo.txt";
	else if(typeid(x) == typeid(weapon))
		 filename = "Weapon.txt";
	else if(typeid(x) == typeid(armor))
		 filename = "Armor.txt";
	else if(typeid(x) == typeid(monster))
		 filename = "Monster.txt";
	else
		{
		 cout <<"Don't understand"<<endl;
		filename = " ";
		}
	return filename;
}

template<class T>
bool getFromDB(T& x, int cmd)  //retrive a specific object
{
	bool success = 0;
	Item item;
/*	Thrown thrown;
	Weapon weapon;
	Armor armor;
	Monster monster("temp",1); */
	string filename = getItemFilename(x);
	ifstream inFile;

	int filelines = getFileline(filename);

inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
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
	while( inFile>>x && linenumber != cmd && !inFile.eof())
				{	
	linenumber++;
				}
		success = 1;
			}  //else
inFile.close();

	return success;
}

template<class T>
bool getFromDB(T& x)  //to search through database for objects
{
	const int QUIT = 0;
	bool success = 0;
	int cmd;
/*	Item item;
	Weapon weapon;
	Armor armor;
	Monster monster("Temp",1); */
	string filename = getItemFilename(x);
	ifstream inFile;

	int filelines = getFileline(filename);
cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
QUIT << " to exit and use selected object ";
cin >> cmd;
	cout <<"-----id entered = " <<cmd<<endl;
	while(cmd != QUIT)
	{

inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
		cmd = QUIT;
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
	while( inFile>>x && linenumber != cmd && !inFile.eof())
				{	
	linenumber++;
				}
		success = 1;
	x.display();
cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
QUIT << " to exit and use selected object";
cin >> cmd;
	cout <<"-----id entered = " <<cmd<<endl;
			}  //else
inFile.close();
	}

	return success;
}

void fillInventory(Hero& champ)
{

		char toadd;
	Weapon aweapon;
	Armor aarmor;
	Consumable ammo;
	Potion apotion;
	Thrown athrown;
	//Add and remove weapons.  Maybe make this set starting eq. based on class etc.
	cout<<"Adjust inventory of heros"<<endl;
	cout<<"Give a healing potion and acid vial to start"<<endl;
					getFromDB(athrown, 3);
					champ.inventory.addThrown(athrown);
					getFromDB(apotion, 1);
					apotion.setNumber(2);
					champ.inventory.addPotion(apotion);

		cout <<"Add a weapon 'w', armor 'a', item 'i', look 'l' what you have, or 'q' to quit: ";

		cin>>toadd;
	while(toadd!='q')
			{
		switch(toadd) {
			case 'w' :  cout<<"load weapon by id or line number"<<endl;
				getFromDB(aweapon);
				champ.inventory.addWeapon(aweapon);
			break;
			case 'a' : cout <<"load armor by id or line number"<<endl;
				getFromDB(aarmor);
				champ.inventory.addArmor(aarmor);
			break;
			case 'i' : 
					{					
					cout <<"Add a thrown substance, potion or ammo? enter 't', 'p', 'a' or 'q' to quit"<<endl;
					cin>>toadd;
				if(toadd == 't' || toadd == 'T')
						{
					getFromDB(athrown);
					champ.inventory.addThrown(athrown);
						}
				if(toadd == 'p')
						{
					//cout<<"Adding items not inplemented yet"<<endl;
					getFromDB(apotion);
					champ.inventory.addPotion(apotion);
						}
				if(toadd == 'a')
						{
					getFromDB(ammo);
					champ.inventory.addAmmo(ammo);
						}
					}
			break;
			case 'l' : champ.inventory.showList();
			break;
			default : cout<<"somehting went wrong, don't understand"<<endl;
				}
		cout <<"Add a weapon 'w', armor 'a', item 'i', or look 'l' what you have, or 'q' to quit: ";
		cin>>toadd;
			}
	
	cout<<"Hero's inventory finished"<<endl<<"Here it is:"<<endl;
		
		cout<<" --- "<< champ.Actor::getName()<<endl;
	champ.inventory.showList();	

}		

#endif

