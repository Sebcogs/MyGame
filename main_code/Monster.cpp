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
	//idNum, name, HP, cr, init, ac, atk, dmgDie, dmgMult, dmgAdjust, sizechar, 1, numdie, HD, saveF, saveR, saveW, type, touch, speed
    out << stu.Id << " " << stu.getName() << " " << stu.getHP() <<" " << stu.getCR()<<" "<<stu.init;
    out <<" "<<stu.AC<<" "<<stu.Atk<<" "<<stu.DmgDie<<" " <<stu.DmgMult<<" "<<stu.DmgAdjust<<" "<<stu.size<<" "<<"1"<<" "<<stu.numDie;
    out <<" "<<stu.hitDie<<" " << stu.aSavethrow.getSaveThrow(FORT)<<" " <<stu.aSavethrow.getSaveThrow(REF) <<" " <<stu.aSavethrow.getSaveThrow(WIL)<<" "<<stu.mType<< " " <<stu.touch<<" " <<stu.getSpeed()<<endl;
      
    return out;
}
istream& operator>>(istream& in, Monster& stu)
{
int idNum;
string name, specialname;
double cr;
int HP, init, ac, atk, dmgDie, dmgMult, dmgAdjust, numdie;
char sizechar;
bool melee;
float hd;
int saveF, saveR, saveW, monsterTy, touch, speed;
int DC, specialatk, specialdur, freq;
//Saves specialSave;
int specialsave;

	//cout<<"Reading input"<<endl;
    in >> idNum >> name >> HP >> cr >>  init >>ac >> atk >> dmgDie >> dmgMult >>dmgAdjust >> sizechar >>melee >> numdie;
    in >> hd >> saveF  >> saveR >> saveW >> monsterTy >> touch >> speed;
    //special atk input
    in>> specialname >> DC >> specialsave >> specialatk >> specialdur >> freq;
//Monster aMonster(name, cr);
stu.setFields(idNum, name, HP, cr, init, ac, atk, dmgDie, dmgMult, dmgAdjust, sizechar, melee, numdie);
stu.special.setFields(specialname, DC, stu.intToSave(specialsave), specialatk, specialdur, freq); 
   stu.hitDie = hd;
stu.aSavethrow.setFields(saveF, saveR, saveW);
	/*stu.saveThrow[0] = saveF;
    stu.saveThrow[1] = saveR;
    stu.saveThrow[2] = saveW; */
    stu.mType = stu.intToType(monsterTy);
    stu.touch = touch;
    stu.setSpeed(speed, speed);
 
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
	init = 0;
	Atk = 0;
	DmgDie = 4;
	DmgMult = 1;
	DmgAdjust = 0;
	Melee = true;
	numDie = 1;
    //setmap();
}

