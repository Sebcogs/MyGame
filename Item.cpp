#ifndef ITEM_CPP
#define ITEM_CPP

//v4
#include<iostream>
#include<string>
#include "Item.h"
using namespace std;


ostream& operator<<(ostream& out, const Item& anItem)
{
	//out << "-"<< anItem.itemName << " " << anItem.weight<<"lb";
out << anItem.IDnum << " " << anItem.itemName << "  "<< anItem.weight <<" "  <<anItem.value<< " "<< anItem.description <<endl;
   return out;
}
istream& operator>>(istream& in, Item& anItem)
{
	//cout << "Enter item name: ";
	//in >> anItem.itemName;
	//cout << "Enter weight: ";
	//in >> anItem.weight;
			string name;
	double weight, price;
	int id;
	
	string desc;	
	in >> id >> name >> weight>> price;
 getline(in, desc);

	anItem.setFields(weight, name, desc, id, price);
	return in;
} 

bool Item::operator<(Item& item) //sort alphabetically
{
	return(itemName < item.itemName);
}
Item::Item()
{
}
Item::Item(double pounds, string name, string desc, int id=0)
{
    setFields(pounds, name, desc, id);
}
Item::Item(double pounds, string name, string desc, int id, double value)
{
    setFields(pounds, name, desc, id, value);
}
void Item::setFields(double pounds, string name, string desc, int id)
{
    weight = pounds;
    itemName = name;
    description = desc;
	IDnum = id;
	value = 0;
}
void Item::setFields(double pounds, string name, string desc, int id, double price)
{
    weight = pounds;
    itemName = name;
    description = desc;
	IDnum = id;
	value = price;
}
void Item::display()
{
    cout <<" - "<< itemName <<", " << weight <<" lb. ";
//	if(value > 10)
//	cout <<value<<" gp";
   // displayDesc();
}
    
double Item::getWeight()
{
    return weight;
}

string Item::getName()
{
    return itemName;
}
void Item::displayDesc()
{
    cout << " description: "<< description << endl;
}
string Item::getDesc()
{
	return description;
}
int Item::getID()
{
	return IDnum;
}
double Item::getValue()
{
	return value;
}
void Item::setValue(double price)
{
	value = price;
}


#endif
