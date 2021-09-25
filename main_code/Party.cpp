#ifndef PARTY_CPP
#define PARTY_CPP
//v4
#include<iostream>
#include<string>
#include<vector>
#include "Party.h"
//#include "Hero.h"
//#include "Actor.h"
//#include "Race.h"


using namespace std;
Party::Party(string names[], int size)
{
	//cout <<"Adding Heros to the party"<<endl;
	//marchingOrder.clear();
	memberNumber = size;
	//Actor& hero[memberNumber];
	for(int i=0;i<memberNumber; i++)
		{
	//	cout << " Hero : "<<names[i] <<" added to party" <<endl;
		marchingOrder.push_back(names[i]);
		}
}

string Party::getMarchingOrderStr()
{
		string temp = "The Marching order is : ";	
	for(int i=0;i<memberNumber; i++)
	{
	temp = temp + "#" + to_string(i+1) +"-" + marchingOrder.at(i) +" ";
	}
	//temp = temp + "\n";
	return temp;
}

void Party::displayHeroNames()
{
	cout <<"Heros are: ";
	for(int i=0;i<memberNumber; i++)
	{
	cout<<"#"<<i+1<<"-"<<marchingOrder.at(i)<<" "; //getPartyMembers();
	}
	cout <<endl;
}
void Party::displayHeroNames(int exclude)
{
        if(exclude+1 > marchingOrder.size())
        {
            cout<<"Problem, player number is bigger then number of PCs."<<endl;
            exclude = 0;
        }
    cout<<"You are "<<getHero(exclude+1)<<endl;
	cout <<"The other heros are: ";
	for(int i=0;i<memberNumber; i++)
	{
        if(i != exclude)
	cout<<"#"<<i+1<<"-"<<marchingOrder.at(i)<<" "; //getPartyMembers();
	}
	cout <<endl;
}
	
void Party::setMarchingOrder()
{
		const string MSG = "input error";	
	int choice;
	cout << "Choose the marching order of heros"<<endl;
	displayHeroNames();
	cout<<endl<< "enter the associated Hero number in the desired order "<<endl;
	vector<string> oldmarchingorder = marchingOrder;
	for(int i = 0; i<memberNumber; i++)
		{
		cout <<i+1<<" position: ";
		cin >>choice;
		if(choice<1)
			throw(MSG);
		if(choice>memberNumber+1)
			throw(MSG);
		
		marchingOrder.at(i) = oldmarchingorder.at(choice-1);
		}
	cout <<"Marching Order set."<<endl;
	cout <<"Order is : "<<getMarchingOrderStr()<<endl;
}

string Party::getHero(int position)
{
	//cout <<getMarchingOrderStr();
//	cout <<"will use hero at position "<<position<<endl;

	return marchingOrder.at(position-1);
} 

int Party::heroPosition(string name)
{
	int position;
	for(int i=0; i<memberNumber; i++)
	{
		if(marchingOrder.at(i) == name)
			position = i+1;
	}
	return position;
}
int Party::getMemberNumber()
{
	return memberNumber;
}
int Party::whichPartyMember()	
{
		const string MSG = "input error";	
	int numberofHeros = getMemberNumber();
	int heroNumber;
	if(numberofHeros == 1)
  				heroNumber = 1;
		else {
			displayHeroNames();
			cout <<"Choose the corresponding hero number";
			cout<<" from 1 to "<<numberofHeros<<": ";
				cin>>heroNumber;
		if(heroNumber<1)
			throw(MSG);
		if(heroNumber>numberofHeros)
			throw(MSG);
			}
	return heroNumber;
}
int Party::whichPartyMember(int exclude)
{
		const string MSG = "input error";	
	int numberofHeros = getMemberNumber();
	int heroNumber;
	if(numberofHeros == 1)
  				heroNumber = 1;
		else {
                cout<<"Enter displayHeroNames(exclude)..."<<endl;
			displayHeroNames(exclude);
			cout <<"Choose the corresponding hero number";
			cout<<" from 1 to "<<numberofHeros<<", but exclude "<<exclude+1<<": ";
				cin>>heroNumber;
		if(heroNumber<1)
			throw(MSG);
		if(heroNumber>numberofHeros || heroNumber == exclude+1)
			throw(MSG);
			}
	return heroNumber-1;
}
	
#endif
