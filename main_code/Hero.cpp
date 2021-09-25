// v4
#ifndef HERO_CPP
#define HERO_CPP

#include<vector>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
//#include <map>
//#include <unordered_map>
#include "Dice.h"
//#include "Actor.h"
#include "Hero.h"
//#include "charClass.h"
//#include "Race.h"
//#include "Ability.h"
#include "loadfromDBtemplate.cpp"

using namespace std;
int extractIDs(vector<int>&, string);

/*
int getWeaponFromDB(Weapon&, int); 
int getArmorFromDB(Armor&, int);
int getThrownFromDB(Thrown&, int);
int getAmmoFromDB(Consumable& ammo, int cmd);
int getPotionFromDB(Potion& potion, int cmd);
int getItemFromDB(Item& item, int cmd);  
bool getSpellFromDB(Spell& spell, int cmd);
//template<class T>bool getFromDB(T& x, int cmd);
//bool getFromDB(Weapon& w, int cmd);
//bool getFromDB(Armor& a, int cmd);
*/
/*
ostream& operator<<(ostream& out, Hero stu)
{  
    //out << stu.getName() << " " << stu.getHP()<< " " << stu.getMaxHP() << " ";
    out << stu.actorName << " " << stu.HP<< " " << stu.maxHP << " ";
int x;
	for(x = STR; x <= CHA; ++x)
	{
	out <<stu.myAbilities.getStat(x) << " ";
    
	}
 out << stu.AC << " "<< stu.Lvl << " " << stu.Exp <<" "<< stu.myRace->getRaceName() << " " << stu.myClass->getClassName();
 out<<" "<< stu.inventory.getCopper() <<" "<< stu.inventory.getSilver() <<" "<<stu.inventory.getGold()  <<endl;  
	out << stu.inventory.getWeaponIDList()<< stu.inventory.getArmorIDList() << stu.inventory.getThrownIDList();
out << stu.inventory.getAmmoIDList() << stu.inventory.getPotionIDList() << stu.inventory.getItemIDList();
	out << stu.getSpellList();

    return out;
} */        //Using above calls destructor after save function
istream& operator>>(istream& in, Hero& stu)
{
	int stat[6], cp, sp, gp;
	string classname, racename, weaponstream, armorstream, thrownstream, ammostream, potionstream, itemstream, spellstream;

	in >> stu.Actor::actorName >> stu.Actor::HP >> stu.Actor::maxHP >> stat[0] >> stat[1] >> stat[2] >> stat[3];
	in >> stat[4] >> stat[5] >> stu.AC >> stu.Lvl >> stu.Exp >> racename >> classname >> cp >> sp >> gp; 
	string blank;
	getline(in, blank);
	getline(in, weaponstream);
	getline(in, armorstream);
	getline(in, thrownstream);
	getline(in, ammostream);
	getline(in, potionstream);
	getline(in, itemstream);
getline(in, spellstream);
		vector<int>weaponIds;
		vector<int>armorIds;
		vector<int>thrownIds;
		vector<int>ammoIds;
		vector<int>potionIds;
		vector<int>itemIds;
	vector<int>spellIds;
		extractIDs(weaponIds, weaponstream);
		extractIDs(armorIds, armorstream);
		extractIDs(thrownIds, thrownstream);
		extractIDs(ammoIds, ammostream);
		extractIDs(potionIds, potionstream);
		extractIDs(itemIds, itemstream);
	extractIDs(spellIds, spellstream);

	Weapon aweapon;
	Armor aarmor;
	Item aitem;
	Thrown athrown;
	Consumable aAmmo;
	Potion aPotion;
	Spell aSpell;
	for(unsigned int count = 0; count < weaponIds.size(); ++count)
		{
		//getWeaponFromDB(aweapon, weaponIds[count]); 
		getFromDB(aweapon, weaponIds[count]); 
		stu.inventory.addWeapon(aweapon);
		}
	for(unsigned int count = 0; count < armorIds.size(); ++count)
		{
		//getArmorFromDB(aarmor, armorIds[count]); 
		getFromDB(aarmor, armorIds[count]);
		stu.inventory.addArmor(aarmor);
		}
	for(unsigned int count = 0; count < thrownIds.size(); count = count+2)
		{
		//getThrownFromDB(athrown, thrownIds[count]); 
		getFromDB(athrown, thrownIds[count]);
		athrown.setNumber(thrownIds[count+1]);
		stu.inventory.addThrown(athrown);
		}
for(unsigned int count = 0; count < ammoIds.size(); count = count+2)
		{
		//getAmmoFromDB(aAmmo, ammoIds[count]); 
		getFromDB(aAmmo, ammoIds[count]);
		aAmmo.setNumber(ammoIds[count+1]);
		stu.inventory.addAmmo(aAmmo);
		}
for(unsigned int count = 0; count < potionIds.size(); count = count+2)
		{
		//getPotionFromDB(aPotion, potionIds[count]);
		getFromDB(aPotion, potionIds[count]);
		aPotion.setNumber(potionIds[count+1]);
		stu.inventory.addPotion(aPotion);
		}
	for(unsigned int count = 0; count < itemIds.size(); ++count)
		{
		//getItemFromDB(aitem, itemIds[count]); 
		getFromDB(aitem, itemIds[count]);
		stu.inventory.addItem(aitem);
		} 

	RaceCreator rCreator;
	CharClassCreator cCreator;
	
	stu.myClass = cCreator.getClass(classname);
	stu.myRace = rCreator.getRace(racename);
	
	if(stu.myClass->classmagic->getHasMagic())
	{
		for(unsigned int count = 0; count < spellIds.size(); ++count)
		{
			getFromDB(aSpell, spellIds[count]);
			stu.myClass->classmagic->addSpell(aSpell);
		}
	}

	cout <<"loading abilities/stats"<<endl;

	int x;
	for(x = STR; x <= CHA; ++x)
		{
	stu.myAbilities.setStat(x,stat[x]);
		}
	stu.setMod();
	stu.aSavethrow.updateStatMod(stu.getMod(CON), stu.getMod(DEX), stu.getMod(WIS));
	stu.setAtk();
	stu.setSpeed();
	stu.inventory.loadMoney(cp, sp, gp);
    return in;
} 
 
