//v4
#ifndef INVENTORY_CPP
#define INVENTORY_CPP

#include<iostream>
#include<vector>
#include<algorithm>
#include "Inventory.h"
#include<string>
#include "Dice.h"
//#include "Item.h"
//#include "Weapon.h"
//#include "Armor.h"
using namespace std;


Inventory::Inventory()
{	//Start with basic things TO TEST
		items.clear();
		thrown.clear();
		potions.clear();
		weapons.clear();
		armor.clear();
		ammo.clear();
	Item backpack(1, "Backpack", "A pack carried on the back for storing loot", 0);
	//Weapon aWeapon;
	//Armor someArmor;

	items.push_back(backpack);
	//weapons.push_back(aWeapon);
	//armor.push_back(someArmor);
		sort(items.begin(), items.end());
	//	sort(weapons.begin(), weapons.end());
		//sort(armor.begin(), armor.end());
	//totalWeight = backpack.getWeight()+aWeapon.getWeight()+someArmor.getWeight();
	Equip stuff;
	myEquip = stuff;
	gold = 1;
	silver = 10;
	copper = 20;
}
Inventory::Inventory(int level, int percentRoll)
{	//create random loot, similar to pg53 of DMG
	 srand( time(0) +percentRoll);
		Equip stuff;
	myEquip = stuff;
		gold =0;
		silver = 0;
		copper = 0;
		items.clear();
	thrown.clear();
	potions.clear();
		weapons.clear();
		armor.clear();
		ammo.clear();
	int LOW = 15-level;
	int MIDLOW = 30-level;
	int MID = 53-level;
	int MIDHIGH = 95;
	int HIGH = 100;
	if(percentRoll < LOW )
		{
		gold = 0;
		silver = 0;
		copper = 0;
		}
	else if(percentRoll < MIDLOW)
		{
		Dice cpdice(level,6);
		copper = cpdice.getValue()*100;		
		}
	else if(percentRoll < MID)
		{
		Dice spdice(level,8);
		silver = spdice.getValue()*10;
		}
	else if(percentRoll < MIDHIGH)
		{
		Dice gpdice(level,8);
		gold = gpdice.getValue()*1;
Dice potiondice(1,1+level);
		int potNumber = potiondice.getValue();
			if(potNumber<1)
				potNumber = 1;
			Potion potion(1, "Light Heal Potion", "A small vial containing some liquid", 2, 50, 8, 1);
//double weight, string name, string desc, int id, int price, int healDie, int healMult
	//	for(int i = 0; i<potNumber; i++)
		//	{
		potion.setNumber(potNumber);
			potions.push_back(potion);
		//	}
		
		}
	else if(percentRoll<=HIGH)
		{
		Dice gpdice(level,8);
		gold = gpdice.getValue()*2;
		Dice gemdice(1,level);
		int gemNumber = gemdice.getValue();
			if(gemNumber<1)
				gemNumber = 1;
			Item gem(.25, "Gem", "A beautiful shiny gemstone", 0, 100);
		for(int i = 0; i<gemNumber; i++)
			{
			items.push_back(gem);
			}
		
		}
	else
		cout <<"Error building inventory. How can the roll be higher than 100%"<<endl;	
}
void Inventory::showList()
{
	
	//cout <<" Showlist() function "<<endl;
	unsigned count;
	cout<<"The inventory contains: "<<endl;
	if(!items.empty())
		{
	for(count = 0; count < items.size(); ++count)
			{
		items[count].display();
	//	cout <<" "<<items[count].getDesc()<<endl;
		cout <<endl;
			}
		}

	if(!thrown.empty())
		{
	for(count = 0; count < thrown.size(); ++count)
			{
		thrown[count].display();
	//	cout <<" "<<thrown[count].getDesc()<<endl;
	//	cout << endl;
			}
		}

	if(!potions.empty())
		{
	for(count = 0; count < potions.size(); ++count)
			{
		potions[count].display();
	//	cout <<" "<<potions[count].getDesc()<<endl;
	//	cout <<endl;
			}
		}

	if(!weapons.empty())
		{
	cout<<"Weapons: "<<endl;
	for(count = 0; count < weapons.size(); ++count)
	 weapons[count].display();
		}

	if(!ammo.empty())
		{
		for(count = 0; count < ammo.size(); ++count)
			{
			ammo[count].display();
		//	cout <<" "<<ammo[count].getDesc()<<endl;
			cout <<endl;
			}
		}
	if(!armor.empty())
		{
	cout <<"Armor: "<<endl;
	for(count = 0; count < armor.size(); ++count)
	armor[count].display();  
		}
	else
		cout <<" - No items. "<<endl;

}
void Inventory::showMoney()
{
	if(copper != 0 || silver !=0 || gold != 0)
	cout<< "Coins include: "<<endl<<" - " <<copper<<"cp, " << silver << "sp, and "<<gold<<"gp"<<endl;
}
void Inventory::addItem(Item thing)
{

totalWeight = totalWeight + thing.getWeight();
items.push_back(thing);
}
void Inventory::addThrown(Thrown thing)
{  //Check if exists already, if it does increase the Thrown number 
	string addedName = thing.getName();
	int qty = thing.getNumber();
	bool inInv = false;
	for(int i = 0; i < getThrownNum(); ++i)
		{
		if(addedName == thrown[i].getName())
			{
		int previousQty = thrown[i].getNumber();
		int newQty = previousQty + qty;
		thrown[i].setNumber(newQty);
		inInv = true;
			}
		}
	if(inInv == false)
		thrown.push_back(thing);

	//cout<<"weight of thrown items, qty: "<<qty<<" x weight: "<<thing.getWeight()<<" = "<<(qty*thing.getWeight())<<endl;
totalWeight = totalWeight + (qty*thing.getWeight());

}
void Inventory::addPotion(Potion thing)
{  //Check if exists already, if it does increase the potion number 
	string addedName = thing.getName();
	int qty = thing.getNumber();
	bool inInv = false;
	for(int i = 0; i < getPotionNum(); ++i)
		{
		if(addedName == potions[i].getName())
			{
		int previousQty = potions[i].getNumber();
		int newQty = previousQty + qty;
		potions[i].setNumber(newQty);
		inInv = true;
			}
		}
	if(inInv == false)
		potions.push_back(thing);

	//cout<<"weight of potion items, qty: "<<qty<<" x weight: "<<thing.getWeight()<<" = "<<(qty*thing.getWeight())<<endl;
totalWeight = totalWeight + (qty*thing.getWeight());

}
void Inventory::addAmmo(Consumable thing)
{  //Check if exists already, if it does increase the potion number 
	string addedName = thing.getName();
	int qty = thing.getNumber();
	bool inInv = false;
	for(int i = 0; i < getAmmoNum(); ++i)
		{
		if(addedName == ammo[i].getName())
			{
		int previousQty = ammo[i].getNumber();
		int newQty = previousQty + qty;
		ammo[i].setNumber(newQty);
		inInv = true;
			}
		}
	if(inInv == false)
		{
		ammo.push_back(thing);
	totalWeight = totalWeight + thing.getWeight();  //Only adjust weight when didn't have before
		}

}
void Inventory::addWeapon(Weapon thing)
{
	totalWeight = totalWeight + thing.getWeight();
	weapons.push_back(thing);
}
void Inventory::addArmor(Armor thing)
{
	totalWeight = totalWeight + thing.getWeight();
	armor.push_back(thing);
}
Item Inventory::dropItem(int position)
{
	Item thing;
		if(position< getItemNum() )	
		{	
		thing = items.at(position);	

		items.erase(items.begin()+position);
		cout <<"Item dropped from inventory"<<endl;
		totalWeight = totalWeight - thing.getWeight();
	//	i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
	//	return 0;
	}
	
	return thing;
}
Thrown Inventory::dropThrown(int position)
{
	Thrown thing;
		if(position< getThrownNum() )	
		{	
		thing = thrown.at(position);	
	if(thing.getNumber() == 1)
		{	//use last of this type of item
		thrown.erase(thrown.begin()+position);
		cout <<"Item dropped from inventory"<<endl;
		}
		else if(thing.getNumber() > 1)
		{   // use one of several of this type and reduce number owned.
			thing.removeThrown();
			thrown.at(position) = thing;
		}
		else
			cout <<"     Error!!  problem with dropThrown in Inventory"<<endl;

		totalWeight = totalWeight - thing.getWeight();
	//	i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
	//	return 0;
	}
	
	return thing;
}
Potion Inventory::dropPotion(int position)
{
	Potion thing;
		if(position< getPotionNum() )	
		{	
		thing = potions.at(position);	
	if(thing.getNumber() == 1)
		{	//use last of this type of item
		potions.erase(potions.begin()+position);
		cout <<"Item dropped from inventory"<<endl;
		}
		else if(thing.getNumber() > 1)
		{   // use one of several of this type and reduce number owned.
			thing.removePotion();
			potions.at(position) = thing;
		}
		else
			cout <<"     Error!!  problem with dropPotion in Inventory"<<endl;

		totalWeight = totalWeight - thing.getWeight();
	//	i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
	//	return 0;
	}
	
	return thing;
}
Consumable Inventory::dropAmmo(int position)
{
	Consumable thing;
		if(position< getAmmoNum() )	
		{	
		thing = ammo.at(position);	
	if(thing.getNumber() == 1)
		{	//use last of this type of item
		ammo.erase(ammo.begin()+position);
		cout <<"Item dropped from inventory"<<endl;
	totalWeight = totalWeight - thing.getWeight();  //weight only change when last one is gone
		}
		else if(thing.getNumber() > 1)
		{   // use one of several of this type and reduce number owned.
			thing.removeConsumable();
			ammo.at(position) = thing;
	
		}
		else
			cout <<"     Error!!  problem with dropPotion in Inventory"<<endl;

		
	//	i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
	//	return 0;
	}
	
	return thing;
}