Monster::Monster():Actor()
{
		Id = 0;   
	AC = 10;
    touch = 10;
    Exp = 0;
   CR = 0;
	size = 'm';
     srand( time(0) );
   Dice dice4d6(4,6);   
   //Exp = (CR+1) * dice4d6.getValue();
	init = 0;
	Atk = 0;
	DmgDie = 4;
	DmgMult = 1;
	DmgAdjust = 0;
	Melee = true;
	numDie = 1;
    //setmap();
}
/*	
void Monster::setmap()
{
    saves[FORT] = "Fort";
	saves[REF] = "Reflex";
	saves[WIL] = "Will";
    	map<Saves, string>::iterator it = saves.begin();
	while(it != saves.end())  //set up savingthrow names
		{
		saveThrowName[it->first] = it->second;
		it++;
		}
} */
void Monster::setFields(int id, string name, int HP, double cr, int in, int ac, int atk, int dmgDie, int dmgMult, int dmgAdjust, char sizechar, bool melee = true, int numdie = 1)
{
	Id = id;	
	Actor::setName(name);   //most use ::
	Actor::maxHP=HP; 
	Actor::setHP(HP);
	Actor::alive = true;
	CR = cr;
	init = in;
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
/*string Monster::getName()
{
	return Actor::getName();
}*/
void Monster::outputData()
{
	cout<<"----output Monster data----";
   Actor::outputData();
   cout <<"CR: "<<CR<<", AC: " <<AC<<", will give "<<Exp<<" experience pts,"<<" has Atk bonus of "<<Atk<< " and damage of "<<DmgMult<<"d"<<DmgDie<< setiosflags(ios::showpos)<< DmgAdjust <<resetiosflags(ios::showpos)<<endl;
    if(special.getSpecialName() != "None")
        cout << "Has " << special.getSpecialName() <<" attack also!"<<endl;
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
	return init;
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
    int atkToUse = Atk;
    if(atkIsSpecial)
        atkToUse = special.getAtk();
//	srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue() + atkToUse; // + sizeMod(); Atk includes size mod etc
		cout << "  Monster hit roll of "<<roll << " includes base Atk bonus "<<atkToUse-sizeMod()<<" + "<<sizeMod()<<" size mod"<<endl;
	return roll;
}
int Monster::getTouchAC()
{
    return touch;
}
/*
int Monster::getSaveThrow(int saves)
{
	if(saves >= 0 || saves <= WIL) //Saves::WIL)
   		 return saveThrow[saves];
	else {
    	cout <<"can't get SavingThrow value, out of range.  Must be: ";
		//cout << Saves::FORT << ", " << Saves::REF;
		//cout <<" and " << Saves::WIL <<endl;
   	 return 0;
		}
}
int Monster::getSaveThrow(Saves save)
{
   return saveThrow[save]; 
} */
monsterType Monster::intToType(int i)
	{
        //enum monsterType {ANIMAL = 0, VERMIN, UNDEAD, GOBLIN, GIANT, HUMANOID};
		monsterType i_Enum;
		switch (i){
		case 0:
			i_Enum = ANIMAL;
			break;
		case 1:
			i_Enum = VERMIN;
			break;
		case 2:
			i_Enum = UNDEAD;
			break;
		case 3:
			i_Enum = GOBLIN;
            break;
        case 4:
            i_Enum = GIANT;
            break;
        case 5:
            i_Enum = HUMANOID;
            break;
        case 6:
            i_Enum = ORC;
            break;
        case 7:
            i_Enum = KOBOLD;
            break;
        case 8:
            i_Enum = CONSTRUCT;
        default:
            i_Enum = HUMANOID;
		}
	return i_Enum;
	}
monsterType Monster::getType()
{
    return mType;
}
Saves Monster::intToSave(int i)
{   //{FORT=0, REF, WIL, NONE}
    		Saves i_Enum;
		switch (i){
		case 0:
			i_Enum = FORT;
			break;
		case 1:
			i_Enum = REF;
			break;
		case 2:
			i_Enum = WIL;
			break;
		case 3:
			i_Enum = NONE;
            break;
        default:
            i_Enum = NONE;
        }
    return i_Enum;
}
bool Monster::useSpecial()
{
    bool useSpecial = false;
    
    if(special.getSpecialName() != "None")
    {
        int freq = special.getFreq();
        if(freq == 0)
            useSpecial = true;
        else if(freq == 1 && firstAtk == true)
        {
            cout<<"OhNo, it uses it's special attack for its 1st attack!"<<endl;
            useSpecial = true;
        }
        else if(freq == 2)
        {
            Dice dice(1,4); //random 1 in 4 chance
            if(dice.getValue() <= 1)
            {
                useSpecial = true;
                cout<<"OhNo, it uses it's special attack!"<<endl;
            }
        }
       // else
        //    cout<<"Error in Monster check useSpecial.  What is the other case??"<<endl;
    }     
        firstAtk = false;
        atkIsSpecial = useSpecial;
    return useSpecial;
            
}
int Monster::getEffectCode()
{
    return special.getEffectCode();
}
int Monster::getDuration()
{
    return special.getDuration();
}
Saves Monster::getSpecialSaveType()
{
    return special.getSaveType();
}
int Monster::getSpecialDC()
{
    return special.getDC();
}
specialType Monster::getSpecialType()
{
    return special.getType();
}
bool Monster::useSpecialDmg()
{
    return special.getIncludeDmg();
}
float Monster::getHitDice()
{
	return hitDie;
}
#endif
