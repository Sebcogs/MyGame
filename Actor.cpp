#ifndef ACTOR_CPP
#define ACTOR_CPP
//v4
#include<iostream>
#include<string>
#include "Dice.h"
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
    alive = false;
	cout <<" - - "<<getName()<<" HAS DIED! - - "<<endl;
        }
}

int Actor::getHP()
{
    return HP;
}

int Actor::getMaxHP()
{
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
    cout<< " Is currently "<<status<<endl;
}
void Actor::revive()
{
	alive = true;
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
	int newHP, oldHP, max;
	oldHP = getHP();
	max = getMaxHP();
	cout <<"Your current HP of "<<oldHP <<" and are healed for " << heal<<endl;
	newHP = oldHP + heal;
	if(oldHP <=0 && newHP >=0)
		revive();
	else if(newHP <= max)
		setHP(newHP);
	else
	setHP(max);

	cout << "Your HP is now "<<getHP()<<endl;
}
int Actor::getSpeed()
{
	return speed;
}
int Actor::getSpeedSlow()
{
	return slowspeed;
}
void Actor::setSpeed(int fast, int slow)
{
	speed = fast;
	slowspeed = slow;
}
#endif


