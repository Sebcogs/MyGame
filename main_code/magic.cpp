#ifndef MAGIC_CPP
#define MAGIC_CPP
//v4
#include<iostream>
#include <fstream>
#include <vector>
#include<string>
#include<iomanip>
#include<algorithm>
//#include <map>
//#include <unordered_map>
#include "magic.h"
//#include "spell.h"
#include "loadfromDBtemplate.cpp"


using namespace std;

Magic::Magic()
{
     name = "Magic";
    desc = "The list of magic you know and control what you can caste";
    user = "none";
	casterlevel = 1;
	hasMagic = false;
	abilityType = INT;
	abilityTypeStr = "Int";
	//abilityScore = statScore[abilityType];
	for(int i = 0; i<=spellLvlMax; i++)
	{
		maxbylevel[i] = -1;
		availableSlots[i] = -1;
		bonusbylevel[i] = 0;
	}
}

void Magic::bonusSpell() //int mod)	//ability mod, bonus spell slots
{
	resetSpell();
	int mod = abilityMod;
	if(hasMagic)
	{
		for(int i=0;i<=spellLvlMax;i++)
			bonusbylevel[i] = 0;	//reset to zero
		cout<<"=== checking for bonus spells"<<endl;
		int count = mod;
			cout<<"---mod and count = "<<mod<<endl;
		for (count=mod; count>0; count--)
		{
			cout<<"count:"<<count<<" slots:"<<availableSlots[count]<<endl;
			if (availableSlots[count]>=0)
			{
				bonusbylevel[count]++;
				cout<<"  --You have a level "<<count<<" bonus slot"<<endl;
			}
		}
		
		if(mod>=5)
		{
			//cout<<"mod is 5 or more"<<endl;
			//count = mod%4;
			//cout<<mod<<"%4 = "<<count<<endl;
			for (int count = mod%4; count>0; count--)
			{
				//cout<<"count:"<<count<<" slots:"<<availableSlots[count]<<endl;
				if (availableSlots[count]>=0)
				{
				bonusbylevel[count]++;
				cout<<"  --You have another level "<<count<<" bonus slot"<<endl;
				}
				
			}
		}	
	}
	resetSpell();
			
}
int Magic::getmax(int level)
	{
		if(level>=spellLvlMax)
			level = spellLvlMax;
			//cout<<"in getmax() "<<level<<": "<<maxbylevel[level]<<endl;
		return maxbylevel[level];//+bonusbylevel[level];
	} 
int Magic::getSlots(unsigned int level)
	{
		if(level>=spellLvlMax)
		{
			level = spellLvlMax;
		}
		return availableSlots[level];	//+bonusbylevel[level];  already include bonus in reset()
	}
Stats Magic::getAbilitytype()
	{
		return abilityType;
	}