Weapon Inventory::dropWeapon(int position)
{
	Weapon thing;
		if(position < getWeapNum() )
		{
	thing = weapons.at(position);	

		weapons.erase(weapons.begin()+position);
		cout <<"Weapon dropped from inventory"<<endl;
		totalWeight = totalWeight - thing.getWeight();
		//i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
		//return thing;
	}
	
	return thing;
}
Armor Inventory::dropArmor(int position)
{
		Armor thing;
		if(position < getArmorNum() )
		{
	thing = armor.at(position);	

		armor.erase(armor.begin()+position);
		cout <<"Armor dropped from inventory"<<endl;
		totalWeight = totalWeight - thing.getWeight();
		//i = items.size();
		}
		else
		{
		cout <<"Wrong position, error";
		//return thing;
	}
	
	return thing;
}
void Inventory::receiveMoney(int cp, int sp, int gp)
{
	gold +=gp;
	silver +=sp;
	copper += cp;
	cout<<"You stash "<<cp<<" copper, "<<sp<<" silver and "<<gp<<" gold"<<endl;
	//showMoney();
}
void Inventory::loadMoney(int cp, int sp, int gp)
{
	gold =gp;
	silver =sp;
	copper = cp;
	cout<<"You stash "<<cp<<" copper, "<<sp<<" silver and "<<gp<<" gold"<<endl;
	//showMoney();
}
int Inventory::spendMoney(int cp, int sp, int gp)
{
	int notBroke = 1;

	if(gold < gp || silver < sp || copper < cp)
		{
		cout << "You don't have enough"<<endl;
		notBroke = 0;
		}
	else
	{
	gold -=gp;
	silver -= sp;
	copper -= cp;
	cout <<" You remove "<<cp<<" copper, "<<sp<< " silver and "<<gp<<" gold coins."<<endl;
	//showMoney():
	notBroke = 1;
	}
	return notBroke;  //returns 1 or true is have enough money

}
int Inventory::getArmorNum()
{
	return armor.size();
}
int Inventory::getWeapNum()
{
	return weapons.size();
}
int Inventory::getItemNum()
{
	return items.size();
}
int Inventory::getThrownNum()
{
	return thrown.size();
}
int Inventory::getPotionNum()
{
	return potions.size();
}
int Inventory::getAmmoNum()
{
	return ammo.size();
}
string Inventory::getArmorIDs()
{
	string output;
	output = "A: ";
	for(int i = 0; i < getArmorNum(); ++i)
		 output += "#" + to_string(armor[i].getID()) +"-" +armor[i].Item::getName() + " ";
	output +='\n';
	return output;
}
string Inventory::getWeaponIDs()
{
	string output;
	output = "W: ";
	for(int i = 0; i < getWeapNum(); ++i)
		{
		//cout<<"weapon ID: "<<to_string(weapons[i].getID())<<endl;
		 output = output + "#" + to_string(weapons[i].getID()) +"-" + weapons[i].Item::getName() + " ";
		}
	output +='\n';
	//cout << "getWeaponIDS: "<<output <<endl;
	return output;
}
string Inventory::getThrownIDs()
{
	string output;
	output = "T: ";
	for(int i = 0; i < getThrownNum(); ++i)
		{
		//cout<<"weapon ID: "<<to_string(weapons[i].getID())<<endl;
	 output = output + "#" + to_string(thrown[i].getID()) + "-" + thrown[i].Item::getName() + " (" + to_string(thrown[i].getNumber()) + ") ";
		}
	output +='\n';
	//cout << "getWeaponIDS: "<<output <<endl;
	return output;
}
string Inventory::getPotionIDs()
{
	string output;
	output = "P: ";
	for(int i = 0; i < getPotionNum(); ++i)
		{
		output = output + "#" + to_string(potions[i].getID()) + "-" + potions[i].getName();
 		output = output + " (" + to_string(potions[i].getNumber()) + ") ";
		}
	output +='\n';

	return output;
}
string Inventory::getAmmoIDs()
{
	string output;
	output = "a: ";
	for(int i = 0; i < getAmmoNum(); ++i)
		{
		output = output + "#" + to_string(ammo[i].getID()) + "-" + ammo[i].getName();
 		output = output + " (" + to_string(ammo[i].getNumber()) + ") ";
		}
	output +='\n';

	return output;
}
string Inventory::getItemIDs()
{
	string output;
	output = "i: ";
	for(int i = 0; i < getItemNum(); ++i)
		{
		output = output + "#" + to_string(items[i].getID()) + "-" + items[i].getName();
 		//output = output + " (" + to_string(items[i].getNumber()) + ") ";
		}
	output +='\n';

	return output;
}
/*  
ID List for save to text
*/

