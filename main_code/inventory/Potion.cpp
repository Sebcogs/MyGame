#ifndef POTION_CPP
#define POTION_CPP
//v4

#include<iostream>
#include<string>
//#include "Item.h"
#include "Potion.h"
using namespace std;


ostream& operator<<(ostream& out, Potion aPotion)
{
	out << aPotion.getID() << " " << aPotion.getName() << "  "<< aPotion.getWeight() <<" " 
<<" "<< aPotion.getHealMult()<<" "<<aPotion.getHealDie()<<" "<< aPotion.getNumber() <<" " << aPotion.getValue() <<" "<< aPotion.getDesc()<<endl;
   return out;
}
istream& operator>>(istream& in, Potion& aPotion)
{
	string name;
	double weight;
	int die, multi, number, id, price;
	
	string desc;	
	in >> id >> name >> weight>> multi >> die >> number >> price;
 getline(in, desc);
//cout <<"Extracted name is: "<<name<<endl;
aPotion.setFields(weight, name, desc, id, price, die, multi);
	aPotion.setNumber(number);
	return in;
} 

Potion::Potion():Consumable()
{
	Consumable::setFields(0.25, "potion", "A Potion to drink", 0);
	healDie = 3;
	healMult = 1;
	//number = 1;
}

Potion::Potion(double weight, string name, string desc, int id, int price, int die, int mult=1):Consumable(weight, name, desc, id, price)
{
	this->healDie = die;
	healMult = mult;
	//number = 1;
}

void Potion::setFields(double weight, string name, string desc, int id, int price, int die, int mult)
{
	Consumable::setFields(weight, name, desc, id, price);
	healDie = die;
	healMult = mult;
	//number = 1;
}

int Potion::getHealDie()
{
	return healDie;
}
int Potion::getHealMult()
{
	return healMult;
}
/* int Potion::getHealRoll()
{
		srand( time(0)+healDie);
		Dice dice(healMult,healDie);
	roll = dice.getValue();
	cout <<"Heal roll of "<<dice.getValue()<< endl;
	return roll;
} */
void Potion::display()
{
	//cout <<number<<" ";
	Consumable::display();
	cout <<" Heals for: "<<getHealMult()<<"d"<<getHealDie()<<".";
	cout<<endl;
}
void Potion::addPotion()
{
	addConsumable();
}
void Potion::removePotion()
{
	removeConsumable();
}

#endif		
