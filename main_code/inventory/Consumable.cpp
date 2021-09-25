#ifndef CONSUMABLE_CPP
#define CONSUMABLE_CPP
//v4

#include<iostream>
#include<string>
//#include "Item.h"
#include "Consumable.h"
using namespace std;

ostream& operator<<(ostream& out, Consumable aConsum)
{
	out << aConsum.getID() << " " << aConsum.getName() << "  "<< aConsum.getWeight() <<" " 
<< aConsum.getNumber()<< " " <<aConsum.getValue()<< " "<< aConsum.getDesc()<<endl;
   return out;
}
istream& operator>>(istream& in, Consumable& aConsum)
{
		string name;
	double weight, price;
	int number, id;
	
	string desc;	
	in >> id >> name >> weight>> number >> price;
 getline(in, desc);

	Consumable temp(weight, name, desc, id, price);
	temp.setNumber(number);
	aConsum = temp;
	return in;
} 

Consumable::Consumable():Item()
{
	Item::setFields(0.25, "Consumable", "A Consumable to use", 0);
	number = 1;
}

Consumable::Consumable(double weight, string name, string desc, int id, double price):Item(weight, name, desc, id, price)
{
	number = 1;
}

/*
void Consumable::setFields(double weight, string name, string desc, int id, int price)
{
	Item::setFields(weight, name, desc, id, price);
	//healDie = die;
	//healMult = mult;
	number = 1;
}
*/

void Consumable::display()
{
	//cout <<" "<<number;
	Item::display();
	cout <<" -"<<getNumber()<<"-";
	
}

int Consumable::getNumber()
{
	return number;
}
void Consumable::setNumber(int num)
{
	//cout <<"You have "<<num<<" "<<getName();
	number = num;
	/*	if(num>1)
		cout <<"s";
	cout <<endl; */
}
void Consumable::addConsumable()
{
	cout<<"You add a "<< getName() <<" to the others."<<endl;
	number++;
}
void Consumable::removeConsumable()
{
	if(number > 1)
		{
		cout<<"You remove a "<< getName() <<" from the others."<<endl;
		if(number < 5)
			cout <<"  !! You have very few left!"<<endl;
		number--;
		}
	else
		cout <<"  Error!! removeConsumable() when number is not >1 error"<<endl;
}
#endif		