string Magic::getAbilitytypeStr()
{
	return abilityTypeStr;
}
Spell Magic::getSpell(unsigned int indexNum)
	{
		if(indexNum >= knownspellList.size()) 
		{
			cout<<"indexNum is bigger than spell list size, set to 0";
			indexNum = 0;
		}
		return knownspellList.at(indexNum);
	}


	void Magic::outputdata()
	{
		cout<<"Magic: ";
		int size = -1;
		size = getMaxSlotLevel();
		//cout<<"size is "<<size<<endl;
		if( size > -1)
		{
		//cout<< name <<": "<< desc <<endl;
		cout<<"You can use magic as a "<<user<<" with the ability "<<getAbilitytypeStr()<<"."<<endl;
		cout<<"    Available spell slots: "<<endl;
		
			for(int count = 0; count <= size; count++)
			{
				cout.width(7);
				cout<<" level "<<count<<" : ";
				int totalslots = getmax(count)+bonusbylevel[count];
				cout<< getSlots(count)<<" out of "<<totalslots;
				if(bonusbylevel[count] !=0 )
					cout<<" including bonus spells ";
					cout<<endl;
			}
			int known = getNumofKnown();
			if(known>0)
			{
				cout<<"You know "<<known<<" spells."<<endl;
				cout<<"Your known spells:"<<endl;
				for(int i = 0; i<known; i++)
				{
					//cout.width(7);
				knownspellList.at(i).outputData();
				}
			}
		}
			else
				cout<<"You don't know any magic"<<endl;
			
	} 
	void Magic::resetSpell()
	{
		if(hasMagic)
		{
		cout<<"reset Spell max and available"<<endl;
			for(int i = 0; i<=spellLvlMax; i++)
			{
			availableSlots[i]=maxbylevel[i]+bonusbylevel[i];
			}		
		}
	}
	void Magic::addSpell(Spell aspell)
	{
		//check that the spell is for the correct class
		string classStr = aspell.getAvailableClass();
		//cout<<" class Str: "<<classStr<<endl;
		bool foundClass = false;
		for(unsigned int i = 0; i<=classStr.size(); i++)
		{
			if(user[0] == classStr[i])
				foundClass = true;
		}
		if(foundClass)
		{
			string newname = aspell.getName();
			bool alreadyknow =false;
			unsigned int listsize = knownspellList.size();
			//cout<<"List size: "<<listsize<<endl;
		if(listsize>0)
		{
			for(unsigned int y=0; y<listsize; y++)
			{
				//cout<<"   test -- "<<y<<endl;
				Spell temp = knownspellList.at(y);
				string tempname = temp.getName();
				//cout<<"    ---testname: "<<tempname<<endl;
				if( tempname == newname)
					alreadyknow = true;
			}
			if(!alreadyknow)
			{
				knownspellList.push_back(aspell);
			cout<<"Spell -"<<aspell.getName()<<"- added to known list"<<endl;
			}
			else
				cout<<"You already know that one, not added"<<endl;
		}
		else if(listsize == 0)
		{
			knownspellList.push_back(aspell);
			cout<<"Spell added to known list"<<endl;
		}
		}
		else
			cout<<"Spell -"<<aspell.getName()<<"- is not for you"<<endl;
		
	}
	int Magic::getNumofKnown()
	{
		return knownspellList.size();
	}
int Magic::getNumofKnown(int spellLvl)
{
	int sum =0;
	for(int x = 0; x<knownspellList.size(); x++)
	{
		int level = knownspellList.at(x).getLevel();
		if(level == spellLvl)
			sum++;
	}
	return sum;
}
bool Magic::getHasMagic()
{
	return hasMagic;
}
string Magic::getSpellList()
{
		string output;
		sort(knownspellList.begin(), knownspellList.end());
	output = "S: ";
	for(int i = 0; i < getNumofKnown(); ++i)
		 output += to_string(knownspellList[i].getID()) +" ";
	output +='\n';
	return output;
}
void Magic::useSlot(unsigned int level)
{
    availableSlots[level]--;
}
int Magic::getMaxSlotLevel()
{
    int maxLvl = -1;
    for(int i=0; i<spellLvlMax; i++)
		{
			if(maxbylevel[i]>=0)
				maxLvl = i;
		}
        return maxLvl;
}
string Magic::casteableList()
{
    string list;
    //using knownlist for now, some need prepared list instead.
    for(unsigned int index = 0; index < knownspellList.size(); index++)
    {
        string name = knownspellList[index].getName();
        list += to_string(index)+": "+ name+ ".  ";
       // list = list + endl;
    }
    return list;
        
}
void Magic::setAbilityScore(int statScore, int mod)
{
	abilityScore = statScore;
	abilityMod = mod;
		//cout<<"CHECK! The ability score for "<<getAbilitytypeStr()<<" is "<<abilityScore<<endl;
	highestSpellLvl = abilityScore - 10;
	if(highestSpellLvl<0)
	{
		cout<<"Ability score is very low, level 0 spells are all you can get."<<endl;
		highestSpellLvl = 0;
	}
}
int Magic::getDC(int level)
{
	return 10+abilityMod+level;
}

