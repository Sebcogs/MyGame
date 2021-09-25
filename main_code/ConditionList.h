#pragma once
#ifndef CONDITIONLIST_H
#define CONDITIONLIST_H

#include<iostream>
#include<string>
#include<vector>
#include "Condition.h"
using namespace std;

class ConditionList  //Vector of different conditions but maybe this is better to track the condition bits and durations...
{
private:
	
	vector<unsigned> conditionlist;  //bits
	vector<int> durations; //times for each conditionlist
	vector<int> immunities;	//positive effects
	vector<int> immunDurations;
public:
	//Condition condition;
	ConditionList();
	~ConditionList();
	string showConditions();
	void addCondition(unsigned condition);  //not sure about this...
	void removeCondition();  //this should be done in update or reset
	void reset();
	void update();

};

#endif