Hero::Hero() : Actor ()
{
	init = 0; 
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
    CharClassCreator classMachine;
	RaceCreator raceMachine;
    myRace = raceMachine.getRace(0);
    myClass = classMachine.getClass(6);
	
}
Hero::~Hero()
{
	cout<<"Start hero deletion"<<endl;
    delete myClass;
	delete myRace;
	cout<<"Hero deleted"<<endl;
}
	
Hero::Hero(string name):Actor(name)  //Hero constructor - Builds a new hero
{
	setFields();
}
/*void Hero::setName(string name)
{
	Actor::setName(name);
}*/
void	Hero::setFields()
{

	//int x;
	for(unsigned x = STR; x <= CHA; ++x)
	{
		myAbilities.setStat(x);
		setMod(x);
		cout.width(5);
		cout << myAbilities.getStatName(x) <<"="<<myAbilities.getStat(x);
		cout << " mod:"<< setiosflags(ios::showpos)<< getMod(x)<< resetiosflags(ios::showpos)<<endl;
	}
	Crit = false;
   init = 0; 
	AC = 10;
   Lvl = 1;
   Exp = 0;
	Dmg = 3;	//unarmed damage 1d3 for m, 1d2 for s
		//Race::setFields();
		
		CharClassCreator classMachine;
	RaceCreator raceMachine;
	
	bool keep = false;
	char keepRace;
	char keepClass;
	
	//Choose race
	while(!keep)
	{
	myRace = raceMachine.getRace();
	cout<<"You chose "<<endl;
	myRace->outputData();
	cout <<"Your ability stats would be:"<<endl;
	Ability initialAbilities = myAbilities;
	adjustStats(myRace);
	cout<<"Do you want to keep this race with these adjusted abilities? 'y' for yes or 'n' for no: ";
	cin>>keepRace;
		if(keepRace == 'y' || keepRace == 'Y' || keepRace == '1')
			keep = true;
		else if(keepRace == 'n' || keepRace == 'Y' || keepRace == '0')
			{
			myAbilities = initialAbilities;		//return abilities back to original rolls
			delete myRace;
			}
		else
			{
			cout<<"Invalid input, reset abilities and try again"<<endl;
			myAbilities = initialAbilities;		//return abilities back to original rolls
			delete myRace;
			}
	}
	
	//choose Class
	keep = false;
	while(!keep )
	{
	myClass = classMachine.getClass();
	cout<<"You chose "<<endl;
	myClass->outputData();
	cout<<"Do you want to keep this class ?  'y' for yes or 'n' for no: ";
	cin>>keepClass;
	if( keepClass == 'y' || keepClass == 'Y' || keepClass == '1')
		keep = true;
	else if(keepRace == 'n' || keepRace == 'Y' || keepRace == '0')
		{
		delete myClass;
		}
	else
		{
		cout<<"Invalid input, reset choice and try again"<<endl;
		delete myClass;
		}
	}
	
	//Adjustments from race and class
	if(myRace->getSize() == 's')
		Dmg = 2;
			
	//adjustStats(myRace);  //adjust Stat scores acording to race, done above
		//cout<<"---TEST--- output race data"<<endl;
		//myRace->outputData();
		//cout<<"---TEST--- output class data"<<endl;
		//myClass->outputData();
	updateHP();	//Set HP according to class hitDice and CON mod
	
	setSpeed();
	//cout<<"Checking for magic bonus"<<endl;
	checkMagicBonus();
	//update Savethrow with data from class and race
	updateAll();

}
void Hero::setAtk()
{
	Atk = myClass->getAtk();
}
int Hero::getAtk()
{
    return Atk;
}
bool Hero::getCrit()
{
    bool crit = Crit;
    Crit = false;
    return crit;
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
	cout <<"Level: "<<Lvl<<", EXP: "<<getExp()<<" / "<<getExpForNext()<<endl;
    myRace->outputData(); 
    myClass->outputData();
		int savemod = condition.getSaveMod();
	aSavethrow.updateTempBonus(savemod, savemod, savemod );
	aSavethrow.outputData();

	outputStats();
   getAC();
	inventory.whatsEquipped();
	inventory.showList();
	inventory.showMoney();
	long lightweight;
 	if(myRace->getSize() == 's')
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
//		if(getHasMagic() == 'c')
//	{
		Stats index = myClass->classmagic->getAbilitytype();	//int, wis, or char, etc
		myClass->classmagic->setAbilityScore(getStat(index), getMod(index));
//	}
	
			//set new HP by a roll of Hit Dice , CON mod and old HP
	updateHP();

	cout<<"enter Class level up to level "<<Lvl<<endl;
	myClass->levelUp(Lvl);
		//update Atk and Savethrow with data from class
	updateAll();
	

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
    if(condition.getStatMod(stat) != 0)
        cout<<"You have a temporary adjustment to your statMod from a condition"<<endl;
    return statMod[stat]+condition.getStatMod(stat);
}
int Hero::getMod(Stats stat)
{
	   if(condition.getStatMod(stat) != 0)
        cout<<"You have a temporary adjustment to your statMod from a condition"<<endl;
    return statMod[stat]+condition.getStatMod(stat);
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
	HD = myClass->getHitDice();
	
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
	if(newHP<1)
		newHP = 1;
	Actor::setHP(newHP);
cout <<"HP is "<< newHitRoll <<" Hit dice roll, plus " <<getMod(CON)<<" from CON mod and oldHP "<< oldHP << " = "<<Actor::getHP()<< endl;
}
int Hero::getAC()
{
	int armMod = 0; //myArmor.getACmod();
	int shieldMod = 0; // myShield.getACmod();
	int ac;
	int dexMod = getMod(DEX);
	int sizeMod = myRace->getsizeMod();
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

	int bonus = condition.getACMeleeMod();	//Need AC for melee and range separately
		if(bonus != 0)
			cout<<"Bonus or penalty to AC of "<<bonus<<endl;
	return ac+bonus;
} 
/*bool Hero::aliveOrDead()
{
	return Actor::aliveOrDead();
} */
int Hero::meleeRoll()
{	
	Crit = false;
	//srand( time(0));
	Dice dice1d20(1,20);
	int roll = dice1d20.getValue();
	int atkroll = roll + Atk + getMod(STR) + myRace->getsizeMod();
	int mincrit=20;  //usually perfect 20 roll is critical, check weapon for min crit value
	//for(unsigned count =0; count < inventory.weapons.size(); count++)
		//{

int weaponPos = inventory.myEquip.getHandPosition();
		if(weaponPos > -1)
			{
			cout <<"Using weapon: "<< inventory.weapons[weaponPos].Item::getName() << endl;
			mincrit = inventory.weapons[weaponPos].getminCrit();
			}
		else
			{
			cout <<"Using weapon: NONE"<<endl;
			}
	if(roll>=mincrit)  //is this here in attack or in damage rolls? here I think
		{
		Crit = true;
		cout<<"CRITICAL HIT!!" <<endl;
		}
		
		cout << "  Melee hit roll of "<<roll << " plus base Atk bonus "<<Atk<<" + "<<getMod(STR)<<" STR mod + "<<myRace->getsizeMod()<<" size mod"<<endl;
	cout << "Total melee hit roll of "<<atkroll<<endl;
	
		int bonus = condition.getAtkMod();
			if(bonus != 0)
				cout<<"You have an atk bonus or penalty from a condition of "<<bonus<<endl;
	return atkroll+bonus;
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
		 
	int atkroll = roll + Atk + getMod(DEX) + myRace->getsizeMod();
		cout << "  Range hit roll of "<<roll << " plus base Atk bonus "<<Atk<<" + "<<getMod(DEX)<<" DEX mod + "<<myRace->getsizeMod()<<" size mod"<<endl;
			
			int bonus = condition.getAtkMod();
			if(bonus != 0)
				cout<<"You have an atk bonus or penalty from a condition of "<<bonus<<endl;
	return atkroll+bonus;
} 
int Hero::getInit()
{
	return init+getMod(DEX);
} 
void Hero::outputShortData()
{
  	cout << "Hero named "<<getName() <<" with HP:"<<getHP();	//don't need Actor::..
    cout <<", "<<myRace->getRaceName() << " " <<myClass->getClassName(); 
	cout <<" Level: "<<Lvl<< " , exp: "<<Exp<<endl;
    cout<<condition.getStatus()<<endl;
	int savemod = condition.getSaveMod();
	aSavethrow.updateTempBonus(savemod, savemod, savemod );
	aSavethrow.outputData();
      	
    cout<<endl;
  
}