string Inventory::getArmorIDList()  
{
	string output;
	output = "A: ";
	for(int i = 0; i < getArmorNum(); ++i)
		 output += to_string(armor[i].getID()) +" ";
	output +='\n';
	return output;
}
string Inventory::getWeaponIDList()
{
	string output;
	output = "W: ";
	for(int i = 0; i < getWeapNum(); ++i)
		{
		//cout<<"weapon ID: "<<to_string(weapons[i].getID())<<endl;
		 output = output + to_string(weapons[i].getID()) + " ";
		}
	output +='\n';
	//cout << "getWeaponIDS: "<<output <<endl;
	return output;
}

// separated by T: ID1 qauntity1 ID2 quantity2 ID3 quantity3 ...
string Inventory::getThrownIDList()
{
	string output;
	output = "T: ";
	for(int i = 0; i < getThrownNum(); ++i)
		{
		//cout<<"weapon ID: "<<to_string(weapons[i].getID())<<endl;
	 output = output + to_string(thrown[i].getID()) + " "+ to_string(thrown[i].getNumber())+ " ";
		}
	output +='\n';
	//cout << "getWeaponIDS: "<<output <<endl;
	return output;
}
string Inventory::getPotionIDList()
{
	string output;
	output = "P: ";
	for(int i = 0; i < getPotionNum(); ++i)
		{
	 output = output + to_string(potions[i].getID()) + " "+ to_string(potions[i].getNumber())+ " ";
		}
	output +='\n';

	return output;
}
string Inventory::getAmmoIDList()
{
	string output;
	output = "a: ";
	for(int i = 0; i < getAmmoNum(); ++i)
		{
	 output = output + to_string(ammo[i].getID()) + " "+ to_string(ammo[i].getNumber())+ " ";
		}
	output +='\n';

	return output;
}
string Inventory::getItemIDList()
{
	string output;
	output = "i: ";
	for(int i = 0; i < getItemNum(); ++i)
		{
		if(items[i].getID() != 0)
			{
	 output = output + to_string(items[i].getID()) +" ";
// + " "+ to_string(items[i].getNumber())+ " ";
			}
		}
	output +='\n';

	return output;
}

