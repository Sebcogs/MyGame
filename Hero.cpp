// v4
#ifndef HERO_CPP
#define HERO_CPP

#include<vector>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<iomanip>
#include <map>
//#include <unordered_map>
#include "Dice.h"
//#include "Actor.h"
#include "Hero.h"
//#include "charClass.h"
//#include "Race.h"
//#include "Ability.h"
//#include "loadfromDBtemplate.cpp"

using namespace std;
int extractIDs(vector<int>&, string);
int getWeaponFromDB(Weapon&, int); 
int getArmorFromDB(Armor&, int);
int getThrownFromDB(Thrown&, int);
int getAmmoFromDB(Consumable& ammo, int cmd);
int getPotionFromDB(Potion& potion, int cmd);
int getItemFromDB(Item& item, int cmd);
//template<class T>bool getFromDB(T& x, int cmd);
//bool getFromDB(Weapon& w, int cmd);
//bool getFromDB(Armor& a, int cmd);

ostream& operator<<(ostream& out, Hero stu)
{  
    out << stu.getName() << " " << stu.getHP()<< " " << stu.getMaxHP() << " ";
int x;
	for(x = STR; x <= CHA; ++x)
	{
	out <<stu.myAbilities.getStat(x) << " ";
	}
 out << stu.AC << " "<< stu.Lvl << " " << stu.Exp <<" "<< stu.Race::getRaceName() << " " << stu.myClass.getClassName() <<" "<< stu.inventory.getCopper() <<" "<< stu.inventory.getSilver() <<" "<<stu.inventory.getGold()  <<endl;  
	out << stu.inventory.getWeaponIDList()<< stu.inventory.getArmorIDList() << stu.inventory.getThrownIDList() << stu.inventory.getAmmoIDList() << stu.inventory.getPotionIDList() << stu.inventory.getItemIDList();
	
    return out;
}
istream& operator>>(istream& in, Hero& stu)
{
	int stat[6], cp, sp, gp;
	string classname, racename, weaponstream, armorstream, thrownstream, ammostream, potionstream, itemstream;

	in >> stu.Actor::actorName >> stu.Actor::HP >> stu.Actor::maxHP >> stat[0] >> stat[1] >> stat[2] >> stat[3] >> stat[4] >> stat[5] >> stu.AC >> stu.Lvl >> stu.Exp >> racename >> classname >> cp >> sp >> gp; 
	string blank;
	getline(in, blank);
	getline(in, weaponstream);
	getline(in, armorstream);
	getline(in, thrownstream);
	getline(in, ammostream);
	getline(in, potionstream);
getline(in, itemstream);
		vector<int>weaponIds;
		vector<int>armorIds;
		vector<int>thrownIds;
		vector<int>ammoIds;
		vector<int>potionIds;
		vector<int>itemIds;
		extractIDs(weaponIds, weaponstream);
		extractIDs(armorIds, armorstream);
		extractIDs(thrownIds, thrownstream);
		extractIDs(ammoIds, ammostream);
		extractIDs(potionIds, potionstream);
		extractIDs(itemIds, itemstream);
	Weapon aweapon;
	Armor aarmor;
	Item aitem;
	Thrown athrown;
	Consumable aAmmo;
	Potion aPotion;
	for(unsigned int count = 0; count < weaponIds.size(); ++count)
		{
		getWeaponFromDB(aweapon, weaponIds[count]); 
		stu.inventory.addWeapon(aweapon);
		}
	for(unsigned int count = 0; count < armorIds.size(); ++count)
		{
		getArmorFromDB(aarmor, armorIds[count]); 
		stu.inventory.addArmor(aarmor);
		}
	for(unsigned int count = 0; count < thrownIds.size(); count = count+2)
		{
		getThrownFromDB(athrown, thrownIds[count]); 
		athrown.setNumber(thrownIds[count+1]);
		stu.inventory.addThrown(athrown);
		}
for(unsigned int count = 0; count < ammoIds.size(); count = count+2)
		{
		getAmmoFromDB(aAmmo, ammoIds[count]); 
		aAmmo.setNumber(ammoIds[count+1]);
		stu.inventory.addAmmo(aAmmo);
		}
for(unsigned int count = 0; count < potionIds.size(); count = count+2)
		{
		getPotionFromDB(aPotion, potionIds[count]); 
		aPotion.setNumber(potionIds[count+1]);
		stu.inventory.addPotion(aPotion);
		}
	for(unsigned int count = 0; count < itemIds.size(); ++count)
		{
		getItemFromDB(aitem, itemIds[count]); 
		stu.inventory.addItem(aitem);
		}
	stu.Race::setFields(racename);
	stu.myClass.charClass::setFields(classname);
	

	cout <<"loading abilities/stats"<<endl;

	int x;
	for(x = STR; x <= CHA; ++x)
		{
	stu.myAbilities.setStat(x,stat[x]);
		}
	stu.setMod();
	stu.setAtk();
	stu.setSpeed();
	stu.inventory.loadMoney(cp, sp, gp);
    return in;
}
 
