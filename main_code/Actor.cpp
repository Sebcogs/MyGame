#ifndef ACTOR_CPP
#define ACTOR_CPP
//v4
#include<iostream>
#include<string>
//#include "Dice.h"
#include "Actor.h"
using namespace std;

Actor::Actor()
{
	maxHP = 1;	
	setName("Temp_Name");
	alive = true;
   setHP(1);
}
Actor::Actor(string name )  //Basic Constructor
{
	maxHP=1;  
	setName(name);
   alive = true;
   setHP(1);
}

/* Actor::~Actor()
{
	//delete actorName;
	//delete alive;
	//delete HP;
	//delete maxHP;
} */

void Actor::setName(string Name)
{
   actorName = Name;
}

string Actor::getName()
{
    return actorName;
}
void Actor::setHP()
{
   
     maxHP=1;
   // Dice dice2d6(2,6);     
//int value = dice2d6.getValue();
  // setHP(value);
   
    setHP(4);
}

void Actor::setHP(int HPvalue)
{
    HP = HPvalue;
    if(maxHP< HPvalue)
       { maxHP = HPvalue;
        cout<<"New max HP set to : "<<maxHP<<endl;
        }
    if(HP<=0)
        {
        HP = 0;
    //alive = false;
	condition.setCondition(4096);  //unconscious
	cout <<" - - "<<getName()<<" is dying! - - "<<endl;
        }
		if(HP<=-10)
		{
			alive = false;
			cout <<" - - "<<getName()<<" HAS DIED! - - "<<endl;
		}
}

int Actor::getHP()
{
	//cout<<"in getHP() = "<<HP<<endl;
    return HP;
}

int Actor::getMaxHP()
{
	//cout<<"in getMaxHP() = "<<maxHP<<endl;
    return maxHP;
}

bool Actor::aliveOrDead()
{
    if(HP<=0)
    alive = 0;
    return alive;
}
void Actor::outputData()
{
	//cout <<"Actor outputData"<<endl;
	//cout <<"Alive = "<<alive<<endl;
string status;
    if (alive)
    status="Alive";
    else
    status="Dead";

 cout <<endl<<endl<< "Actors " << actorName << " with HP: " << HP << " out of " << maxHP ;
    cout<< " Is currently "<<status<<" and "<<condition.getStatus()<<endl;
}
void Actor::revive()
{
	alive = true;
	condition.setCondition(0);
}
void Actor::receiveDamage(int dmg)
{
	int newHP, oldHP;
	
	if(aliveOrDead()) 
		{
		cout <<"You are damage for " <<dmg<< " HP."<<endl;
		oldHP = getHP();
		newHP = oldHP - dmg;
		setHP(newHP);
		cout <<"HP was "<<oldHP<<" and is now "<<newHP<<endl;			
		}
	else
		cout << getName()<< "You are already dead!"<<endl;
}
void Actor::receiveHealing(int heal)
{
	//cout<<"In receiveHealing("<<heal<<")"<<endl;
	int newHP, oldHP, max;
	
	oldHP = getHP();
	max = getMaxHP();
	cout <<"Your current HP of "<<oldHP <<" and are healed for " << heal<<endl;
	newHP = oldHP + heal;
	if(oldHP <=0 && newHP >=0)
		revive();
	if(newHP <= max)
		setHP(newHP);
	else
	setHP(max);

	cout << "Your HP is now "<<getHP()<<endl;
}
int Actor::getSpeed()
{
	int value = speed+condition.getSpeedMod();
	if(value < 0)
		value =0;
	return value;
}
int Actor::getSpeedSlow()
{
	int value = slowspeed+condition.getSpeedMod();
	if(value < 0)
		value =0;
	return value;
}
void Actor::setSpeed(int fast, int slow)
{
	speed = fast;
	slowspeed = slow;
}
int Actor::getSaveThrow(Saves save)
{
	int savemod = condition.getSaveMod();
	aSavethrow.updateTempBonus(savemod, savemod, savemod );
	return aSavethrow.getSaveThrow(save);
}
int Actor::getSaveThrow(Saves save, specialType special)
{
	int savemod = condition.getSaveMod();
	aSavethrow.updateTempBonus(savemod, savemod, savemod );
	return aSavethrow.getSaveThrow(save, special);
}
#endif