int Inventory::getCopper()
{
	return copper;
}
int Inventory::getSilver()
{
	return silver;
}
int Inventory::getGold()
{
	return gold;
}
long Inventory::getTotalWeight()
{
	totalWeight = 0;	
	//int weight = 0;
	unsigned count;
	for(count = 0; count < items.size(); ++count)
		{
		totalWeight= totalWeight + items[count].getWeight();
	//	cout << endl;
		}
	for(count = 0; count < thrown.size(); ++count)
		{
		totalWeight= totalWeight + thrown[count].getWeight()*thrown[count].getNumber();
	//	cout << endl;
		}
	for(count = 0; count < potions.size(); ++count)
		{
		totalWeight= totalWeight + potions[count].getWeight()*potions[count].getNumber();
		//cout << endl;
		}
for(count = 0; count < ammo.size(); ++count)
		{
		totalWeight= totalWeight + ammo[count].getWeight();
		}
	for(count = 0; count < weapons.size(); ++count)
	 totalWeight= totalWeight + weapons[count].getWeight();
	
	for(count = 0; count < armor.size(); ++count)
	totalWeight= totalWeight + armor[count].getWeight();  
	totalWeight= totalWeight + gold*.02 + silver *.02 + copper*.02;
		
	//weight = totalWeight;
	return totalWeight;
}
int Inventory::getArmorID(int position)
{
	return armor.at(position).getID();
}
int Inventory::getWeaponID(int position)
{
	return weapons.at(position).getID();
}
int Inventory::getThrownID(int position)
{
	return thrown.at(position).getID();
}
int Inventory::getPotionID(int position)
{
	return potions.at(position).getID();
}
int Inventory::getAmmoID(int position)
{
	return ammo.at(position).getID();
}
int Inventory::getItemID(int position)
{
	return items.at(position).getID();
}
void Inventory::equipWeapon(int position)
{
	int size = weapons.size();
	
	if(position >=0 && position <= size)
	{
	if(!weapons[position].isEquipped())
		{
	int range = weapons.at(position).getRange();
	bool ranged = false;
		if(range > 0)
		ranged = true;
//cout <<"Weapon has range "<<range<<" and is therefore ranged:"<<ranged<<endl;
	char hand;
	cout<< "Do you want to equip this to the main hand 'm', off hand 'o', or 2-hand 't'?";
	cin >> hand;
	switch (hand) {
	case 'm' :
		{
	if(weapons[position].Item::getName()[0] == 'G' || weapons.at(position).Item::getName()[0] == 'Q' || ranged)
			cout <<"These are two handed weapons, equip as such!"<<endl;
	else{
			if(myEquip.setHand(position))
				{
				weapons.at(position).wield();
			cout <<"You hold your "<< weapons[position].Item::getName();
			cout <<" in your main hand!" <<endl;
				myEquip.setRange(ranged);
				}
		}
		}
	break;
	case 'o' : 
		{
		if(weapons[position].Item::getName()[0] == 'G' || weapons.at(position).Item::getName()[0] == 'Q' || ranged)
			cout <<"These are two handed weapons, equip as such!"<<endl;
	else{
			if(myEquip.setOffHand(position, false))
			{
		weapons.at(position).wield();
		cout <<"You hold your "<< weapons[position].Item::getName();
		cout <<" in your off hand!" <<endl;
				myEquip.setRange(ranged);
			}
		}
		}
	break;
	case 't' : 
		{
		if(weapons[position].Item::getName()[0] == 'G' || weapons.at(position).Item::getName()[0] == 'Q' || ranged)
			{
			if(myEquip.set2Hand(position))
				{
			weapons.at(position).wield();
		cout <<"You hold your "<< weapons[position].Item::getName() <<" in both hands!" <<endl;
				myEquip.setRange(ranged);
				}
			}
		else
			cout <<"That is not a 2handed weapon.  Try again"<<endl;
		}
	break;
		default: cout <<"error, didn't read correct input"<<endl;
	}
	}
	else
		cout <<"That weapon is already equipped"<< endl;
	}
	else
		cout <<"Error.  Either the inventory.equipArmor position is -1 or larger than the vector size"<<endl;
}
void Inventory::equipArmor(int position)
{
	int size = armor.size();
	if(position >=0 && position <= size)
	{
	

	string str = armor[position].Item::getName().substr(0,6);
	//cout <<"check shield string...: "<<str<<endl;
	if( str == "Shield") 
		{
			if(myEquip.setOffHand(position, true))
			{
			armor.at(position).wield();
			cout << "You hold your "<< armor[position].Item::getName() <<" in your off hand!" <<endl;
			}
		}
		else 	
		{
			if(myEquip.setBody(position))
			{
			armor.at(position).wield();
			cout << "You don your "<< armor[position].Item::getName() <<" !" <<endl;
			}
		}
	}
	else
		cout <<"Error.  Either the inventory.equipArmor position is -1 or larger than the vector size"<<endl;

}
void Inventory::whatsEquipped()
{
cout <<"	This is what you have equipped: "<<endl;
cout <<"	Body: ";
	int armorpos = myEquip.getBodyPosition();
	bool hasbody = myEquip.hasBody();
	bool has2hand = myEquip.has2Hand();
	bool hasHand = myEquip.hasHand();
	bool hasOffHand = myEquip.hasOffHand();
	bool isShield = myEquip.getIsShield();
		if(hasbody)	
		{
	cout << armor[armorpos].Item::getName()<<endl;	
		}
		else
		{
	cout <<"nothing"<<endl;
		}
	
		cout <<"	Main Hand: ";
int weaponpos = myEquip.get2HandPosition();
	
	if(has2hand) 
	{
	
	cout <<weapons[weaponpos].Item::getName()<<" in both hands."<<endl;
	}
	else if(hasHand)
	 {
	weaponpos = myEquip.getHandPosition();
	cout <<weapons[weaponpos].Item::getName()<<" in your main hands."<<endl;
	}
	else
		{
		cout <<"nothing. "<<endl;
		}
	//cout <<"Entering offhand"<<endl;
	int offhandpos = myEquip.getOffHandPosition();
	//	cout <<"Offhand position "<< offhandpos << ", Has Offhand: " <<hasOffHand << endl;
	cout <<"	Off-hand: ";
	if(hasOffHand && offhandpos >= 0)
		{
		if(isShield)
			{
		cout << armor[offhandpos].Item::getName() <<" in your off hand"<<endl;
			}
		else 
			{
			cout <<weapons[offhandpos].Item::getName() <<" in your off hand"<<endl;
			}
		}
		else
			{
			cout <<"nothing";
			}
		cout << endl;
}	
void Inventory::unEquip()
{
	const char QUIT = 'q';
	const int EMPTY = -1;
	char input;
	bool hasbody = myEquip.hasBody();
	bool has2hand = myEquip.has2Hand();
	bool hasHand = myEquip.hasHand();
	bool hasOffHand = myEquip.hasOffHand();
	bool isShield = myEquip.getIsShield();

	whatsEquipped();
	cout <<" what do you want to unequip? Body 'b', main hand 'm', or offhand 'o' or "<<QUIT<<" to quit?";
	cin >> input;
	while(input != QUIT) 
	{
	switch(input) 
		{
		case 'b' :
			{
			if(hasbody)
				{
				int armorpos = myEquip.getBodyPosition();
				armor.at(armorpos).unwield();
			cout << "You take off your ";
			cout << armor[armorpos].Item::getName() <<" !" <<endl;
				myEquip.setBody(EMPTY);
				}
			else
				cout <<"You have nothing equipmed there."<<endl;
			}
		break;
		case 'm' :
			{
			if(hasHand)
				{
				int weaponpos = myEquip.getHandPosition();
				weapons.at(weaponpos).unwield();
				cout << "You sheath your ";
				cout << weapons[weaponpos].Item::getName(); 
				myEquip.setHand(EMPTY);
				if(has2hand)
					{
					weaponpos = myEquip.get2HandPosition();
					weapons.at(weaponpos).unwield();  //should not be needed
					myEquip.set2Hand(EMPTY);
					cout <<" from both hands!"<<endl;
						myEquip.setRange(false);
					}
				else
					cout <<" from your main hand!"<<endl;
				}
			else
				cout <<"You have nothing equipped there."<<endl;
			}
		break;
		case 'o' :
			{
			if(hasOffHand)
				{
				if(isShield)
					{
					int armorpos = myEquip.getOffHandPosition();
					armor.at(armorpos).unwield();
				cout << "You remove your ";
			cout << armor[armorpos].Item::getName() <<" from your arm!" <<endl;
					}
				else
					{
				int weaponpos = myEquip.getOffHandPosition();
					weapons.at(weaponpos).unwield();
				cout << "You sheath your ";
			cout << weapons[weaponpos].Item::getName();
			cout <<" from your off hand!" <<endl;
					}
				myEquip.setOffHand(EMPTY, false);
				}
			else
				cout <<"You have nothing equipped there."<<endl;
			}
		break;
		default: cout <<"error, didn't read correct input"<<endl;
		}
		cout <<"Unequip something else? Body 'b', main hand 'm', or offhand 'o' or "<<QUIT<<" to quit?";
	cin >> input;
	}			
}

