#ifndef EQUIP_CPP
#define EQUIP_CPP
//v4
#include<iostream>
#include<string>
#include "Equip.h"

using namespace std;

Equip::Equip()
{
	body = EMPTY;
	hand = EMPTY;
	offhand = EMPTY;
	twohand = EMPTY;
	isShield = false;
	isRange = false;
	
}

bool Equip::setBody(int armorID)
{
	bool set = false;
if(armorID == EMPTY)
	{
	body = EMPTY;
	}
else
	{
	if(hasBody())
		{
	cout <<"Armor is already equipped, need to unequip first"<<endl;
		}
	else
		{
	body = armorID;
	set = true;
		}
	}
	return set;
}
bool Equip::setHand(int WeaponID)
{
	bool set = false;
if(WeaponID == EMPTY)
	{
	hand = EMPTY;
	}
else
	{
	if(hasHand())
		{
	cout <<"A weapon is already equipped, need to unequip first"<<endl;
		}
	else
		{
	hand = WeaponID;
	set = true;
		}
	}
	return set;
}
bool Equip::setOffHand(int ID, bool shield) //ie (weaponID, false) or (armorID, true)
{
	bool set = false;
if(ID == EMPTY)
	{
		offhand = EMPTY;
		isShield = false;
	}
else
	{
	if(hasOffHand())  //use 0 to unequip
		{
	cout << "Something is in the off hand already"<<endl;
		}
	else
		{
		if(has2Hand())
			{
			cout <<"Why is offhand empty but 2hand is not??"<<endl;	
			}
		else
			{
	isShield = shield;
	offhand = ID;
	set = true;
			}
		}
	
	}
	return set;
}
bool Equip::set2Hand(int weaponID)
{
	bool set = false;
if(weaponID == EMPTY)
	{
	hand = EMPTY;
	offhand = EMPTY;
	twohand = EMPTY;
	isShield = false;
	}
else
	{
	if(has2Hand())
		{
	cout <<"A 2-handed weapon is already equipped, need to unequip first"<<endl;
		}
	else
		{

		if(hasOffHand())
			{	
		cout <<"Equip a 2  handed weapon, must unequip any shield or off hand weapon first"<<endl<<"Not equipped!"<<endl;
			}
		else
			{
		twohand = weaponID;
		hand = weaponID;
		offhand = weaponID;
		isShield = false;
		set = true;
			}
		}
	}
	return set;
}	
int Equip::getBodyPosition()
{
	return body;
}
int Equip::getHandPosition()
{
	return hand;
}
int Equip::getOffHandPosition()
{
	return offhand;
}
int Equip::get2HandPosition()
{
	return twohand;
}
bool Equip::getIsShield()
{
	return isShield;
}
bool Equip::hasBody()
{
	bool a =false;	
	if(body !=EMPTY)
		a = true;
	return a;
}
bool Equip::hasHand()
{
	bool a =false;	
	if(hand !=EMPTY)
		a = true;
	return a;
}
bool Equip::has2Hand()
{
	bool a =false;	
	if(twohand !=EMPTY)
		a = true;
	return a;
}
bool Equip::hasOffHand()
{
	bool a =false;	
	if(offhand !=EMPTY)
		a = true;
	return a;
}
void Equip::setRange(bool ranged)
{
	if(ranged)
		{
		isRange = true;
		//cout <<"Equipped is ranged"<<endl;
		}
	else if(!ranged)
		isRange = false;
	else
		cout <<"Error!  Equip setRange error"<<endl;
}

bool Equip::hasRange()
{
	return isRange;
}

#endif

