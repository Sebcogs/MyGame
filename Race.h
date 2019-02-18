#ifndef RACE_H
#define RACE_H
//v4
#include<iostream>
#include<string>
#include <map>
//#include <unordered_map>
#include <iterator>
#include "Ability.h"
//#include "Stats.h"


using namespace std;
class Race
{
   private:
       const static int statNumber = 6;
        string raceName;
        char size;
        int mod[statNumber];
		Ability stats;
   public:
       Race();  //set all mod to 0
		// ~Race();
        enum Races {HUM=0, ELF, DWA, HAF};
			map<string, Races> races;
		void setMap();
		void setFields();
        void setFields(Races);
      void setFields(string);
        void outputData();
        int getMod(int);
        char getSize();
		int getRaceIndex();
		int getsizeMod();
		Races getRace(string);
		string getRaceName();
}; 
#endif