WizMagic::WizMagic() : Magic()
{
	user = "Wizard";
	hasMagic = true;
	desc = "You have a list of spells from which you must prepare some to control and caste";
	abilityType = INT;
	abilityTypeStr = "Int";
	maxbylevel[0] = 3;
	maxbylevel[1] = 1;	
	/*int mod;
		cout<<"check for bonus spells, enter "<<abilityType<<" mod: "<<endl;
		cin>>mod;
		bonusSpell(mod); */
	//known spells: all 0th level , 3 1st level and bonus 1st = int mod
	resetSpell();
	//must make prepared list
	
	//create knownList  WANT TO MOVE TO SEPARATE METHOD TO BE CALLED IN HERO.CPP
	Spell aspell;
	int cantrips[] = {1, 2, 3, 4, 5, 6, 7, 8, 11};
int total = sizeof(cantrips)/sizeof(cantrips[0]);
	//cout<<"Wizard spells loading: array size is "<<total<<endl;
		for(int x=0; x<total; x++)
		{
		getFromDB(aspell, cantrips[x]);
		addSpell(aspell);
		}
//		if(highestSpellLvl >= 1)
//			{
			int firstlevel[] = {31, 15, 30};	//15 burning hands, 32 sleep, 35 hypnotism
			total = sizeof(firstlevel)/sizeof(firstlevel[0]);
			for(int x = 0; x<total; x++)
				{
				getFromDB(aspell,firstlevel[x]);
				addSpell(aspell);
				}
//			}
//		else
//			cout<<"Your ability score is not high enough to learn 1st level Spells!!"<<endl;
}
void WizMagic::levelUp(int lvl)
{
	cout<<"Wizard level up magic"<<endl;	
	unsigned int currentSpLvl;
	unsigned int index;
	for(index = 0; index<=spellLvlMax; index++)
	{
		if(maxbylevel[index] !=-1)
			currentSpLvl = index;
	}
			cout<<"Current max spell level: "<<currentSpLvl<<endl;
		//is level odd or even
		bool isOdd = lvl%2;
			cout<<" is odd? lvl:"<<lvl<<"%2 = "<<isOdd<<endl;
		if(isOdd && highestSpellLvl > currentSpLvl)	//add another spell level
		{
			maxbylevel[currentSpLvl+1] = 1;
		}
			if(!isOdd)
			{
				for(int x=currentSpLvl; x>=0; x--)
				{
					if(maxbylevel[x]!=4)
						maxbylevel[x]++;
				}
			}	
			
		//add spells	
	Spell aSpell, bSpell;
	int spellID, spellID2;
	if(lvl == 2) //new 1st level spell
	{
	spellID = 24;	//20 color spray
	//31 Mage Armour when properly implemented
	spellID2 = 34;	//34 magic missile
	}
	//cout<<"Choose two new spells"<<endl;
	//cout<<"...Still to implement...."<<endl;
getFromDB(aSpell,spellID);
getFromDB(bSpell,spellID2);
	if(highestSpellLvl >= aSpell.getMinLevel())
	{
	addSpell(aSpell);
	addSpell(bSpell);
	}
	else
		cout<<"Your ability score is not high enough to learn those new spells."<<endl;
	
		//resetSpell();
}
RangMagic::RangMagic() : Magic()
{	//create a special bonusSpell() method to bypass 0lvl and add bonus to 1st level slots
	user = "Ranger";
	hasMagic = false;
	desc = "Once you reach level 4 you learn magic.";
	abilityType = WIS;
	abilityTypeStr = "Wis";
	maxbylevel[0] = -1;		//no magic until level 4
	maxbylevel[1] = -1;	//check these numbers
	resetSpell();
}

