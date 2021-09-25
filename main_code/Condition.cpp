#include<iostream>
#include "Condition.h"

using namespace std;
Condition::Condition()
{
	
	status = "Normal";
	idNum = 10;
	isBlind=0;
	isCharmed=0;	//dazzled  (charmed won't attack...)
	isDeafended=0;
	isFrightened=0;	//cowering, confused...
	isGrappled=0;
	isInvisible=0;
	isParalyzed=0;
	isPetrified=0;
	isPoisoned=0;
	isProne=0;
	isRestrained=0;
	isStunned=0;	//dazed no action but no AC penalty
	isUnconscious=0;  //same as asleep...?
	isResistant=0;
	isAtkBonus=0;
	isACBonus = 0;
	isDmgBonus = 0;
	isHaste = 0;
}

Condition::~Condition()
{
}

unsigned Condition::getCondition()
{
	/*unsigned temp;
	temp = isBlind * 1
	+ isCharmed * 2
	+ isDeafended * 4       -4 on initiative, 20% spell failure, fail listen check
	+ isFrightened * 8      -2 on atk, save, run away
	+ isGrappled * 16
	+ isInvisible * 32
	+ isParalyzed * 64
	+ isPetrified * 128
	+ isPoisoned * 256
	+ isProne * 512
	+ isRestrained * 1024
	+ isStunned * 2048
	+ isUnconscious * 4096
	+ isResistant * 8192
	+ isAtkBonus *  16384
	+ isACBonus	*	32768
	+ isDmgBonus *	65536
	+ isHaste * 131072
	 return temp; */
	int* temp = &idNum;
	++temp;
	return *temp;
}
	bool Condition::getIsNormal()
	{
		return isNormal;
	}
	bool Condition::getIsHelpless()
	{
		return isHelpless;
	}
	bool Condition::getIsIncap()
	{
		return isIncapacitated;
	}
	void Condition::setCondition(int bitvalue)
	{
		//reset values 
            status = "";
			atkmod = 0;
			speedmod = 0;
			dmgmod = 0;
			ACmeleemod = 0;
			ACrangemod = 0;
			saveThrowmod = 0;
            for(int i =STR; i<=CHA; i++)
                statMod[i] = 0;
                
		if(bitvalue != 0)
		{
			isNormal = false;
			status = "Abnormal status: ";
		}
		else
		{
			isNormal = true;
			isIncapacitated = false;
			isHelpless = false;
			status = "Normal";
			
		}
		int* p;
		p = &idNum;
		++p;
		*p = bitvalue;
		//6336 is incapacitated
		//4288 is helpless and incapacitated
		if(bitvalue & helplessBit)
		{
			isIncapacitated = true;
			isHelpless = true;
			status = status + " -helpless and incapacitated";
			atkmod = -100;
			ACmeleemod = -4;
			ACrangemod = 0;
            statMod[DEX] = -5;
			speedmod = -10;
		}
        if(bitvalue & 64)   //paralyzed (part of helpless)
            status = status + " -paralyzed";
		if(bitvalue & 2048)	//stunned or dazed
		{
			isIncapacitated = true;
			isHelpless = false;
			status =status + " -incapacitated, possibly stunned";
			atkmod = -100;
			ACmeleemod = -2;
			ACrangemod = -2;
            statMod[DEX] = -2;
		}
		if(bitvalue & 2)	//Charmed or dazzled
		{
			atkmod=-1;
			ACmeleemod =0;
			ACrangemod = 0;
			status = status + " -charmed or dazzled";
		}
		if(bitvalue & 1024) //restrained/entangled
		{
			atkmod = -2;
			ACmeleemod = 0;
			ACrangemod = 0; //Dex -4 penalty
            statMod[DEX] = -2;
            status = status + " -restrained or entangled";
			speedmod = -10;
		}
		if(bitvalue & 1)	//blinded
		{
			ACmeleemod = -2;
			ACrangemod = -2;
			status = status + " -blinded and can't see";
		}
		if(bitvalue & 32)	//invisible
		{
			atkmod = 2;
			ACmeleemod = 0;
			ACrangemod = 0;
			status = status + " -invisible!";
		}
		if(bitvalue & 8)	//frightened/cowering/distracted won't target enemy properly
		{
			atkmod = -2;
			ACmeleemod = -2;
			ACrangemod = -2;
            saveThrowmod = -2;
			status = status + " -scared or distracted";
		}
		if(bitvalue & 8192)	//resistance improved
		{
			saveThrowmod = 1;
			status = status + " -resistance improved";
		}
		if(bitvalue & 16384)
		{
			atkmod = 1;
			status = status + " -attack improved (+" + to_string(atkmod) + " atk)";
		}
        if(bitvalue & 256)      //poisoned
        {
            atkmod = -2;
            statMod[STR] = -2;
            statMod[DEX] = -1;
            status = status + " -poisoned (atk, str, and dex decreased).";
        }
		if(bitvalue & 32768)		//AC bonus
			{
				ACmeleemod = 1;
				ACrangemod = 1;
				status = status + " -AC improved (+" + to_string(ACmeleemod) + " AC)";
			}
			if(bitvalue & 65536)		//dmg bonus
			{
				dmgmod = 1;
				status = status + " -Dmg improved (+" + to_string(dmgmod) + " dmg)";
			}
			if(bitvalue & 131072)	//speed adjust 5ft increments
			{
				speedmod = 1;
				status = status + " -Speed improved (+" + to_string(speedmod) + "x5ft)";
			}
			cout<<status<<endl;
	}
	void Condition::setCondition(int bitvalue, int mod)
	{
		if(mod == 1)
		{	
				setCondition(bitvalue);
		}	
		else
		{
			//reset values 
                status = "";
			atkmod = 0;
			speedmod = 0;
			dmgmod = 0;
			ACmeleemod = 0;
			ACrangemod = 0;
			saveThrowmod = 0;
            for(int i =STR; i<=CHA; i++)
                statMod[i] = 0;
                
			if(bitvalue != 0)
			{
			isNormal = false;
			status = "Abnormal status: ";
			}
			else
			{
			isNormal = true;
			isIncapacitated = false;
			isHelpless = false;
			status = "Normal";
			
			}
			int* p;
			p = &idNum;
			++p;
			*p = bitvalue;
		
			if(bitvalue & 8192)	//resistance improved
			{
			saveThrowmod = mod;
			status = status + " resistance improved";
			}
			if(bitvalue & 16384)
			{
			atkmod = mod;
			status = status + " attack improved (+" + to_string(atkmod) + " atk";
			}
			if(bitvalue & 32768)		//AC bonus
			{
				ACmeleemod = mod;
				ACrangemod = mod;
				status = status + " AC improved (+" + to_string(ACmeleemod) + " AC)";
			}
			if(bitvalue & 65536)		//dmg bonus
			{
				dmgmod = mod;
				status = status + " Dmg improved (+" + to_string(ACmeleemod) + " dmg)";
			}
			if(bitvalue & 131072)	//speed adjust 5ft increments
			{
				speedmod = mod;
				status = status + " Speed improved (+" + to_string(speedmod) + "x5ft)";
			}
		}
				cout<<status<<endl;
	}
	string Condition::getStatus()
	{
        string temp;
        if(numRounds > 0)
            temp = status + " for " + to_string(numRounds) + " rounds.";
		return temp;
	}
	int Condition::getAtkMod()
	{
		return atkmod;
	}
	int Condition::getACMeleeMod()
	{
		return ACmeleemod;
	}
	int Condition::getACRangeMod()
	{
		return ACrangemod;
	}
	int Condition::getSaveMod()
	{
		return saveThrowmod;
	}
	int Condition::getDmgMod()
	{
		return dmgmod;
	}
	int Condition::getSpeedMod()
	{
		return speedmod;
	}
    void Condition::setDuration(int rounds)
    {
        numRounds = rounds;
    }
    void Condition::update()
    {
        //after each round adjust numRounds if there is a non-normal condition.
        if(numRounds != 0)
            numRounds--;
        if(numRounds <= 0)
        {
            setCondition(0);
            numRounds = 0;
        }
    }
    int Condition::getStatMod(int index)
    {
        if(index <0 || index >= statNumber)
        {
            cout<<"Error, index wrong in Condition getStatMod() returning 0."<<endl;
            return 0;
        }
        return statMod[index];
    }