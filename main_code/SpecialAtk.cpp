#include "SpecialAtk.h"
using namespace std;
//{GENERIC = 0, POISON, FEAR, SLEEP, ILLUSION, ENCHANTMENT}

map<specialType, string> create_SpecialsMap()
{
	map<specialType, string> s;
	s[GENERIC] = "GENERIC";
	s[POISON] = "POISON";
	s[FEAR] = "FEAR";
	s[SLEEP] = "SLEEP";
	s[ILLUSION] = "ILLUSION";
	s[ENCHANTMENT]  = "ENCHANTMENT";
	return s;
}

SpecialAtk::SpecialAtk()
{
    name = "none";     //poison, paralysis, etc
    dC = 0;      //DC to avoid special attack
    save = NONE;  //fort, will, reflex...
    atk = 0;         //if different from normal atk
    duration = 0;
    frequency = 1;  //frequency of special use. 0; every atk, 1; 1st atk, 2; random
    range = 1;
    includeDmg = true;
}

SpecialAtk::~SpecialAtk()
{
}

    void SpecialAtk::setFields(string i_name, int i_DC, Saves i_save, int i_atk, int i_dur, int i_freq)
    {   //Specialname>>DC>>save>>atk>>dur>>freq
//    cout<<"Loading monster special with name: "<<i_name<<endl;
        name = i_name;
        dC = i_DC;
        save = i_save;
        atk = i_atk;
        duration = i_dur;
        frequency = i_freq;
        range = 1;
        if(name == "poison")     //is it better to make derived classes??
        {
            effectCode = 256;
            specialtype = POISON;
            includeDmg = true;
        }
        else if(name == "shriek" || name == "paralysis")
        {
            if(name == "shriek")
            {
                range = 10;
                includeDmg = false;
            }
            effectCode = 64;
            specialtype = FEAR;
        }
    }
    int SpecialAtk::getDC()
    {
        return dC;
    }
    int SpecialAtk::getAtk()
    {
        return atk;
    }
    int SpecialAtk::getDuration()
    {
        return duration;
    }
    Saves SpecialAtk::getSaveType()
    {
        return save;
    }
    string SpecialAtk::getSpecialName()
    {
        return name;
    }
    int SpecialAtk::getFreq()
    {
        return frequency;
    }
unsigned SpecialAtk::getEffectCode()
{
    return effectCode;
}
specialType SpecialAtk::getType()
{
    return specialtype;
}
bool SpecialAtk::getIncludeDmg()
{
    return includeDmg;
}