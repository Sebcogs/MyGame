#ifndef EQUIP_H
#define EQUIP_H
//v4
#include<iostream>

using namespace std;

class Equip
	{
		private:  //assign equipment inventory vector poisitions, -1 for empty
		static const int EMPTY = -1;			
			int body;	//a place to equip armor
			int hand;	//the primary hand to hold a weapon
			int offhand;	//either offhand weapon or shield
			bool isShield; //true if offhand has a shield
			int twohand;	//if using two handed weapon
			bool isRange;
			
		public:
			Equip();
			bool setBody(int);
			bool setHand(int);
			bool setOffHand(int, bool);	//armor or weapon position, bool true for shield
			bool set2Hand(int);
			int getBodyPosition();
			int getHandPosition();
			int getOffHandPosition();
			int get2HandPosition();
			bool getIsShield();
			bool hasBody();
			bool hasHand();
			bool has2Hand();
			bool hasOffHand();
			void setRange(bool);
			bool hasRange();
			
};
#endif