Hero::Hero() : Actor (), Race()
{
	Init = 0; 
	AC = 10;
   Lvl = 1;
   Exp = 0;
    Atk = 0;
	Dmg = 3;	//unarmed damage 1d3 for m, 1d2 for s
	Crit = false;
   int x;
    for(x = STR; x <= CHA; ++x)
    {
        myAbilities.setStat(x, 10); //default set to average value
        setMod(x);
    }
}
	
Hero::Hero(string name):Actor(name),Race()  //Hero constructor - Builds a new hero
{
	setFields();
}
void Hero::setName(string name)
{
	Actor::setName(name);
}
void	Hero::setFields()
{

	int x;
	for(x = STR; x <= CHA; ++x)
	{
		myAbilities.setStat(x);
		setMod(x);
		cout.width(5);
		cout << myAbilities.getStatName(x) <<"="<<myAbilities.getStat(x);
		cout << " mod:"<< setiosflags(ios::showpos)<< getMod(x)<< resetiosflags(ios::showpos)<<endl;
	}
	Crit = false;
   Init = 0; 
	AC = 10;
   Lvl = 1;
   Exp = 0;
	Dmg = 3;	//unarmed damage 1d3 for m, 1d2 for s
		Race::setFields();
	if(Race::getSize() == 's')
		Dmg = 2;
		myClass.setFields();
			//adjust Stat scores acording to race
	for(x = STR; x <= CHA; ++x)
	{
	int newStat=0;
	cout <<"Stat "<<myAbilities.getStatName(x)<< " was ";
	cout <<myAbilities.getStat(x)<<", adjusted to ";
		newStat = myAbilities.getStat(x)+ Race::getMod(x);
		if(newStat < 3) 
			newStat = 3;
		myAbilities.setStat(x, newStat);

	cout <<myAbilities.getStat(x)<<" with mod:"<<setiosflags(ios::showpos);
	cout<< getMod(x) <<resetiosflags(ios::showpos)<< endl;
	}
			//Set HP according to class hitDice and CON mod
	updateHP();	
	setAtk();
	setSpeed();

}
void Hero::setAtk()
{
	Atk = myClass.getAtk();
}
int Hero::getAtk()
{
    return Atk;
}
void Hero::outputStats()
{
cout<<"Stats are: "<<endl;
	int x;
	for(x = STR; x <= CHA; ++x)
	{
	cout.width(7);
	cout <<myAbilities.getStatName(x)<<" = "<<myAbilities.getStat(x)<<" with mod:"<<setiosflags(ios::showpos)<< getMod(x) <<resetiosflags(ios::showpos)<<endl;
	}
}
int Hero::getStat(int stat)
{
  return  myAbilities.getStat(stat);
}
void Hero::outputData()
{
   	Actor::outputData();
    Race::outputData(); 
    myClass.outputData();
if(getRaceName() == "Halfling")
	cout << "Halflings add a bonus +1 to all saving throws"<<endl;
  	cout <<"Level: "<<Lvl<<", AC: " <<getAC()<< " , exp: "<<Exp <<", "<<endl;

	outputStats();
   
	inventory.whatsEquipped();
	inventory.showList();
	inventory.showMoney();
	long lightweight;
 	if(Race::getSize() == 's')
		lightweight = 0.75*myAbilities.carryMaxLight();
	else
		lightweight = myAbilities.carryMaxLight();
	cout <<"You are carrying a total of "<<inventory.getTotalWeight();
	cout <<" lb. Max light carrying capacity is " << lightweight << endl;
	cout <<endl;
	
	
}
void Hero::setExp(int exp)
{
	Exp = getExp() + exp;
	cout<< "You now have "<< Exp <<" exp points."<<endl;
	long needed = getExpForNext();
	if(Exp >= needed)
		levelUp();
	cout << " You need a total of" << getExpForNext();
	cout << " exp pts for next level, " << getExpForNext() - Exp;
	cout <<"pts more to level up"<<endl;
}
long Hero::getExp()
{
    return Exp;
}
void Hero::levelUp()
{		//increase level, check for ability score increase, charClass levelUp (atk and savethrow increase), what else?...
    Lvl+=1;
    cout<<"Congrates! you are now Level "<<Lvl<<endl;


	myAbilities.levelUp(Lvl);
	setMod();
	
			//set new HP by a roll of Hit Dice , CON mod and old HP
	updateHP();

	cout<<"enter Class level up to level "<<Lvl<<endl;
	myClass.levelUp(Lvl);
	Atk = myClass.getAtk();

}
int Hero::getLevel()
{
    return Lvl;
}


