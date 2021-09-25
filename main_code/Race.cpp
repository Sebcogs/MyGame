#ifndef RACE_CPP
#define RACE_CPP
//v4
#include <iostream>
#include <string>
#include <map>
//#include <unordered_map>
#include <iterator>
#include "Race.h"

using namespace std;
map<Races, string> create_Racesmap()
{
	map<Races, string> r;
	r[HUM] = "Human";
	r[ELF] = "Elf";
	r[DWA] = "Dwarf";
	r[HAF] = "Halfling";
	r[GNO] = "Gnome";
	return r;
}
map<string, Races> create_RaceStringmap()
{
	map<string, Races> rS;
	rS["Human"] = HUM;
	rS["Elf"] = ELF;
	rS["Dwarf"] = DWA;
	rS["Halfling"] = HAF;
	rS["Gnome"] = GNO;
	return rS;
}

Race::Race()
{
raceName = "Human";
for(int count=0; count<statNumber; count++)
    mod[count] = 0;
	size = 'm';
	setMap();
	for(int x = FORT; x<=NONE; ++x)
	{
		raceSaveBonus[x]=0;
	}
	for(int y = 0; y<=SPECIAL_TYPE_NUMBER; ++y)
	{
		specialAtksaves[y] = 0;
	}
	//racemagic = new Magic();
}
/* Race::~Race()
{
	//delete only works for pointer ? destructor kind of pointless in this case...	
	//delete raceName;
	//delete size;
	//delete mod[];
	//delete raceIndex;
} */
void Race::setMap()
{
	races = create_RaceStringmap();
	/*races["Human"] = HUM;
	races["Elf"] = ELF;
	races["Dwarf"] = DWA;
	races["Halfling"] = HAF; */

}

void Race::outputData()
{
    cout<< "You are: " << raceName << " and are size: "<<size <<endl;
	//racemagic->outputdata();
}

int Race::getMod(int stat)
{
    return mod[stat];
}
char Race::getSize()
{
    return size;
}

int Race::getsizeMod()
{
	int mod;
	if(getSize() == 's')
		mod = 1;
	else
		mod=0;
	return mod;
}
Races Race::getRace(string input)
{
	return races.find(input) -> second;
}
string Race::getRaceName()
{
	return raceName;
}
monsterType Race::getFavouredEnemy(int index)
{
    if(index <0 || index > MAX_ENEMY-1)
    {
        cout<<"Error in favoured Enemy index, set to first element (0)"<<endl;
        index = 0;
    }
    return favouredEnemy[index];       
}
monsterType Race::getDodgeEnemy(int index)
{
    if(index <0 || index > MAX_ENEMY-1)
    {
        cout<<"Error in dodge Enemy index, set to first element (0)"<<endl;
        index = 0;
    }
    return dodgeEnemy[index];
} 
void Race::addFavouredEnemy(monsterType amonster)
{
    int place =-1;  //location of fist non-NotMonster index
    for(int index = 0; index < MAX_ENEMY; place++)
    {
        if(favouredEnemy[index]==NOTMonster)
        {
            place = index;
            index = MAX_ENEMY;
        }            
    }
    if(place < 0)
        {
            cout<<"You can't add another favoured enemy, you already have 3"<<endl;
        }
    else
        {
            favouredEnemy[place] = amonster;
           cout<<"You gain advanced offensive fighting against this type of enemy, this will give you +1 atk roll."<<endl;

        }
}
void Race::addDodgeEnemy(monsterType amonster)
{
   int place =-1;  //location of fist non-NotMonster index
    for(int index = 0; index < MAX_ENEMY; place++)
    {
        if(dodgeEnemy[index]==NOTMonster)
        {
            place = index;
            index = MAX_ENEMY;
        }            
    }
    if(place < 0)
        {
            cout<<"You can't add another dodge enemy, you already have 3"<<endl;
        }
    else
        {
            dodgeEnemy[place] = amonster;
            cout<<"You gain advanced defensive fighting against this type of enemy, this will give you +4 dodge AC."<<endl;
        }    
}
int Race::getMaxFavoured()
{
    return MAX_ENEMY;
}
int Race::getRaceSave(Saves save)
{
	return raceSaveBonus[save];
}
int Race::getSpecialSave(int special)
{
	return specialAtksaves[special];
}

