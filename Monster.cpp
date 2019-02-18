//v4
#ifndef MONSTER_CPP
#define MONSTER_CPP

#include<iostream>
#include<string>
#include<iomanip>
#include "Dice.h"
#include "Actor.h"
#include "Monster.h"
using namespace std;

ostream& operator<<(ostream& out, Monster stu)
{
	//idNum, name, HP, cr, init, ac, atk, dmgDie, dmgMult, dmgAdjust, sizechar, 1, numdie
    out << stu.Id << " " << stu.getName() << " " << stu.getHP() <<" " << stu.getCR()<<" "<<stu.Init <<" "<<stu.AC<<" "<<stu.Atk<<" "<<stu.DmgDie<<" " <<stu.DmgMult<<" "<<stu.DmgAdjust<<" "<<stu.size<<" "<<"1"<<" "<<stu.numDie<<endl;
      
    return out;
}
istream& operator>>(istream& in, Monster& stu)
{
int idNum;
string name;
double cr;
int HP, init, ac, atk, dmgDie, dmgMult, dmgAdjust, numdie;
char sizechar;
bool melee;
	//cout<<"Reading input"<<endl;
    in >> idNum >> name >> HP >> cr >>  init >>ac >> atk >> dmgDie >> dmgMult >>dmgAdjust >> sizechar >>melee >> numdie;

//Monster aMonster(name, cr);
stu.setFields(idNum, name, HP, cr, init, ac, atk, dmgDie, dmgMult, dmgAdjust, sizechar, melee, numdie);
    return in;
}

Monster::Monster(string name, double cr):Actor(name)
{ 
	Id = 0;   
	AC = 10;
    Exp = 300*cr;
   CR = cr;
	size = 'm';
     srand( time(0)+cr );
   Dice dice4d6(4,6);   
   Exp = (cr+1) * dice4d6.getValue();
	Init = 0;
	Atk = 0;
	DmgDie = 4;
	DmgMult = 1;
	DmgAdjust = 0;
	Melee = true;
	numDie = 1;
}

Monster::Monster():Actor()
{
		Id = 0;   
	AC = 10;
    Exp = 0;
   CR = 0;
	size = 'm';
     srand( time(0) );
   Dice dice4d6(4,6);   
   //Exp = (CR+1) * dice4d6.getValue();
	Init = 0;
	Atk = 0;
	DmgDie = 4;
	DmgMult = 1;
	DmgAdjust = 0;
	Melee = true;
	numDie = 1;
}
	
void Monster::setFields(int id, string name, int HP, double cr, int init, int ac, int atk, int dmgDie, int dmgMult, int dmgAdjust, char sizechar, bool melee = true, int numdie = 1)
{
	Id = id;	
	Actor::setName(name);   //most use ::
	Actor::maxHP=HP; 
	Actor::setHP(HP);
	Actor::alive = true;
	CR = cr;
	Init = init;
	AC = ac;
	Atk = atk;
	DmgDie = dmgDie;
	DmgMult = dmgMult;
	DmgAdjust = dmgAdjust;
	size = sizechar;
	Melee = melee;
	numDie = numdie;
	Exp = 300*CR;
	
}
string Monster::getName()
{
	return Actor::getName();
}
void Monster::outputData()
{
	cout<<"output data";
   Actor::outputData();
   cout <<"CR: "<<CR<<", AC: " <<AC<<", will give "<<Exp<<" experience pts"<<" Has Atk bonus of "<<Atk<< "and damage of "<<DmgMult<<"d"<<DmgDie<< setiosflags(ios::showpos)<< DmgAdjust <<resetiosflags(ios::showpos)<<endl;
}
void Monster::display()
{
	outputData();
}
int Monster::giveExp()
{
    return Exp;
}

double Monster::getCR()
{   
    return CR;
}
int Monster::getInit()
{
	return Init;
}
int Monster::getDmgRoll()
{
//	  srand( time(0) );
	Dice dice(DmgMult, DmgDie);
	int damage = dice.getValue() + DmgAdjust;
	if(damage <1)
		damage = 1;
	return damage;
}
void Monster::receiveDamage(int dmg)
{
	int newHP, oldHP;
	
	if(Actor::aliveOrDead()) 
		{
		cout <<"You damage "<<getName() << "for "<<dmg<< " HP."<<endl;
		oldHP = Actor::getHP();
		newHP = oldHP - dmg;
		Actor::setHP(newHP);
		cout <<"HP was "<<oldHP<<" and is now "<<newHP<<endl;
		}
	else
		cout << getName() << "Was already dead!"<<endl;
}
void Monster::receiveHealing(int heal)
{
	int newHP, oldHP, max;
	oldHP = Actor::getHP();
	max = Actor::getMaxHP();
	newHP = oldHP + heal;
	if(newHP <= max)
	Actor::setHP(newHP);
	else
	Actor::setHP(max);
}
int Monster::getAC()
{
	return AC;		//includes size mod etc
}
bool Monster::aliveOrDead()
{
	if(!Actor::aliveOrDead())
		setSpeed(1,1);
	return Actor::aliveOrDead();
}
int Monster::sizeMod()
{
	int mod;
	if(size == 's')
		mod = 1;
	if(size == 'l')
		mod = -1;
	if(size == 't')
		mod = 2;
	else
		mod = 0;
	return mod;
}
int Monster::meleeRoll()
{	
//	srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue() + Atk; // + sizeMod(); Atk includes size mod etc
		cout << "  Monster hit roll of "<<roll << " includes base Atk bonus "<<Atk-sizeMod()<<" + "<<sizeMod()<<" size mod"<<endl;
	return roll;
}

#endif
