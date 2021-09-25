#ifndef WEAPON_CPP
#define WEAPON_CPP
//v4

#include<iostream>
#include<string>
#include "Item.h"
#include "Weapon.h"
using namespace std;

ostream& operator<<(ostream& out, Weapon anWeapon)
{
	out << anWeapon.getID() << " " << anWeapon.getName() << "  "<< anWeapon.getWeight() <<" "<< anWeapon.getDieMultiple()<<" "<<anWeapon.getDie()<<" "<< anWeapon.getminCrit() << " " << anWeapon.getCritMultiple() << " " << anWeapon.getSize() << " "<< anWeapon.getRange()<< " " <<anWeapon.getValue()<< " "<< anWeapon.getDesc()<<endl;
   return out;
}
istream& operator>>(istream& in, Weapon& anWeapon)
{
	string name;
	double weight, value;
	int die, diemult, mincrit, critmult, id, range;
	char size;
	string desc;	
	in >> id >> name >> weight>> /*desc >>*/ diemult >> die >> mincrit >> critmult >> size >> range >> value;
 getline(in, desc);

anWeapon.setFields(weight, name, desc,  die, diemult, mincrit, critmult, id, range);
	anWeapon.setSize(size);
	anWeapon.setValue(value);
	return in;
} 
Weapon::Weapon():Item()
{	//Make a basic weapon
	Item::setFields(1, "pointyStick", "A crappy 1d4 stick you can use as a weapon", 1);
	die = 4;
	dieMultiple = 1;
	minCrit = 20;
	critMultiple = 2;
	equipped = false;
	size = 'm';	//default size
	IDnum = 0;
	range = 0;
}
/*
Weapon::Weapon(double pounds, string name, string desc, int dice=6, int mult=1, int crit=20, int critDmg=2) : Item(pounds, name, desc)
{
    die = dice;
    dieMultiple = mult;
    minCrit = crit;
    critMultiple = critDmg;
    equipped = false;
}
 */
void Weapon::setFields(double weigh, string name, string desc, int dice, int mult, int crit, int critDmg, int id, int dis)
{
    Item::setFields(weigh, name, desc, id);
    die = dice;
    dieMultiple = mult;
    minCrit = crit;
    critMultiple = critDmg;
    equipped = false;
	range = dis;
}

void Weapon::display()
{
	Item::display();
	cout << " -" <<getSize()<<"-";
    cout << " Damage: " << getDieMultiple() <<"d"<<getDie();
	if(equipped)
		cout <<" Equipped";
	cout <<endl;
}
void Weapon::displayLong()
{
cout << "-" <<Item::getName() << "  "<<Item::getDesc()<<" " << Item::getWeight() <<"lbs, Damage: " << dieMultiple<<"d"<<die;
    cout <<", crit " << getminCrit()<<"-20/x"<< getCritMultiple() <<endl;
}
int Weapon::getDie()
{
    return die;
}
int Weapon::getDieMultiple()
{
    return dieMultiple;
}
int Weapon::getminCrit()
{
    return minCrit;
}
int Weapon::getCritMultiple()
{
    return critMultiple;
}
void Weapon::wield()
{
    equipped = true;
}
void Weapon::unwield()
{
    equipped = false;
}	
void Weapon::setSize(char sizechar)
{	//If a character is small, all weapons and armor most be small too
 size = sizechar;
}
char Weapon::getSize()
{
	return size;
}
bool Weapon::isEquipped()
{
	return equipped;
}
int Weapon::getRange()
{
	return range;
}

#endif
