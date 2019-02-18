#ifndef ARMOR_CPP
#define ARMOR_CPP
//v4
#include<iostream>
#include<string>
#include "Item.h"
#include "Armor.h"
using namespace std;

ostream& operator<<(ostream& out, Armor anArmor) //const Armor& anArmor)
{
	//out <<"-"<< /*"Item name " <<*/ anArmor.Item::itemName << "  "/*weight"*/ << anArmor.Item::weight<<"lbs, AC: " << anArmor.ACmod;

	out << anArmor.getID() << " " << anArmor.getName() <<" "<< anArmor.getWeight() << " " <<anArmor.getACmod() << " " << anArmor.getPenalty() << " " <<anArmor.getMaxDex() <<" "<< anArmor.getSize() << " " << anArmor.getValue() << " " << anArmor.Item::description << endl;
   return out;
}
istream& operator>>(istream& in, Armor& anArmor)
{

string name;
	double weight, value;
	int id, ac, penalty, maxdex;
	char size;
	string desc;	
	in >> id >> name >> weight>> ac >> penalty >> maxdex >> size >> value;
 getline(in, desc);

	anArmor.setFields(weight, name, desc, ac, penalty, maxdex, id);
	anArmor.setSize(size); 
	anArmor.setValue(value);
	return in;
}
Armor::Armor():Item()
{	//Make a basic Armor
	Item::setFields(1, "Apron", "A crappy +1 leather apron you can use as Armor", 1);
	ACmod = 1;
	penalty = 0;
	maxDexMod = 0;
	equipped = false;
	size = 'm';
}
/*
Armor::Armor(double pounds, string name, string desc, int ac=1, int pen =0) : Item(pounds, name, desc)
{
    ACmod = ac;
	penalty = pen;
}
 */
void Armor::setFields(double weigh, string name, string desc, int ac, int pen, int maxdex, int id)
{
    Item::setFields(weigh, name, desc, id);
   	ACmod = ac;
	penalty = pen;
	maxDexMod = maxdex;
    equipped = false;

}

void Armor::display()
{
    //cout << " -" <<getSize();
	Item::display();
	cout << " -" <<getSize()<<"-";
cout <<" AC: +"<<ACmod<<", penalty: " << penalty << ", DEX max: "<<getMaxDex();
	if(equipped)
		cout <<" Equipped";
	cout <<endl;
}
int Armor::getACmod()
{
    return ACmod;
}
int Armor::getPenalty()
{
    return penalty;
}
void Armor::wield()
{
    equipped = true;
}
void Armor::unwield()
{
    equipped = false;
}
void Armor::setSize(char sizechar)
{	//If a character is small, all weapons and armor most be small too
 size = sizechar;
}
char Armor::getSize()
{
	return size;
}
void Armor::displayLong()
{
display();
cout << Item::getDesc()<<endl;
}
int Armor::getMaxDex()
{
	return maxDexMod;
}
bool Armor::isEquipped()
{
	return equipped;
}

#endif
