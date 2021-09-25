#ifndef THROWN_H
#define THROWN_H
//v4
#include<iostream>
#include<string>
//#include "Item.h"
#include "Consumable.h"
using namespace std;

class Thrown: public Consumable //, public Item
{
  friend ostream& operator<<(ostream&, const Thrown&);
  friend istream& operator>>(istream&, Thrown&);
	private:
		int dmg;  //damage from 1d(dmg) dice
		const static int range =3;
		int effectRounds;
		//int number;
	public:
		Thrown();
		Thrown(double weight, string name, string desc, int id, int price, int dmg, int effectRounds);
		void setFields(double weight, string name, string desc, int id, int price, int dmg, int effectRounds);
		int getDmg();
	//	int getDmgRoll();
		void display();
		int getRange();
		int getRounds();
	//	int getNumber();
	//	void setNumber(int number);
		void addThrown();
		void removeThrown();
		
};
#endif		
