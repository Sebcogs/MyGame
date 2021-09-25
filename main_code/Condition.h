#ifndef CONDITION_H
#define CONDITION_H

#include<iostream>
#include<string>
#include<vector>
#include "Stats.h"
using namespace std;
class Condition
{
	const static int totalBitStates = 18;
	const static unsigned helplessBit = 4288;
	//const static unsigned incapBit = 6336;
private:
	bool isIncapacitated = false;
	bool isHelpless = false;
	bool isNormal = true;
	string status;
	int atkmod = 0, dmgmod = 0, speedmod = 0;
    int numRounds = 0;  //number of rounds for the effect to last
	int ACmeleemod = 0, ACrangemod = 0, saveThrowmod = 0, statMod[statNumber] = {0};
	int idNum;	//just a place holder to start the bit address 
	unsigned isBlind:1;
	unsigned isCharmed:1;
	unsigned isDeafended:1;
	unsigned isFrightened:1;
	unsigned isGrappled:1;
	unsigned isInvisible:1;
	unsigned isParalyzed:1;
	unsigned isPetrified:1;
	unsigned isPoisoned:1;
	unsigned isProne:1;
	unsigned isRestrained:1;
	unsigned isStunned:1;
	unsigned isUnconscious:1;
	unsigned isResistant:1;
	unsigned isAtkBonus:1;
	unsigned isACBonus:1;
	unsigned isDmgBonus:1;
	unsigned isHaste:1;
	
	
public:
	Condition();
	~Condition();
	unsigned getCondition();  //converts bit to int
	bool getIsNormal();
	bool getIsIncap();
	bool getIsHelpless();
	void setCondition(int bitvalue);  //converts int to bit code
	void setCondition(int bitvalue, int mod);	//in case the adjustment mod maybe larger than default
	string getStatus();
	int getAtkMod();
	int getACMeleeMod();
	int getACRangeMod();
	int getSaveMod();
    int getStatMod(int index);
	int getDmgMod();
	int getSpeedMod();
    void setDuration(int rounds);
    void update();      //each round, count down length of condition.

};

#endif // CONDITION_H