string Hero::getDmgDie()
{
	string temp = "Damage roll ";
	int mult =1, die = Dmg, range=0;

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
				range = 0;
				Dmg = 3;	//unarmed damage 1d3 for m, 1d2 for s
			if(myRace->getSize() == 's')
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
 
int roll = 0;  //damage roll result

	if(hasHand)
		{
	mult = inventory.weapons[weaponPos].getDieMultiple();
			critDmg = inventory.weapons[weaponPos].getCritMultiple();
			Dmg = inventory.weapons[weaponPos].getDie();
		}

	Dice dice(mult,Dmg);
	if(!range)  //melee damage includes str mod
	{ 
	roll = dice.getValue();
	cout <<"Damage roll of "<<roll<<" + Str Mod of "<<getMod(STR)<<endl;
	roll = roll + getMod(STR);
cout <<"For damage of "<<roll<<endl;
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
		int dmgmod = condition.getDmgMod();
		 if(dmgmod!=0)
		 {
			 roll = roll + dmgmod;
			 cout<<"plus "<<dmgmod<<" of special damage adjustment."<<endl;
		 }
		cout <<"You deal "<<roll<<" damage!" <<endl;
	return roll;
} 
string Hero::basicInfo()
{
  string level = to_string(getLevel());
    string temp = Actor::getName() + " (" +myRace->getRaceName() + " Level: ";
	temp= temp+ level +" "+myClass->getClassName() + ") ";
	return temp;
} 

string Hero::getStatName(int stat)
{
	return myAbilities.getStatName(stat);
}	
void Hero::setSpeed()
{
	string race = myRace->getRaceName();
	string classname = myClass->getClassName();
	if(myRace->getSize() == 's')
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
 	if(myRace->getSize() == 's')
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
void Hero::adjustStats(Race *tempRace)
{
//adjust Stat scores acording to race
	for(int x = STR; x <= CHA; ++x)
	{
		//cout<<"Race mod for stat "<<x<<" is "<<
	int newStat=0;
	cout <<"Stat "<<myAbilities.getStatName(x)<< " was ";
	cout <<myAbilities.getStat(x)<<", adjusted to ";
		newStat = myAbilities.getStat(x)+ tempRace->getMod(x);
		if(newStat < 3) 
			newStat = 3;
		myAbilities.setStat(x, newStat);
setMod(x);
	cout <<myAbilities.getStat(x)<<" with mod:"<<setiosflags(ios::showpos);
	cout<< getMod(x) <<resetiosflags(ios::showpos)<< endl;
	}
}
void Hero::checkMagicBonus()
{
		//cout<<"    -in checkMagicBonus()-"<<endl;
	bool hasRmag = myRace->racemagic->getHasMagic();
		//cout<<"--BONUS--- has race magic? "<<hasRmag<<endl;
	bool hasCmag = myClass->classmagic->getHasMagic();
		//cout<<"--BONUS--- has class magic? "<<hasCmag<<endl;
		
	if(hasRmag)
	{
			//cout<<"   Race Magic"<<endl;
	Stats index = myRace->racemagic->getAbilitytype();	//int, wis, or char, etc

			//cout<<"  --Stats is "<<myAbilities.getStatName(index)<<endl;
		int statScore = getStat(index);
		int mod = getMod(index);
			//cout<<"  --mod is: "<<mod<<endl;
			myRace->racemagic->setAbilityScore(statScore, mod);
		myRace->racemagic->bonusSpell();	//this is using default bonusSpell not child version

	}
	if(hasCmag)
	{
			//cout<<"   Class magic"<<endl;
	Stats index = myClass->classmagic->getAbilitytype();	//int, wis, or char, etc
			//cout<<"Stats is "<<myAbilities.getStatName(index)<<endl;
			int statScore = getStat(index);
		int mod = getMod(index);
			//cout<<"  --mod is: "<<mod<<endl;
			myClass->classmagic->setAbilityScore(statScore, mod);
		myClass->classmagic->bonusSpell();	//this is using default bonusSpell not child version
	}

}
void Hero::setCondition(int bitcode)
{
	condition.setCondition(bitcode);
}
void Hero::setCondition(int bitcode, int mod)
{
	condition.setCondition(bitcode, mod);
}
string Hero::getSpellList()
{
	cout<<"Only spell list for the Class created, not gnome spell list"<<endl;
	return myClass->classmagic->getSpellList();
}
string Hero::saveData()
{
    string str;
    str = getName() + " " + to_string(getHP()) + " " + to_string(getMaxHP()) + " ";
    int x;
	for(x = STR; x <= CHA; ++x)
        {
        str = str + to_string(myAbilities.getStat(x)) + " ";
        }
    str = str + to_string(AC) + " " + to_string(Lvl) + " " + to_string(Exp) + " " + myRace->getRaceName() + " " + myClass->getClassName();
    str = str + " " + to_string(inventory.getCopper()) + " " + to_string(inventory.getSilver()) + " " + to_string(inventory.getGold()) + "\n";  
	str = str + inventory.getWeaponIDList() + inventory.getArmorIDList() + inventory.getThrownIDList();
    str = str + inventory.getAmmoIDList() + inventory.getPotionIDList() + inventory.getItemIDList();
	str = str + getSpellList();
    
    return str;
}
char Hero::getHasMagic()
{
    char magictype = '0';
    if(myRace->racemagic->getHasMagic() && myClass->classmagic->getHasMagic())
        magictype = 'b';  //both
    else if(myClass->classmagic->getHasMagic())
        magictype = 'c';  //class
    else if(myRace->racemagic->getHasMagic())
        magictype = 'r';  //race
    else
        magictype = 'n';  //no
        
    return magictype;
}
string Hero::getStartingGear()
{
    string gear = myClass->getStartingGear();
    istringstream gearstream(gear);
    string weapons, armor, ammo, output;
   // char bowCrossSling = 0;     //char to identify ranged weapon
char size = myRace->getSize();
getline(gearstream, weapons);
	getline(gearstream, armor);
       // cout<<"Weapons are: "<<weapons<<endl;
       // cout<<"Armors are: "<<armor<<endl;

		vector<int>weaponIds;
		vector<int>armorIds;
        vector<int>ammoIds;
		
		extractIDs(weaponIds, weapons);
		extractIDs(armorIds, armor);
       // extractIDs(ammoIds, ammo);
              for(unsigned int count = 0; count < weaponIds.size(); ++count)    //create ammo
        {
            if(weaponIds[count] == 13 || weaponIds[count] == 17)
                ammoIds.push_back(1);
            if(weaponIds[count] == 15)
                ammoIds.push_back(2);
            if(weaponIds[count] == 19)
                ammoIds.push_back(3);
                
        }
       
        if(size == 's')
        {
            for(unsigned int count = 0; count < armorIds.size(); ++count)
            {
                armorIds[count]++;
            }
            for(unsigned int count = 0; count < weaponIds.size(); ++count)
            {
                if(weaponIds[count] == 7 || weaponIds[count] == 8)
                {
                    weaponIds[count] = 4;   // change 2-handed to longsword 
                    armorIds.push_back(14); //add shield
                }
                else
                    weaponIds[count]++;
            }
        }
 
        if(myRace->getRace(myRace->getRaceName()) == HAF)
        {   //check to make sure it doesn't already exist
            weaponIds.push_back(20);    //add sling to halfling equipement
            ammoIds.push_back(3);
        }
        
        output = "W: ";
        for(unsigned int count = 0; count < weaponIds.size(); ++count)
            output = output+ to_string(weaponIds[count]) +" ";
        output = output + "\n";
        output = output + "A: ";
        for(unsigned int count = 0; count < armorIds.size(); ++count)
            output = output+ to_string(armorIds[count]) +" ";
        output = output + "\n";
        output = output + "a: ";
        for(unsigned int count = 0; count < ammoIds.size(); ++count)
            output = output+ to_string(ammoIds[count]) +" ";
        output = output + "\n";
        
                
    return output;
}
int Hero::getSaveThrow(Saves save)
{
	//int savemod = condition.getSaveMod();	//are all saveMod the same?
	//aSavethrow.updateTempBonus(savemod, savemod, savemod );
	aSavethrow.updateStatMod(getMod(CON), getMod(DEX), getMod(WIS));
	return Actor::getSaveThrow(save);
	//return aSavethrow.getSaveThrow(save);
}
int Hero::getSaveThrow(Saves save, specialType special)
{
	//int savemod = condition.getSaveMod();
	//aSavethrow.updateTempBonus(savemod, savemod, savemod );
	aSavethrow.updateStatMod(getMod(CON), getMod(DEX), getMod(WIS));
	return Actor::getSaveThrow(save, special);
	//return aSavethrow.getSaveThrow(save, special);
}
void Hero::updateAll()
{
	aSavethrow.setFields(myClass->getSaveThrow(FORT), myClass->getSaveThrow(REF),myClass->getSaveThrow(WIL));
	aSavethrow.setRaceFields(myRace->getRaceSave(FORT), myRace->getRaceSave(REF), myRace->getRaceSave(WIL));
	aSavethrow.updateStatMod(getMod(CON), getMod(DEX), getMod(WIS));
	int specialArray[SPECIAL_TYPE_NUMBER];
for(int c=0; c<SPECIAL_TYPE_NUMBER; ++c)
	specialArray[c] = myRace->getSpecialSave(c);
	aSavethrow.setSpecialFields(specialArray);
	setAtk();
	myClass->turning->setFields(getLevel(), getMod(CHA));

}
#endif