Human::Human() : Race()
{
	raceName = "Human";
        //    raceIndex = 0;
            size = 'm';
			racemagic = new Magic();
           // favouredEnemy = {-1,-1,-1};
}

Elf::Elf() : Race()
{
	 raceName = "Elf";
         //   raceIndex = 1;
            size = 'm';
            mod[DEX] = 2;
            mod[CON] = -2;
			racemagic = new Magic();
            //favouredEnemy = {-1,-1,-1};
			specialAtksaves[SLEEP] = 100;	//immune to sleep
			specialAtksaves[ENCHANTMENT] = 2;	//+2 to enchantment
}

Dwarf::Dwarf() : Race()
{
	raceName = "Dwarf";
         //   raceIndex = 2;
            size = 'm';
            mod[CON] = 2;
            mod[CHA] = -2;
			racemagic = new Magic();
            favouredEnemy[0] = ORC;
            favouredEnemy[1] = GOBLIN;
            dodgeEnemy[0] = GIANT;   //also troll and ogre
}

Halfling::Halfling() : Race()
{
	raceName = "Halfling";
          //  raceIndex = 3;
            size = 's';
            mod[DEX] = 2;
            mod[STR] = -2;
			racemagic = new Magic();
			for(int x=FORT; x<=WIL; x++)
				raceSaveBonus[x] = 1;	//get a bonus to saving throws
				specialAtksaves[FEAR] = 2;	//+2 against fear, plus +1 usual bonus
}
Gnome::Gnome() : Race()
{
	raceName = "Gnome";
          //  raceIndex = 3;
            size = 's';
            mod[CON] = 2;
            mod[STR] = -2;
			//GnomMagic temp;
			//racemagic = &temp;
			racemagic = new GnomMagic();
            favouredEnemy[0] = KOBOLD;
            favouredEnemy[1] = GOBLIN;
            dodgeEnemy[0] = GIANT;   //also troll and ogre
			specialAtksaves[ILLUSION] = 2;	//+2 against Illusions
}
void Gnome::outputData()
{
	cout<<"Gnome output"<<endl;
    cout<< "You are: " << raceName << " and are size: "<<size <<endl;
	racemagic->outputdata();
}
Race * RaceCreator::getRace(string choice)
	{
	map<string, Races > races = create_RaceStringmap();
	
		unsigned int type;
		type = races.find(choice) ->second; 
		Race *temp = getRace(type);
		return temp;
			  
	} 
Race * RaceCreator::getRace()
	{
		map<Races, string > races = create_Racesmap();
	
		unsigned int type;
    cout <<"Choose a Race";  
			cout<<endl;

    cout<<"Don't forget the racial modes:"<<endl;
	cout<<" Elf->Dex+2,Con-2; Dwarf->Con+2,CHar-2; Halfling->Dex+2,STR-2; Gnome->Con+2,STR-2;  "<<endl;
	int x = 0;
map<Races, string>::iterator it = races.begin();
	// Iterate over the map using Iterator till end.
	while (it != races.end())
	{	
		string word = it->second;  // Accessing KEY from element pointed by it.
		int place = it->first;
 		cout << ", #"<<place<<": "<< word ;
		x++;
		it++;
		}
		cout<<": ";

   cin >> type;
	//Race *temp = getRace(type);
		
			//return temp;
			return getRace(type);
	}
Race * RaceCreator::getRace(unsigned int type)
	{
		//cout<<"Type is: "<<type<<"."<<endl;
		switch(type) {
		case 0:
			return new Human;
			break;
		case 1:
			return new Elf;
			break;
		case 2:
			return new Dwarf;
			break;
		case 3:
			return new Halfling;
			break;
		case 4:
			return new Gnome;
			break;
		default:
			cout <<"invalid input, you will be human by dafault."<<endl;
			return new Human;
			}
	}
#endif


