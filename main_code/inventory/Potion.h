#ifndef POTION_H
#define POTION_H
//v4
#include<iostream>
#include<string>
#include "Consumable.h"
using namespace std;

class Potion: public Consumable
{
  friend ostream& operator<<(ostream&, const Potion&);
  friend istream& operator>>(istream&, Potion&);
	private:
		int healDie;  //healing from healMult-d-(healDie) dice
		int healMult;
		//int number;
	public:
		Potion();
		Potion(double weight, string name, string desc, int id, int price, int healDie, int healMult);
		void setFields(double weight, string name, string desc, int id, int price, int healDie, int healMult);
		int getHealDie();	
		int getHealMult();
		//int getHealRoll();
		void display();
	//	int getNumber();
	//	void setNumber(int number);
		void addPotion();
		void removePotion();
		
};
#endif		