void RangMagic::levelUp(int lvl)		//this is a bit akward, but the pattern changes
{
		cout<<"Ranger level up magic"<<endl;	//caster level is 1/2 ranger level
	if(lvl == 4)
	{
		hasMagic = true;
		maxbylevel[0] = 0;
		maxbylevel[1] = 0;		//no magic until level 4, start at 1st level	
	//create knownList
	Spell aspell;
	int firstLevel[] = {12, 16, 23, 25};		//25 when implemented    
    int total = sizeof(firstLevel)/sizeof(firstLevel[0]);
	//cout<<"Wizard spells loading: array size is "<<total<<endl;
		for(int x=0; x<total; x++)
		{
		getFromDB(aspell, firstLevel[x]);
		addSpell(aspell);
		}
        	//must make prepared list
	}
	if(hasMagic && lvl != 4)
	{
		unsigned int currentSpLvl = 1;
	unsigned int index;
	for(index = 1; index<=spellLvlMaxRang; index++)
		{
		if(maxbylevel[index] !=-1)
			currentSpLvl = index;       
		}
			cout<<"Current max spell level: "<<currentSpLvl<<endl;
		//is level odd or even
		bool isOdd = lvl%2;
			cout<<" is odd? lvl:"<<lvl<<"%2 = "<<isOdd<<endl;
			
	if(lvl<16)
		{
		if(!isOdd)		//only changes on even levels
			{
			if(currentSpLvl == 4)   //is highest level is 4, rest to level 1 to increase lower level
				currentSpLvl = 1;
			
			if(maxbylevel[currentSpLvl] != 0 )
				{
					//if(currentSpLvl == 4)
				//	maxbylevel[1]++;
				//else
				//{
				if(highestSpellLvl > currentSpLvl)
					maxbylevel[currentSpLvl+1]++;   //add an extra spell level
					if(currentSpLvl == 3 && maxbylevel[4]==0)
						maxbylevel[1]++;
				//}
					
				}
			if(maxbylevel[currentSpLvl] <= 0)
			maxbylevel[currentSpLvl]++;
			}
		if(isOdd && currentSpLvl >=3)
			{
			if(maxbylevel[currentSpLvl] == 0)
				maxbylevel[currentSpLvl]++;
			}
			
			/*if(!isOdd)
			{
				for(int x=currentSpLvl; x>=0; x--)
				{
					//if(maxbylevel[x]!=4)
						maxbylevel[x]++;
				}
			}	*/
		}
		else if(lvl >=16)  //for level above 16
		{
			switch (lvl)
			{
				case 16: 
					maxbylevel[1] = 2;
					maxbylevel[2] = 2;
					maxbylevel[3] = 1;
					maxbylevel[4] = 1;
					break;
				case 17:
					maxbylevel[3] = 2;
					break;
				case 18:
					maxbylevel[1] = 3;
					break;
				case 19:
					maxbylevel[2] = 3;
					maxbylevel[3] = 3;
					maxbylevel[4] = 2;
					break;
				case 20:
					maxbylevel[4] = 3;
					break;
			}
			//add spell level2 at level 8, add spell level3 at level 11
		}
	}
		//resetSpell();	//in charclass levelup
		//bonusSpell();
}
ClerMagic::ClerMagic() : Magic()
{
	user = "Cleric";
	abilityType = WIS;
	abilityTypeStr = "Wis";
	hasMagic = true;
	maxbylevel[0] = 3;		
	maxbylevel[1] = 2;	//check these numbers (technically 1 is domain)
	/*int mod;
		cout<<"check for bonus spells, enter "<<abilityType<<" mod: "<<endl;
		cin>>mod;
		bonusSpell(mod); */
	resetSpell();
	//must make prepared list from all available spells
	//must make prepared list
	
	//create knownList	MOVE TO NEW METHOD TO BE CALLED BY HERO.CPP
	Spell aspell;
	int cantrips[] = {5, 8, 9, 10, 11};
int total = sizeof(cantrips)/sizeof(cantrips[0]);
	//cout<<"Cleric spells loading: array size is "<<total<<endl;
		for(int x=0; x<total; x++)
		{
		getFromDB(aspell, cantrips[x]);
		addSpell(aspell);
		}
//		if(highestSpellLvl>= 1)		
//			{
		int firstlevel[] = {14, 15, 21, 22, 29};
			total = sizeof(firstlevel)/sizeof(firstlevel[0]);
			for(int x = 0; x<total; x++)
			{
			getFromDB(aspell,firstlevel[x]);
			addSpell(aspell);
			}
//			}
//		else
//			cout<<"Your ability score is not high enough to learn 1st level Spells!!"<<endl;
} 
void ClerMagic::levelUp(int lvl)
{
		cout<<"Cleric level up magic"<<endl;	
	unsigned int currentSpLvl;
	unsigned int index;
	for(index = 0; index<=spellLvlMax; index++)
	{
		if(maxbylevel[index] !=-1)
			currentSpLvl = index;
	}
			cout<<"Current max spell level: "<<currentSpLvl<<endl;
		//is level odd or even
		bool isOdd = lvl%2;
			cout<<" is odd? lvl:"<<lvl<<"%2 = "<<isOdd<<endl;
		if(isOdd && highestSpellLvl > currentSpLvl)
		{
			maxbylevel[currentSpLvl+1] = 2;
		}
			if(!isOdd)
			{
				for(int x=currentSpLvl; x>=0; x--)
				{
					//if(maxbylevel[x]!=4)
						maxbylevel[x]++;
				}
			}	
				//resetSpell();
}
BardMagic::BardMagic() : Magic()
{
	user = "Bard";
	hasMagic = true;
	abilityType = CHA;
	abilityTypeStr = "Cha";
	maxbylevel[0] = 2;		//level 2: 0th 3, 1st 0
	
	/*int mod;
		cout<<"check for bonus spells, enter "<<abilityType<<" mod: "<<endl;
		cin>>mod;
		bonusSpell(mod); */
	resetSpell();
	//prepared list is known list
    	//create knownList
	Spell aspell;
	int cantrips[] = {1, 4, 8, 11};
int total = sizeof(cantrips)/sizeof(cantrips[0]);
	//cout<<"Bard spells loading: array size is "<<total<<endl;
		for(int x=0; x<total; x++)
		{
		getFromDB(aspell, cantrips[x]);
		addSpell(aspell);
		}
}
void BardMagic::levelUp(int lvl)
{
		cout<<"Bard level up magic"<<endl;	//see pg29 for spells known
		unsigned int currentSpLvl=0;
		unsigned int index;
		for(index = 0; index<=spellLvlMaxBrd; index++)
			{
			if(maxbylevel[index] !=-1)
				currentSpLvl = index;
			}
		if(lvl<6)
		{
			
			if(maxbylevel[currentSpLvl]>=1 && highestSpellLvl > currentSpLvl)
				maxbylevel[currentSpLvl+1]++;
				for(int i=currentSpLvl; i>=0; i--)
				{
					if(maxbylevel[i]!=3)
				maxbylevel[i]++;
				}
			
				
			
		}
		else if(lvl<14)
		{
			
			if(maxbylevel[currentSpLvl]>=2 && highestSpellLvl > currentSpLvl)
				maxbylevel[currentSpLvl+1]++;
			else if(maxbylevel[currentSpLvl]!=3)
			{
				if(highestSpellLvl > currentSpLvl)
					maxbylevel[currentSpLvl]++;
				if(maxbylevel[currentSpLvl-1]!=3)
				{
					maxbylevel[currentSpLvl-1]++;
				}
			}
		}
		
		else	//lvl more that 14
		{
			if(maxbylevel[currentSpLvl]>=2 && currentSpLvl != spellLvlMaxBrd && highestSpellLvl > currentSpLvl)
				maxbylevel[currentSpLvl+1]++;
			else if(maxbylevel[currentSpLvl]!=3)
			{
				maxbylevel[currentSpLvl]++;
				if(maxbylevel[currentSpLvl-1]!=3)
				{
					maxbylevel[currentSpLvl-1]++;
				}
			}
				int slot4th = lvl%14;
					cout<<lvl<<"%14 = "<<slot4th<<endl;
					if(slot4th<=spellLvlMaxBrd && maxbylevel[slot4th]!=4)
						maxbylevel[slot4th]++;
			
				
		}
			//resetSpell();
}
GnomMagic::GnomMagic() : Magic()
{
	user = "Gnome";
	hasMagic = true;
	abilityType = CHA;	//if char>=10 1/d
	abilityTypeStr = "Cha";
		maxbylevel[0]=1;	//speak with animals lv 1, should be lv0
		Spell aspell;
		getFromDB(aspell, 12);	
        aspell.setSpellLvl(0);
		addSpell(aspell);
        
		/*int mod;
		cout<<"check for bonus spells, enter "<<abilityType<<" mod: "<<endl;
		cin>>mod;
		bonusSpell(mod); */
		
		resetSpell();
		
}
void GnomMagic::levelUp(int lvl)
{
	
}

