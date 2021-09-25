#ifndef THROWN_CPP
#define THROWN_CPP
//v4

#include<iostream>
#include<string>
//#include "Item.h"
//#include "Consumable.h"
#include "Thrown.h"
using namespace std;


ostream& operator<<(ostream& out, Thrown aThrown)
{
	out << aThrown.getID() << " " << aThrown.getName() << "  "<< aThrown.getWeight() <<" " 
<<" "<< aThrown.getDmg()<<" "<<aThrown.getRounds()<<" "<< aThrown.getNumber() <<" " << aThrown.getValue() <<" "<< aThrown.getDesc()<<endl;
   return out;
}
istream& operator>>(istream& in, Thrown& aThrown)
{
	string name;
	double weight;
	int dmg, rounds, number, id, price;
	
	string desc;	
	in >> id >> name >> weight>> dmg >> rounds >> number >> price;
 getline(in, desc);
//cout <<"Extracted name is: "<<name<<endl;
aThrown.setFields(weight, name, desc, id, price, dmg, rounds);
	aThrown.setNumber(number);
	return in;
} 

Thrown::Thrown(): Consumable()//,Item()
{
	Item::setFields(0.25, "bomb", "A thrown weapon", 0);
	dmg = 3;
	effectRounds = 1;
	//number = 1;
}

Thrown::Thrown(double weight, string name, string desc, int id, int price, int dmg, int rounds=1): Consumable(weight, name, desc, id, price)//, Item(weight, name, desc, id, price)
{
	this->dmg = dmg;
	this->effectRounds = rounds;
	//number = 1;
}

void Thrown::setFields(double weight, string name, string desc, int id, int price, int dmg, int rounds)
{
	Item::setFields(weight, name, desc, id, price);
	this->dmg = dmg;
	this->effectRounds = rounds;
	//number = 1;
}

int Thrown::getDmg()
{
	return dmg;
}
/* int Thrown::getDmgRoll()
{
		srand( time(0)+dmg);
		Dice dice(mult,Dmg);
	roll = dice.getValue() + getMod(STR);
	cout <<"Damage roll of "<<dice.getValue()<<" + Str Mod of "<<getMod(STR)<<endl;
	return roll;
} */
void Thrown::display()
{
	
	Consumable::display();
	
	cout <<" Damage: 1d"<<getDmg()<<" plus splash damage";
	if(effectRounds >1)
		cout<<" that lasts "<<effectRounds<< " rounds";
	cout<<endl;
}
int Thrown::getRange()
{
	return range;
}
int Thrown::getRounds()
{
	return effectRounds;
}
void Thrown::addThrown()
{
	addConsumable();
}
void Thrown::removeThrown()
{
	removeConsumable();
}
#endif		
