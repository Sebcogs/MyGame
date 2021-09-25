#ifndef SPELL_CPP
#define SPELL_CPP

#include<iostream>
#include<string>
#include<iomanip>

#include "spell.h"

//enum Schools {Univ = 0, Abju, Conj, Divi, Ench, Evoc, Illu, Necro, Tran};
//enum Component {None = 0, Verb, Soma, Mate};
//enum SpellType {Effect = 0, Attack, Heal};
using namespace std;

map<Schools, string> create_Schoolmap()
{
	map<Schools, string> s;
	s[Univ] = "Universal";
	s[Abju] = "Abjuration";
	s[Conj] = "Conjuration";
	s[Divi] = "Divination";
	s[Ench] = "Enchantment"; 
	s[Evoc] = "Evocation";
	s[Illu] = "Illusion";
	s[Necro] = "Necromancy";
	s[Tran] = "Transmutation";
	return s;
}

ostream& operator<<(ostream& out, const Spell& aspell)
{
	out<<aspell.idNum<< " " <<aspell.name<< " " << aspell.school <<" "
	<<aspell.level<<" " <<aspell.casteTime << " " << aspell.duration<< " "
	<<aspell.range<< " " <<aspell.spellType<< " " << aspell.component[0]<< " "
	<<aspell.component[1]<<" "<<aspell.component[2]<< " " <<aspell.effectCode
	<<" "<<aspell.availableClass<<" "<<aspell.area<<" "<<aspell.saveType<<" "
    <<aspell.saveEffect<<" "<<aspell.hasTouch<<" "<<" "<<aspell.oD_type<<" "<<" "<<aspell.effectMod<<" "<<aspell.desc<<endl;
	return out;
}
istream& operator>>(istream& in, Spell& aspell)
{
	int idn, lvl, ctime, dur, ran, effmod;
	string n, des;
	Schools scEnum;
	int sc, sTy, ar, saveTy, touch;
    float saveEf;
	SpellType sTyEnum;
	Component compEnum[3] = {None};
	int comp[3];
	unsigned code;
	string user;
    char odtype;
	
	in >> idn >> n >> sc >> lvl>>ctime>>dur>>ran>>sTy>>comp[0]>>comp[1]>>comp[2]>>code>>user>>ar>>saveTy>>saveEf>>touch>>odtype>>effmod;
	getline(in, des);
	//cout<<n<<" loaded!"<<endl;
	scEnum = aspell.intToSchool(sc);
	sTyEnum = aspell.intToSpellType(sTy);
	for(int i=0; i<=2; i++)
	{
		//cout<<"int to Comp #"<<i<<endl;
		compEnum[i] = aspell.intToComponent(comp[i]);
	}
	aspell.idNum = idn;
	aspell.name = n;
	aspell.desc = des;
	aspell.school = scEnum;
    aspell.minlevel = lvl;
	aspell.level = lvl;
	aspell.casteTime = ctime;
	aspell.duration = dur;
	aspell.range = ran;
	aspell.spellType = sTyEnum;
	for(int x=0; x<=2; x++)
	{
		//cout<<"loading component into spell, #"<<x<<endl;
		aspell.component[x] = compEnum[x];
	}
	if(sTy == 1 || sTy == 2)
	{
		//cout<<" sTy = "<<sTy<<" loading effectdice."<<code<<endl;
		aspell.effectDice = code;
        //cout<<"effectDice is "<<aspell.getEffectDice()<<endl;
		code = 0;
	}
	aspell.effectCode = code;
	aspell.effectMod = effmod;
	aspell.availableClass = user;
	aspell.area = ar;
    aspell.hasTouch = touch;
    switch(saveTy){
        case 0:
        aspell.saveType = FORT;
        break;
        case 1:
        aspell.saveType = REF;
        break;
        case 2:
        aspell.saveType = WIL;
        break;
        case 3:
        aspell.saveType = NONE;
        break;
        default:
        aspell.saveType = NONE;
    }
    aspell.saveEffect = saveEf;
	if(ar == 0)
		aspell.isSingleTarget = true;
		else
			aspell.isSingleTarget = false;
        aspell.oD_type = aspell.charToOD(odtype);    
        
	return in;
}