void GnomMagic::bonusSpell()
{
	int mod = abilityMod;
	//cout<<"====check for bonus gnome spells===="<<endl;
	if(mod>0)
		{
		maxbylevel[1] = 3;
		cout<<"  --You get 3 bonus Gnome spells!"<<endl;
		Spell aspell, bspell, cspell;
		getFromDB(aspell, 1);	//actually should be level 1
		getFromDB(bspell, 3);	//actually should be level 1
		getFromDB(cspell, 7);	//actually should be level 1
        aspell.setSpellLvl(1);
        bspell.setSpellLvl(1);
        cspell.setSpellLvl(1);
        addSpell(aspell);
		addSpell(bspell);
		addSpell(cspell);
		}
	resetSpell();
}
Magic * MagicCreator::getMagic()
	{
		
		unsigned int type;
    cout <<"Choose a Type: 0 for Wizard, 1 for Ranger, 2 for Cleric, 3 for Bard and 4 for gnome";  
			cout<<endl;
			cin >> type;
			switch(type) {
		case 0:
			return new WizMagic;
			break;
		case 1:
			return new RangMagic;
			break;
		case 2:
			return new ClerMagic;
			break;
		case 3:
			return new BardMagic;
			break;
		case 4:
			return new GnomMagic;
			break;
		default:
			cout <<"invalid input, you will be human by dafault."<<endl;
			return new Magic;
			}
	}

#endif