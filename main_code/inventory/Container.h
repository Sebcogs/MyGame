//v4
#ifndef CONTAINER_H
#define CONTAINER_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "Inventory.h"
//#include "Item.h"

using namespace std;

class Container
{
	private:
		
		string description;
		string type;  //chest, bag, etc
		bool locked;  //make lock class..
	public:
		Container();
		Container(string, string, int, int);
	Inventory bag;
		void getDesc();
		bool isLocked();
		void open();
		void showContents();
		int lock();
		int unlock();
		Item takeItem();
		Potion takePotion();
		string takeMoney();
		string takeAllMoney();
		void showType();
};
#endif
