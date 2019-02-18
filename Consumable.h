#ifndef CONSUMABLE_H
#define CONSUMABLE_H
//v4
#include<iostream>
#include<string>
#include "Item.h"
using namespace std;

class Consumable : public Item
{
  friend ostream& operator<<(ostream&, const Consumable&);
  friend istream& operator>>(istream&, Consumable&);
	private:
		int number;
	public:
		Consumable();
		Consumable(double weight, string name, string desc, int id, double price);
		//void setFields(double weight, string name, string desc, int id, int price, int healDie, int healMult);
		void display();
		int getNumber();
		void setNumber(int number);
		void addConsumable();
		void removeConsumable();
		
};
#endif		