Spell::Spell()
{
	setMap();
	idNum=0;
	name = "Presidigitation";
	desc = "A simple trick to impress people.";
	school = Univ;
	casteTime = 1;
	duration = 60;
	range = 2;	//10ft so 2 squares.
	isSingleTarget = false;
	area = 2;	//2squares area or 10ft2
	level = 0;
	spellType = Effect;
	component[0] = Verb;
	component[1] = Soma;
	effectCode = 8;
	availableClass = "BWG";  //bard, wizard, gnome
}
Spell::Spell(string n, Schools sch, SpellType spellty)
{
	setMap();
	name = n;
	school = sch;
	spellType = spellty;
	duration = 0;
	range = 0;
	casteTime = 1;
	cout<<"Create a spell "<<getName()<<endl;
	cout<<"Add spell data.."<<endl;
	if(spellType == Attack)
	{
		cout<<"Attack spell, enter min range in squares: ";
		cin>>range;
		cout<<"enter damage dice: ";
		cin>>effectDice;
		cout<<"Enter area of effect in #5ft squares, or 0 for single target: ";
		cin>>area;
		if(area == 0)
			isSingleTarget = true;
			else
				isSingleTarget = false;
		//cout<<endl;
	}
	if(spellType == Heal)
	{
		range = 0;
		cout<<"Heal spell, enter heal dice: ";
		cin>>effectDice;
		cout<<endl;
	}
	
}
void Spell::setMap()
{
	Schoolmap = create_Schoolmap();
}
bool Spell::operator<(Spell& aspell)
{
	return(level < aspell.level); 
}
	string Spell::getName()
	{
		return name;
	}
	string Spell::getSchool(Schools key)
	{
		return Schoolmap.find(key) -> second;
	}
	void Spell::outputData()
	{
		string typeStr;
		switch(spellType) {
			case Effect:
				typeStr = "Effect";
				break;
			case Attack:
				typeStr = "Attack";
				break;
			case Heal:
				typeStr = "Heal";
				break;
			default:
				typeStr = "unknown";
		}
		string temp = getSchool(school);
		//cout.width(7);
		cout<<"  - "<<name<<"- lvl: "<<level<<", "<<typeStr<<", school: "<<temp;
        if(typeStr == "Attack")
            cout<<" with damage = "<<effectDice<<endl;
        else
            cout<<" with effect code "<<effectCode<<endl;
	}
	string Spell::getAvailableClass()
	{
		return availableClass;
	}
unsigned Spell::getEffectCode()
{
	return effectCode;
}
int Spell::getEffectMod()
{
	return effectMod;
}
Schools Spell::intToSchool(int i)
	{
		Schools scEnum;
		switch (i){
		case 0:
			scEnum = Univ;
			break;
		case 1:
			scEnum = Abju;
			break;
		case 2:
			scEnum = Conj;
			break;
		case 3:
			scEnum = Divi;
			break;
		case 4:
			scEnum = Ench;
			break;
		case 5:
			scEnum = Evoc;
			break;
		case 6:
			scEnum = Illu;
			break;
		case 7:
			scEnum = Necro;
			break;
		case 8:
			scEnum = Tran;
			break;
		default:
			scEnum = Univ;
		}
	return scEnum;
	}
Component Spell::intToComponent(int i)
	{
		Component scEnum;
		switch (i){
		case 0:
			scEnum = None;
			break;
		case 1:
			scEnum = Verb;
			break;
		case 2:
			scEnum = Soma;
			break;
		case 3:
			scEnum = Mate;
			break;
		case 4:
			scEnum = Focu;
			break;
		default:
			scEnum = None;
		}
		return scEnum;
	}
SpellType Spell::intToSpellType(int i)
	{
		SpellType scEnum;
		switch (i){
		case 0:
			scEnum = Effect;
			break;
		case 1:
			scEnum = Attack;
			break;
		case 2:
			scEnum = Heal;
			break;
		default:
			scEnum = Effect;
		}
	return scEnum;
	}
void Spell::setSpellLvl(int lv)
{
    //cout<<"changing spell level from "<<level<<" to "<<lv<<endl;
	if(lv < minlevel)
	{
		lv = minlevel;
		cout<<"level is lower than minimum spell level, set to min level"<<endl;
	}
		
	level = lv;
	if(level >=5)
		level = 5;
	if(range>0)
		range = range + range/10*(level-minlevel);
		
		duration = duration * (1+level-minlevel);    //duration per level
		if(spellType != Heal)
		effectDice = effectDice *(1+level-minlevel); //damage is 1d(dice) per level
}
int Spell::getID()
{
	return idNum;
}
SpellType Spell::getEffectType()
{
    return spellType;
}
int Spell::getEffectDice()
{
    return effectDice;
}
bool Spell::getIsSingleTarget()
{
    return isSingleTarget;
}
int Spell::getRange()
{
    return range;
}
int Spell::getMinLevel()
{
    return minlevel;
}
int Spell::getLevel()
{
    return level;
}
Saves Spell::getSaveType()
{
    return saveType;
}
float Spell::getSaveEffect()
{
    return saveEffect;
}
bool Spell::getHasTouch()
{
    return hasTouch;
}
int Spell::getDuration()
{
    return duration;
}
offOrDef Spell::getOD()
{
    return oD_type;
}
offOrDef Spell::charToOD(char input)
{
    offOrDef type;
    switch(input){
        case 'o':
            type = OFFENSE;
            break;
        case 'd':
            type = DEFENSE;
            break;
        default:
            type = OFFENSE;
    }
        return type;
}
int Spell::getArea()
{
	return area;
}
#endif