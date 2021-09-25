#ifndef WEAPON_H
#define WEAPON_H
//v4
#include<iostream>
#include<string>
using namespace std;

class Weapon: public Item
{
friend ostream& operator<<(ostream&, Weapon);
   friend istream& operator>>(istream&, Weapon&);
    private:    
        bool equipped;
        int die;            //damage dice
        int dieMultiple;    //mutlipleDdie
        int minCrit;
        int critMultiple;
		char size;
		int range;
		
    public:
		Weapon();
       // Weapon(double, string, string, int, int, int, int);
        void setFields(double weigh, string name, string desc, int dice, int mult, int crit, int critDmg, int id, int range);
        void display();        
        int getDie();
        int getDieMultiple();
        int getminCrit();
        int getCritMultiple();
        void wield();
        void unwield();
		void setSize(char);
		char getSize();
		void displayLong();
		bool isEquipped();
		int getRange();
		
		        
};
#endif
