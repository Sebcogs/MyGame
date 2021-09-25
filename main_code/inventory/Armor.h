#ifndef ARMOR_H
#define ARMOR_H
//v4
#include<iostream>
#include<string>
using namespace std;

class Armor: public Item
{
friend ostream& operator<<(ostream&, Armor);
   friend istream& operator>>(istream&, Armor&);
    private:    
        bool equipped;
        int ACmod;       //AC mod
		int maxDexMod;	//max Dex mod that can be used in this armor
        int penalty; 	//is there a penalty??
		char size;
    public:
		Armor();
       // Armor(double, string, string, int, int);
        void setFields(double, string, string,int, int, int, int);
        void display();        
        int getACmod();
        int getPenalty();
        void wield();
        void unwield();
		void setSize(char);
		char getSize();
		void displayLong();
		int getMaxDex();
		bool isEquipped();
		
};
#endif
