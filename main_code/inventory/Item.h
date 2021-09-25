#ifndef ITEM_H
#define ITEM_H
//v4
#include<iostream>
#include<string>
using namespace std;

class Item
{
   friend ostream& operator<<(ostream&, const Item&);
  friend istream& operator>>(istream&, Item&);
   protected:
      double weight;
        string itemName;
        string description;
		int IDnum;
		double value;  //in gold pieces
                
   public:
	   bool operator<(Item&);
		Item();
        Item(double, string, string, int);
		  Item(double, string, string, int, double price);
        void setFields(double, string, string, int);
			void setFields(double, string, string, int, double price);
        void display();
        double getWeight();
        string getName();
        void displayDesc();
		string getDesc();
		int getID();
			double getValue();
		void setValue(double price);
};
#endif
