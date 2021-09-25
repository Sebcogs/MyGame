#ifndef INVENTORY_H
#define INVENTORY_H
//v4
#include<iostream>
#include<vector>
#include<algorithm>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Equip.h"
#include "Thrown.h"
#include "Potion.h"
using namespace std;

class Inventory
{
	//friend ostream& operator<<(ostream&, const Item&);
	//friend istream& operator>>(istream&, Item&);
	private:

		long totalWeight;
		int gold;
		int silver;
		int copper;	
		
	public:
		Inventory();
		Inventory(int level, int percentroll);   
		Equip myEquip;
			vector<Item>items;		//gems and sellable
			vector<Thrown>thrown;	//splash weapons
			vector<Potion>potions;	//healing potions
			vector<Weapon>weapons;	
			vector<Armor>armor;
			vector<Consumable>ammo;
		void showList();
		void showMoney();
			void addItem(Item);
			void addThrown(Thrown);
			void addPotion(Potion);
			void addWeapon(Weapon);
			void addArmor(Armor);
			void addAmmo(Consumable);
			Item dropItem(int position);
			Thrown dropThrown(int position);
			Potion dropPotion(int position);
			Weapon dropWeapon(int position);
			Armor dropArmor(int position);
			Consumable dropAmmo(int position);
		void receiveMoney(int, int, int);
		void loadMoney(int, int, int);
		int spendMoney(int, int, int);
			int getArmorNum() const;
			int getWeapNum() const;
			int getItemNum() const;
			int getThrownNum() const;
			int getPotionNum() const;
			int getAmmoNum() const;
			string getArmorIDs();
			string getWeaponIDs();
			string getThrownIDs();
			string getPotionIDs();
			string getItemIDs();
			string getAmmoIDs();
			string getArmorIDList();
			string getWeaponIDList();
			string getThrownIDList();
			string getPotionIDList();
			string getAmmoIDList();
			string getItemIDList();
		int getCopper() const;
		int getSilver() const;
		int getGold() const;
		long getTotalWeight();
			int getArmorID(int position);
			int getWeaponID(int position);
			int getThrownID(int position);
			int getPotionID(int position);
			int getItemID(int position);
			int getAmmoID(int position);
		void equipWeapon(int position);
		void equipArmor(int position);
		void whatsEquipped();
		void unEquip();
		
};
#endif		 