#endif

/*
int main()
{
Inventory bag;

//unsigned count;
Item enteredVal;
Weapon enteredWeap;
Armor enteredArm;
const char QUIT = 'q';
char quitChar;
cout<< "create a basic inventory"<<endl;
bag.showList();


cout << "Do you want to insert a new item, weapon or armor into " <<
"the list? i, w, a or q ";
cin >> quitChar;
while(quitChar != QUIT)
{
	string name;
	double weight;
	int ac;
	int dmgdie;
	if(quitChar == 'i')
	{
cout << "Enter a new inventory item " <<
"to add to the list " << endl << " ";
	cout <<"Enter the name ";
cin >> name;
	cout << "Enter weight ";
cin >> weight;

enteredVal.setFields(weight, name, "Description ");
bag.addItem(enteredVal);
	}
	else if(quitChar == 'w')
	{
	cout << "Enter a new weapon item " <<
"to add to the list " << endl << " ";
	cout <<"Enter the name ";
cin >> name;
	cout << "Enter weight ";
cin >> weight;
	cout << "Enter damage die";
cin >> dmgdie;

enteredWeap.setFields(weight, name, "Description ", dmgdie, 1, 20, 2);
bag.addWeapon(enteredWeap);
	}
	else if(quitChar == 'a')
	{
	cout << "Enter a new armor item " <<
"to add to the list " << endl << " ";
	cout <<"Enter the name ";
cin >> name;
	cout << "Enter weight ";
cin >> weight;
	cout << "Enter AC mod ";
cin >>ac;

enteredArm.setFields(weight, name, "Description ", ac, 0);
bag.addArmor(enteredArm);
	}

bag.showList();

cout << "Do you want to insert another new item "
"into the list? y or n ";
cin >> quitChar;
}

return 0;
}
*/
