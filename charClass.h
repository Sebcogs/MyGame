#ifndef CHARCLASS_H
#define CHARCLASS_H
//v4
#include<iostream>
#include<string>
#include <map>
//#include <unordered_map>

using namespace std;
class charClass
{
   private:
        string className;  
        int hitDice;     
        int Atk;
        int saveThrow[3];
    string saveThrowName[3]; // = {"FORT", "REFLEX", "WILL"};
       
   public:
       charClass();  //set all mod to 0
	enum Styles {BARB=0, BARD, FIGH, CLER, RANG};
			map<string, Styles> styles;
        enum Saves {FORT=0, REF, WIL};
			map<Saves, string> saves;
		void setMap();
        void setFields(Styles);
		void setFields(string);
     void setFields();
		Styles getStyle(string);
		Saves getSaves(string);
        void outputData();
        int getAtk();
        int getHitDice();
		string getClassName();
		void levelUp(int); 
        int getSaveThrow(int);   
		string getSaveName(unsigned int);    
}; 
#endif
