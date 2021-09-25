#pragma once
#ifndef SpecialAtk_H
#define SpecialAtk_H

#include<iostream>
#include<string>
#include <map>
#include "Stats.h"


using namespace std;
enum specialType {GENERIC = 0, POISON, FEAR, SLEEP, ILLUSION, ENCHANTMENT};
const static int SPECIAL_TYPE_NUMBER = 6;
extern map<specialType, string> create_SpecialsMap();


class SpecialAtk
{
private:
       string name;     //poison, paralysis, etc
        int dC;      //DC to avoid special attack
        Saves save = NONE;  //fort, will, reflex...
        int atk;         //if different from normal atk
        int duration;   //dice 1dDuration
        int frequency = 1;  //frequency of special use. 0; every atk, 1; 1st atk, 2; random
        int range = 1;
        unsigned effectCode = 0;
        specialType specialtype = GENERIC;
        bool includeDmg;
public:
    SpecialAtk();
    ~SpecialAtk();
    void setFields(string name, int DC, Saves save, int atk, int dur, int freq);
    int getDC();
    int getAtk();
    int getDuration();
    Saves getSaveType();
    string getSpecialName();
    int getFreq();
    unsigned getEffectCode();
    specialType getType();
    bool getIncludeDmg();
};

#endif