void Hero::setMod(int stat)  //Stats stat)
{
   statMod[stat] = -5;

	int count = 1;
	while(count <= myAbilities.getStat(stat)) //statScore[stat])
   {
   
   statMod[stat]+=1;
   count+=2;
   if(Lvl == 0 && count >= 25)
      {break;}
   }
  //cout<<"Ability "<<getStatName(stat)<<": "<<getStat(stat)<<", has mod: "<< setiosflags( ios::showpos) << statMod[stat]<<resetiosflags(ios::showpos)<<endl;
}

void Hero::setMod()
{

	int x;
	for(x = STR; x <= CHA; ++x)
	{
		setMod(x);
		cout << myAbilities.getStatName(x)<<" = "<<myAbilities.getStat(x)<<" and mod:"<< setiosflags(ios::showpos)<< getMod(x)<< resetiosflags(ios::showpos)<<endl;
	}
}

//USE enum easy naming
int Hero::getMod(int stat) //Stats stat)
{
    return statMod[stat];
}

long Hero::getExpForNext()
{
	long points, levelSum = 0;
	for(int count = 1; count <=getLevel(); count++)
		levelSum = levelSum + count;
	points = expLvlIncrement * levelSum;

	return points;
}

void Hero::updateHP()
{
	int newHP, oldHP, newHitRoll, HD;
	HD = myClass.getHitDice();
	
	if(Lvl == 1)  //for 1dst level, don't roll dice.
	{
	newHitRoll =  HD;
	oldHP = 0;
	}
	else
	{
	srand( time(0) );
	Dice diceHitD(1, HD);
	newHitRoll = diceHitD.getValue();
		if(newHitRoll < 1)
			newHitRoll = 1;
	oldHP = Actor::getHP();
	}
	newHP = newHitRoll + getMod(CON) + oldHP;
	Actor::setHP(newHP);
cout <<"HP is "<< newHitRoll <<" Hit dice roll, plus " <<getMod(CON)<<" from CON mod and oldHP "<< oldHP << " = "<<Actor::getHP()<< endl;
}
int Hero::getAC()
{
	int armMod = 0; //myArmor.getACmod();
	int shieldMod = 0; // myShield.getACmod();
	int ac;
	int dexMod = getMod(DEX);
	int sizeMod = Race::getsizeMod();
	bool hasBody = inventory.myEquip.hasBody();
	bool isShield = inventory.myEquip.getIsShield();
	//
	
			if(hasBody)	
				{
			int armorPos = inventory.myEquip.getBodyPosition();
			armMod = inventory.armor[armorPos].getACmod();
			int maxdex= inventory.armor[armorPos].getMaxDex();
			if(dexMod> maxdex )
				dexMod = maxdex;
				}

	if(isShield)
	{
int	shieldPos = inventory.myEquip.getOffHandPosition();
	shieldMod = inventory.armor[shieldPos].getACmod();
	}
	//	}

	ac = AC + dexMod + sizeMod + armMod + shieldMod;
		cout<<" AC is: "<< ac <<" base AC "<<AC<<" + "<<dexMod<<" DEX mod + "<<sizeMod<< " size mod + "<<armMod<<" armor Mod + "<<shieldMod<<" shield Mod."<<endl;


	return ac;
}
bool Hero::aliveOrDead()
{
	return Actor::aliveOrDead();
}
int Hero::meleeRoll()
{	
	srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue();
	int atkroll = roll + Atk + getMod(STR) + Race::getsizeMod();
	int mincrit=20;  //usually perfect 20 roll is critical, check weapon for min crit value
	//for(unsigned count =0; count < inventory.weapons.size(); count++)
		//{

int weaponPos = inventory.myEquip.getHandPosition();
		if(weaponPos > -1)
			{
			cout <<"Using weapon :"<< inventory.weapons[weaponPos].Item::getName() << endl;
			mincrit = inventory.weapons[weaponPos].getminCrit();
		}
	if(roll>=mincrit)  //is this here in attack or in damage rolls? here I think
		{
		Crit = true;
		cout<<"CRITICAL HIT!!" <<endl;
		}
		
		cout << "  Melee hit roll of "<<roll << " plus base Atk bonus "<<Atk<<" + "<<getMod(STR)<<" STR mod + "<<Race::getsizeMod()<<" size mod"<<endl;
	cout << "Total melee hit roll of "<<atkroll;
	return atkroll;
}
int Hero::rangeRoll()
{	
	srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue();
int mincrit=20;  //usually perfect 20 roll is critical, check weapon for min crit value
	for(unsigned count =0; count < inventory.weapons.size(); count++)
		{
		if(inventory.weapons[count].isEquipped() )
			{
			cout <<"Using weapon :"<< inventory.weapons[count].Item::getName() << endl;
			mincrit = inventory.weapons[count].getminCrit();
			}
		}
	if(roll>=mincrit)  //is this here in attack or in damage rolls? here I think
		{
		Crit = true;
		cout<<"CRITICAL HIT!!" <<endl;
		}
	int atkroll = roll + Atk + getMod(DEX) + Race::getsizeMod();
		cout << "  Range hit roll of "<<roll << " plus base Atk bonus "<<Atk<<" + "<<getMod(DEX)<<" DEX mod + "<<Race::getsizeMod()<<" size mod"<<endl;
	return atkroll;
}
int Hero::getInit()
{
	return Init+getMod(DEX);
}
void Hero::outputShortData()
{
  	cout << "Hero named "<<Actor::getName() <<" with HP:"<<Actor::getHP();
    cout <<", "<<Race::getRaceName() << " " <<myClass.getClassName(); 
	cout <<" Level: "<<Lvl<< " , exp: "<<Exp;
      	
    cout<<endl;
  
}
string Hero::getDmgDie()
{
	string temp = "Damage roll ";
	int mult =1, die = Dmg, range;

int weaponPos = inventory.myEquip.getHandPosition();
bool hasHand = inventory.myEquip.hasHand();
if(hasHand)
			{
		string name = inventory.weapons[weaponPos].Item::getName();
				temp = temp +"using weapon : "+ name+ " is ";
				mult = inventory.weapons[weaponPos].getDieMultiple();
				die = inventory.weapons[weaponPos].getDie();
				range = inventory.weapons[weaponPos].getRange();
				
			}
		else
			{
				temp+="unarmed is ";
				Dmg = 3;	//unarmed damage 1d3 for m, 1d2 for s
			if(Race::getSize() == 's')
				Dmg = 2;
			die = Dmg;
			}
	
		temp = temp + to_string(mult) +"d" + to_string(die);
		Dmg = die;
		if(range > 1)
			temp = temp + " with range " + to_string(range);

	return temp;
}
int Hero::getDmgRoll()
{
	srand( time(0)+1);
	int mult = 1, critDmg = 2;
bool hasHand = inventory.myEquip.hasHand();
bool has2Hand = inventory.myEquip.has2Hand();
bool range = inventory.myEquip.hasRange();
int weaponPos = inventory.myEquip.getHandPosition();
int weapon2handPos = inventory.myEquip.get2HandPosition();
int roll;  //damage roll result
	if(hasHand)
		{
	mult = inventory.weapons[weaponPos].getDieMultiple();
			critDmg = inventory.weapons[weaponPos].getCritMultiple();
			Dmg = inventory.weapons[weaponPos].getDie();
		}

	Dice dice(mult,Dmg);
	if(!range)  //melee damage includes str mod
	{
	roll = dice.getValue() + getMod(STR);
	cout <<"Damage roll of "<<dice.getValue()<<" + Str Mod of "<<getMod(STR)<<endl;
		if(has2Hand)
		{
			if(weaponPos == weapon2handPos)
			{
		int twohandStrMod = getMod(STR)+ 0.5*getMod(STR);
			cout <<"2handed have 1 1/2xSTR mod of : "<<getMod(STR)+ 0.5*getMod(STR);
			cout <<" but rounds to actually gives mod of: "<<twohandStrMod<<endl;
		roll = roll + 0.5*getMod(STR);
			}
			else
				{
			cout <<"     !!!Error."<<endl;
			cout <<"  2 handed weapon has different position number in main and off hand !!!! "<<endl;
				}
		}
	}
	else if(range)  //Range damage includes str penalty
	{
	roll = dice.getValue();
		int strMod = getMod(STR);
		if(strMod>0)
			strMod = 0;
		cout <<"Damage roll of "<<roll<<" -" <<strMod<< " Str penalty"<<endl;
		roll = roll + strMod;
	}
	else
		cout <<"    !!!Error! Damage can't determine if ranged or not"<<endl;

		if(Crit)
		{
		cout <<"Critical deals x"<< critDmg<<" damage"<<endl;
		roll = roll *critDmg;
		Crit = false;  //return critical hit to normal after damage
		}
		cout <<"You deal "<<roll<<" damage!" <<endl;
	return roll;
}
string Hero::basicInfo()
{
  string level = to_string(getLevel());
    string temp = Actor::getName() + " (" +Race::getRaceName() + " Level: ";
	temp= temp+ level +" "+myClass.getClassName() + ") ";
	return temp;
}
int Hero::getSaveThrow(int save)
{
	int saveThrow = myClass.getSaveThrow(save);
		if(getRaceName() == "Halfling")
			{
			cout <<endl<<"Halflings have saving throw bonus:";
			saveThrow++;
			}
   	return saveThrow;
}
string Hero::getSaveName(int save)
{
	return myClass.getSaveName(save);
}
string Hero::getStatName(int stat)
{
	return myAbilities.getStatName(stat);
}	
void Hero::setSpeed()
{
	string race = getRaceName();
	string classname = myClass.getClassName();
	if(race == "Halfling") // || race == "Gnome")
		{
		Actor::setSpeed(4,3);
		}
	else if(race == "Dwarf")
		{
		Actor::setSpeed(4,4);
		}
	if(classname == "Barbarian")
		{
		int speed1 = getSpeed();
		int speed2 = getSpeedSlow();
		Actor::setSpeed(speed1+2, speed2+2);
		}
	
}
int Hero::getMaxLightWeight()
{
	long lightweight;
 	if(Race::getSize() == 's')
		lightweight = 0.75*myAbilities.carryMaxLight();
	else
		lightweight = myAbilities.carryMaxLight();

	return lightweight;
}
int Hero::getCurrentSpeed()
{
	int maxLight = getMaxLightWeight();
	int currentWeight = inventory.getTotalWeight();
	if(currentWeight > maxLight)
		return getSpeedSlow();
	else
		return getSpeed();
}
#endif


