#ifndef CONTAINER_CPP
#define CONTAINER_CPP
//v4
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "Container.h"
#include "Dice.h"
using namespace std;

//This is to make chest, bags, or other containers for loot in a room
Container::Container()
{ //create an empty container
	type = "";
	description = "";
	locked = false;
	Inventory invent(1, 0);
	bag = invent;
}
	
Container::Container(string type, string desc, int level, int percent)
{
	this->type = type;
	description = desc;
	locked = false;
	Inventory invent(level, percent);
	bag = invent;
	//bag.addItem(item);
	//bag.addWeapon(Weapon);
	//bag.addArmor(Armor);
	//contains default amount of coins
}
void Container::showType()
{
	cout << type <<endl;
}
	
void Container::getDesc()
{
	cout << description <<endl;
}
bool Container::isLocked() //true is locked
{
	return locked;
}	
void Container::open()
{
	getDesc();
	if(locked)
	{
	cout <<"It is locked, you can't open it"<<endl;
	}	
	else
	{
	
	cout<<"you open the "<<type<<endl;
	showContents();
	}
}
void Container::showContents()
{
	cout <<"This "<<type<<" has the following contents"<<endl;
	bag.showList();
	bag.showMoney();
}
int Container::lock()
{
	cout << "You lock the "<<type<<endl;
	locked = true;
	return 0;
}
int Container::unlock()
{
	//Pobably need to do a lock pick check
	cout<<" You attempt to unlock the "<<type<<endl;
	locked = false;
	return 0;
}
Item Container::takeItem()
{
	const string MSG = "input error";
	Item thing;
	int input;
	int max = bag.items.size();
if(max >1)
	{
	cout <<"Which item to take? 1 to "<<max;
	cin>>input;
		if(input<1)
			throw(MSG);
		if(input>max)
			throw(MSG);
	}
else if(max == 1)
	input =1;
	if(input>0 && input <=max)
		{
			thing = bag.dropItem(input-1);
		cout<<"Item "<<thing.getName() <<" removed"<<endl;
		}
	else
		cout <<"You entered a number outside the range"<<endl;
	return thing;	 	 
}
Potion Container::takePotion()
{
	const string MSG = "input error";
	Potion thing;
	int input;
	int max = bag.potions.size();
if(max >1)
	{
	cout <<"Which item to take? 1 to "<<max;
	cin>>input;
	if(input<1)
			throw(MSG);
		if(input>max)
			throw(MSG);
	}
else if(max == 1)
	input =1;

	if(input>0 && input <=max)
		{
			thing = bag.dropPotion(input-1);
		cout<<"Item "<<thing.getName() <<" removed"<<endl;
		}
	else
		cout <<"You entered a number outside the range"<<endl;
	return thing;	 	 
}
string Container::takeMoney()
{
	string money = "";
			int cp = bag.getCopper();
			int sp = bag.getSilver();
			int gp = bag.getGold();
		if(cp != 0 || sp != 0 || gp != 0)
		{	
	cout<<"Enter the amount of copper, silver and gold you want";
			int cp, sp, gp;
			cin>>cp;
			cin>>sp;
			cin>>gp;
	int copper = bag.spendMoney(cp, 0, 0);
	int silver = bag.spendMoney(0, sp, 0);
	int gold = bag.spendMoney(0, 0, gp);
		if(copper)
			money+= to_string(cp)+ " ";
		else
			money+= to_string(0)+ " ";
		if(silver)
			money+= to_string(sp)+ " ";
		else
			money+= to_string(0)+ " ";
		if(gold)
			money+= to_string(gp)+ " ";
		else
			money+= to_string(0)+ " ";
	
			cout<<"Money removed (cp, sp, gp)"<<money<<endl;
		}
		else
			{
			money = "0 0 0";
			cout <<"It was empty! "<<endl;
			}
	
	return money;
}
string Container::takeAllMoney()
{
string money = "";
	
			int cp = bag.getCopper();
			int sp = bag.getSilver();
			int gp = bag.getGold();
		if(cp != 0 || sp != 0 || gp != 0)
		{	
	int confirm = bag.spendMoney(cp, sp, gp);
	
		if(confirm)
			{
			money+= to_string(cp)+ " ";		
			money+= to_string(sp)+ " ";
			money+= to_string(gp)+ " ";
		cout<<"Money removed (cp, sp, gp)"<<money<<endl;
			}
		else
			{
			money = "0 0 0";
			cout <<"Error! There was money in the chest but it didn't confirm properly"<<endl;
			}
		} 
		else
			{
			money = "0 0 0";
			cout <<"It was empty! "<<endl;
			}
	
	
	return money;
}
	#endif
