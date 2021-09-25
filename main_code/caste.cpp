#include<string>
#include "caste.h"

using namespace std;

Caste::Caste(Hero* attack)	//call Caste* caste = new Caste(&champ);
{
		isOffence = false;	//use offensively, check against spell off/def type
	this->attacker = attack;
	this->defender = NULL;
	this->receiver = attack;
	//aspell = NULL;
	classMagic =true;
	raceMagic = false;
	hasAreaEffect = false;
	distance = -1;
	cout<<"Attacker is "<<attacker->getName()<<endl;
	cout<<"Receiver is "<<receiver->getName()<<endl;
	//chooseMagicType();		//use race or class magic  Most be Class magic
	chooseSpell();		//choose spell
}
Caste::Caste(Hero* attack, Monster* defend, int dis)	//call with Caste* caste = new Caste(&champ, &amonster, 2);
{
	isOffence = true;	//use offensively, check against spell off/def type
	this->attacker = attack;
	this->defender = defend;
	this->receiver = NULL;
	//aspell = NULL;
	classMagic =false;
	raceMagic = false;
	hasAreaEffect = false;
	//isOffence = false;
	distance = dis;
	cout<<"Attacker is "<<attacker->getName()<<endl;
	cout<<"Defender is "<<defender->getName()<<endl;
	
	chooseMagicType();		//use race or class magic
	if(classMagic || raceMagic)
	chooseSpell();		//choose spell
}
Caste::Caste(Hero* attack, Hero* receive, int dis)
{		isOffence = false;	//use offensively, check against spell off/def type
	this->attacker = attack;
	this->defender = NULL;
	this->receiver = receive;
	//aspell = NULL;
	classMagic =attacker->getHasMagic();
	raceMagic = false;
	hasAreaEffect = false;
	distance = dis;
	cout<<"Attacker is "<<attacker->getName()<<endl;
	cout<<"Receiver is "<<receiver->getName()<<endl;
	//chooseMagicType();		//use race or class magic  Most be Class magic
	if(classMagic)
		chooseSpell();		//choose spell
}
Caste::~Caste()
{
	       if(classMagic)
            attacker->myClass->classmagic->useSlot(aspell.getLevel());
        else if(raceMagic)
            attacker->myRace->racemagic->useSlot(aspell.getLevel());
	attacker = NULL;
	defender = NULL;
	receiver = NULL;
	cout<<"Caste destructor; all set to null."<<endl;
}
void Caste::chooseMagicType()
{
	   cout<<"+++ chooseMagicType function+++"<<endl;
     if(attacker->getHasMagic() == 'b')
        {
            cout<<"Do you want to use your race or class magic? Enter R for Race and C for Class."<<endl;
            char choice;
            cin>>choice;
            if(choice == 'r' || choice == 'R')
                raceMagic = true;
            else if(choice == 'c' || choice == 'C')
                classMagic = true;
            else
            {
                cout<<"invalid entry, will use class magic"<<endl;
                classMagic = true;
            }
        }
        else if(attacker->getHasMagic() == 'c')
            classMagic = true;
        else if(attacker->getHasMagic() == 'r')
            raceMagic = true;
			
				
}
void Caste::chooseSpell()
{
	   cout<<"+++ chooseSpell function +++"<<endl;
	   if(defender!=NULL)
		   cout<<"Choose an attack spell"<<endl;
		if(receiver!=NULL)
			cout<<"Choose a defensive spell"<<endl;
//    Spell aspell;
    int maxSpellLvl, maxId;
    string spellList;
	bool success = false; 	//used to choose a spell that will work
	bool exit = false;		//used to exit caste (ie if enemy is out of range, etc
	while(!success)
	{
		if(raceMagic)
            {
                maxSpellLvl = attacker->myRace->racemagic->getMaxSlotLevel();
                spellList = attacker->myRace->racemagic->casteableList();
                maxId = attacker->myRace->racemagic->getNumofKnown();
            }
		else if(classMagic)
            {
                maxSpellLvl = attacker->myClass->classmagic->getMaxSlotLevel();
                spellList = attacker->myClass->classmagic->casteableList();
                maxId = attacker->myClass->classmagic->getNumofKnown();
            }
		int m_spellId;
        cout<<"What spell to caste? chose the ID number next to the desired spell, or -1 to exit"<<endl;
        cout<<spellList;
			try  //not catching wrong type error properly
			{
            cin>>m_spellId;
            //throw(m_spellId);
			}
			catch(...)
			{
                cout<<"Error not valid, setting to first spell."<<endl;
                m_spellId = 1;
			}
        if(m_spellId>maxId)
            m_spellId = 1;
			else if(m_spellId <= -1)
			{
				cout<<"exit caste."<<endl;
				classMagic = false;
				raceMagic = false;
				success = true;
				exit = true;
				//break;
				//return 0;
			}
        if(classMagic)
			aspell = attacker->myClass->classmagic->getSpell(m_spellId);
        else if(raceMagic)
           aspell = attacker->myRace->racemagic->getSpell(m_spellId);
		   
		healUndead = false;

		if(defender!=NULL && !exit)
		{
			if(aspell.getEffectType() == Heal && defender->getType() == UNDEAD)
			{
			healUndead = true;
			cout<<"You caste a healing spell to damage an undead monster"<<endl;
			}
        
			if(aspell.getOD() == OFFENSE || healUndead == true)
			{ 
            //cout<<"You can caste spell "<<aspell.getName()<<" as level "<<to_string(aspell.getLevel())<<endl;
            success = checkRange();
			}    
			else
			{
           cout<<"You can't caste a defensive spell against an enemy"<<endl;
			}
		}
		else if(receiver!=NULL && !exit)
		{
			if(aspell.getOD() == DEFENSE || healUndead == false)
			{ 
            //cout<<"You can caste spell "<<aspell.getName()<<" as level "<<to_string(aspell.getLevel())<<endl;
            success = checkRange();
			}    
			else
			{
           cout<<"You can't caste a offensive spell against a friend"<<endl;
			}
		}
		else
			cout<<"Error, can't choose offensive against an enemy and can't choose defensive for a friend!"<<endl;
	}	//end while loop
        if(!exit)
		{
    int m_spellLvl;
        cout<<"You have max slot level of "<<maxSpellLvl<<endl;
        cout<<"Which level slot to use?  Enter between "<<aspell.getMinLevel()<<" and "<<maxSpellLvl<<endl;
        try     //not catching wrong type error properly
        {
            cin>>m_spellLvl;
           // throw(m_spellLvl);
            if(m_spellLvl>maxSpellLvl)
                throw(m_spellLvl);
        /*    else if(m_spellLvl< aspell.getMinLevel())
                m_spellLvl = aspell.getMinLevel(); */  //done in spell method
        }
        
        catch(...)
        {
                cout<<"Error not valid, setting to max level spell slot."<<endl;
                m_spellLvl = maxSpellLvl;
        }
        
        //aspell.setCasterLvl(m_spellLvl);
        aspell.setSpellLvl(m_spellLvl);
		hasAreaEffect = !aspell.getIsSingleTarget();
        aspell.outputData(); 
		}
}
int Caste::getSaveDC()
{
	int DC;
	if(raceMagic)
		DC = attacker->myRace->racemagic->getDC(aspell.getLevel());
	else if(classMagic)
		DC = attacker->myClass->classmagic->getDC(aspell.getLevel());
	else
	{
		cout<<"Error, in Caste::getSaveDC. neither race or class magic"<<endl;
		DC = 10;
	}
	return DC;
}
bool Caste::checkRange()
{
	    bool success = false;
    int range = aspell.getRange();
    if(distance <= (1*range) && range > 1)
    {
        cout <<"Range Spell attack"<< endl;	
        cout<<"Spell range is "<<range<<" and target is "<<distance<<" away."<<endl;
        success = true;
    }
    else if(range <= 1 && distance <= range)
    {
        cout<<"melee Spell attack"<< endl;
        cout<<"Spell range is "<<range<<" and target is "<<distance<<" away."<<endl;
        success = true;
    }
	else if(range == -1 && distance == -1)
	{
		cout<<"Caste on self"<<endl;
		success = true;
	}
    else
        cout <<"You are out of range. Maximum distance of spell is "<<1*range<<" but the target is "<<distance<<"away. Try something else"<<endl;

    return success;
}
bool Caste::checkSpellHit()
{
	int hitRoll = 1;    //incase there is no touch attack roll, the spell will hit
	int MonsterAC = 0;
        if(aspell.getHasTouch())
        {
            hitRoll = attacker->rangeRoll();	//some spells have touch (range) attack
            MonsterAC = defender->getTouchAC(); 
            cout<<" Your touch attack roll of "<<hitRoll<<" vs opponents touch AC of "<<MonsterAC<<endl;
       
        }
        if(hitRoll >= MonsterAC)
            return true;
        else
            return false;
}
float Caste::getSpellSaveMod()
{
	float dmgMod = 1.0;
	//bool success = false;   //if save succeeds
    int saveDC, saveRoll;
          Saves saveType = aspell.getSaveType();
        if(saveType != NONE)
        { 
       saveDC = getSaveDC();
        
        Dice d20(1,20);
        int d20roll = d20.getValue();
        saveRoll = d20roll + defender->getSaveThrow(saveType);
        cout<<saveDC<<" DC, save Roll of "<<d20roll<<" + saving throw = "<<saveRoll<<endl; 
            if(saveRoll > saveDC)
            {
                //success = true;
            dmgMod = aspell.getSaveEffect();
            cout<<defender->getName()<<" succeeded on saving throw, damage is adjusted by "<<dmgMod<<endl;
            }      
        }   
    return dmgMod;
}
bool Caste::casteSpell()
{
	if(!classMagic && !raceMagic)
		return false;
	else
	{
	if(defender!=NULL)
	{
	bool isHit = checkSpellHit();
	if(isHit)
		{		
	float dmgMod = getSpellSaveMod();
	int dmgCrit = 1;
	   if(attacker->getCrit())
            {
                cout<<"Your spell makes a critical hit! Damage is doubled"<<endl;
                dmgCrit = 2;
            } 
	
		cout <<" You hit the monster "<< defender->getName() <<"! "<<endl;
        if(aspell.getEffectType() == Attack || healUndead == true)     //damage
            {
                cout<<" an attack spell, getting damage..."<<endl;
            int dmg = aspell.getEffectDice();
                cout<<"damage dice is "<<dmg<<endl;
            Dice dice(1,dmg);
            int dmgRoll = dice.getValue();
            cout <<" Damage for "<<dmgRoll<<" with mod from saving throw of "<<dmgMod<<endl;
            defender->receiveDamage(dmgRoll*dmgMod*dmgCrit);
            }
        else if(aspell.getEffectType() == Effect)     //effect
            {
                if(dmgMod!=0)
				{
                defender->condition.setCondition(aspell.getEffectCode(), aspell.getEffectMod());
                defender->condition.setDuration(aspell.getDuration()*dmgMod);    //save effects duration
				}
            }
        else 
            {
            cout<<"Error, what is the other case? Heal spell when not on undead..."<<endl;
            }
 
		}

    else
            cout<<"Your spell misses the target"<<endl;
			
	}
	else if(receiver!=NULL)
	{
		       if(aspell.getEffectType() == Heal)     //damage
            {
             //   cout<<" an healing spell, getting healing hp..."<<endl;
            int dmg = aspell.getEffectDice();
                cout<<"healing dice is "<<aspell.getMinLevel()<<"d"<<dmg<<"+"<<aspell.getLevel()<<endl;
            Dice dice(aspell.getMinLevel(),dmg);
            int dmgRoll = dice.getValue() + aspell.getLevel();	
            cout <<" Heal for "<<dmgRoll<<endl;
            receiver->receiveHealing(dmgRoll); //*dmgMod*dmgCrit);
				cout<<"done"<<endl;
            }
        else if(aspell.getEffectType() == Effect)     //effect
            {
		receiver->condition.setCondition(aspell.getEffectCode(), aspell.getEffectMod());
		receiver->condition.setDuration(aspell.getDuration());
			}
			else
				cout<<"Error, How can you caste neither heal nor effect against friend?"<<endl;
	}
	else
		cout<<"In casteSpell, why neither defender or receiver?"<<endl;
			
			if(hasAreaEffect)
				cout<<"Has area effect! To implement later"<<endl;

		//do this after checking for area effect  -move to destructor
 /*       if(classMagic)
            attacker->myClass->classmagic->useSlot(aspell.getLevel());
        else if(raceMagic)
            attacker->myRace->racemagic->useSlot(aspell.getLevel());
			 */
		return true;
	}
}
int Caste::getAreaRange()
{
	int area;
	if(aspell.getIsSingleTarget())
		area = 0;
	else
		area = aspell.getArea();
	return area;
}
void Caste::setNextTarget(Monster* defender)
{
	this->defender = defender;
}
void Caste::setNextTarget(Hero* receiver)
{
	this->receiver = receiver;
}

/*
//functions not part of class.  To be removed when class functions properly
//
Spell caste(Hero& attacker, Monster& defender, int distance, bool& success)  //, Spell aspell)  //returns spell to check for area effect
{  
	success = false;
	int hitRoll, range, DC; 
    string statName;
	bool useRaceMagic = false;
    bool useClassMagic = false;
    bool healUndead = false;
    Spell aspell;
    int MonsterAC;
    Saves saveType;     //Fort, Ref, Will
    float dmgMod = 1.0;     //effect from successful save
    int dmgCrit = 1;
    
		cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
if(attacker.getHasMagic()!= 'n')    //has magic and can caste
    {
    chooseMagicType(attacker, useClassMagic, useRaceMagic);
    aspell = chooseSpell(attacker, useClassMagic, useRaceMagic, statName);
    range = aspell.getRange();
    saveType = aspell.getSaveType();

    if(aspell.getEffectType() == Heal && defender.getType() == UNDEAD)
        {
        healUndead = true;
        cout<<"You caste a healing spell to damage an undead monster"<<endl;
        }
        
       if(aspell.getOD() == OFFENSE || healUndead == true)
       { 
            cout<<"You caste spell "<<aspell.getName()<<" as level "<<to_string(aspell.getLevel())<<endl;
            success = checkRange(range, distance);
        }    
       else
       {
           cout<<"You can't caste a defensive spell against an enemy"<<endl;
       }
    bool spellHit = false;  //used to check if touch attack succeeds
    bool spellSave = false; //used to check if save throw is succeeds
	if(success)	
	{
        spellHit = checkSpellHit(attacker, defender, aspell, hitRoll, MonsterAC, dmgCrit);
        if(useClassMagic)
		DC = attacker.myClass->classmagic->getDC(aspell.getLevel());
		else
			DC = attacker.myRace->racemagic->getDC(aspell.getLevel());
        spellSave = checkSpellSave(attacker, defender, aspell, DC, saveType, dmgMod);



//		cout << "hitRoll "<< hitRoll << " vs monster AC " <<MonsterAC<<endl;
	if(spellHit)
		{		
   
		cout <<" You hit the monster "<< defender.getName() <<"! "<<endl;
        if(aspell.getEffectType() == Attack || healUndead == true)     //damage
            {
                cout<<" an attack spell, getting damage..."<<endl;
            int dmg = aspell.getEffectDice();
                cout<<"damage dice is "<<dmg<<endl;
            Dice dice(1,dmg);
            int dmgRoll = dice.getValue();
            cout <<" Damage for "<<dmgRoll<<" with mod from saving throw of "<<dmgMod<<endl;
            defender.receiveDamage(dmgRoll*dmgMod*dmgCrit);
            }
        else if(aspell.getEffectType() == Effect)     //effect
            {
                
                defender.condition.setCondition(aspell.getEffectCode());
                defender.condition.setDuration(aspell.getDuration()*dmgMod);    //save effects duration
            }
        else 
            {
            cout<<"Error, what is the other case? Heal spell when not on undead..."<<endl;
            }
 
		}

    else
            cout<<"Your spell misses the target"<<endl;
	
        if(useClassMagic)
            attacker.myClass->classmagic->useSlot(aspell.getLevel());
        else if(useRaceMagic)
            attacker.myRace->racemagic->useSlot(aspell.getLevel());
    }
    else if(!success)
        cout<<"You fail to caste the spell, but you don't lose the available spell slot."<<endl;
    }
    else
        cout<<"You don't know magic and can't caste anything"<<endl;
        
            return aspell;
       
}

bool caste(Hero& attacker, Hero& defender, int distance)  //caste a defensive spell on a fellow hero
{  
	bool success = false;
	int range; //, maxSpellLvl, maxId;
    string statName;
	bool useRaceMagic = false;
    bool useClassMagic = false;
    Spell aspell;
    
		cout <<attacker.getName() << " is casting a spell on "<<defender.getName()<<"."<<endl;
if(attacker.getHasMagic()!= 'n')    //has magic and can caste
    {
        chooseMagicType(attacker, useClassMagic, useRaceMagic);
        aspell = chooseSpell(attacker, useClassMagic, useRaceMagic, statName);
           
        range = aspell.getRange();        
   
       if(aspell.getOD() == DEFENSE)
       { 
            cout<<"You caste spell "<<aspell.getName()<<" as level "<<to_string(aspell.getLevel())<<endl;
            success = checkRange(range, distance);
       }
       else
       {
           cout<<"You can't caste a offensive spell against a friend"<<endl;
       }

	if(success)	
	{

        if(aspell.getEffectType() == Heal)     //damage
            {
                cout<<" an healing spell, getting healing hp..."<<endl;
            int dmg = aspell.getEffectDice();
                cout<<"healing dice is "<<aspell.getMinLevel()<<"d"<<dmg<<"+"<<aspell.getLevel()<<endl;
            Dice dice(aspell.getMinLevel(),dmg);
            int dmgRoll = dice.getValue() + aspell.getLevel();	
            cout <<" Heal for "<<dmgRoll<<endl;
            defender.receiveHealing(dmgRoll); //*dmgMod*dmgCrit);
            }
        else if(aspell.getEffectType() == Effect)     //effect
            {
                defender.condition.setCondition(aspell.getEffectCode(), aspell.getEffectMod());
                defender.condition.setDuration(aspell.getDuration());
            }
        else //if(aspell.getEffectType() == Attack)
            {
            cout<<"Error, this attack spell should not be allowed"<<endl;
            }

 //   else
 //           cout<<"Your spell misses the target"<<endl;
	
        if(useClassMagic)
            attacker.myClass->classmagic->useSlot(aspell.getLevel());
        else if(useRaceMagic)
            attacker.myRace->racemagic->useSlot(aspell.getLevel());
    }
    else if(!success)
        cout<<"You fail to caste the spell, but you don't lose the available spell slot."<<endl;
    }
    else
        cout<<"You don't know magic and can't caste anything"<<endl;
        
	return success;
}

bool caste(Hero& attacker, Monster& defender, int distance, Spell& aspell)  //for area, true is spell can be used
{  //throwAt(champ[player], aMonster, dis, athrown);
	bool success = false;
	int hitRoll, range, DC; //, maxSpellLvl, maxId;
    string statName;
    bool healUndead = false;
    int MonsterAC;
    Saves saveType;     //Fort, Ref, Will
    float dmgMod = 1.0;     //effect from successful save
    int dmgCrit = 1;
    
		cout <<attacker.getName() << " is attacking "<<defender.getName()<<"."<<endl;
           
        range = aspell.getRange();
        saveType = aspell.getSaveType();

    if(aspell.getEffectType() == Heal && defender.getType() == UNDEAD)
        {
        healUndead = true;
        cout<<"You caste a healing spell to damage an undead monster"<<endl;
        }
        
       if(aspell.getOD() == OFFENSE || healUndead == true)
       { 
            cout<<"You caste spell "<<aspell.getName()<<" as level "<<to_string(aspell.getLevel())<<endl;
            success = checkRange(range, distance);
       }
       else
       {
           cout<<"You can't caste a defensive spell against an enemy"<<endl;
       }

   bool spellHit = false;  //used to check if touch attack succeeds
       bool spellSave = false; //used to check if save throw is succeeds
	if(success)	
        {
        spellHit = checkSpellHit(attacker, defender, aspell, hitRoll, MonsterAC, dmgCrit);
		//	if(useClassMagic)	//how to determine if this was from class or race??
				DC = attacker.myClass->classmagic->getDC(aspell.getLevel());
		//	else
		//	DC = attacker.myRace->racemagic->getDC(aspell.getLevel());
        spellSave = checkSpellSave(attacker, defender, aspell, DC, saveType, dmgMod);

        if(spellHit)
            {
   
            cout <<" You hit the monster "<< defender.getName() <<"! "<<endl;
            if(aspell.getEffectType() == Attack || healUndead == true)     //damage
                {
                cout<<" an attack spell, getting damage..."<<endl;
            int dmg = aspell.getEffectDice();
                cout<<"damage dice is "<<dmg<<endl;
            Dice dice(1,dmg);
            int dmgRoll = dice.getValue();
            cout <<" Damage for "<<dmgRoll<<" with mod from saving throw of "<<dmgMod<<endl;
            defender.receiveDamage(dmgRoll*dmgMod*dmgCrit);
                }
            if(aspell.getEffectType() == Effect)     //effect
                {
                
                defender.condition.setCondition(aspell.getEffectCode());
                defender.condition.setDuration(aspell.getDuration()*dmgMod);    //save effects duration
                }
            else
                {
                cout<<"Error, whats the other case.. Healing spell?.."<<endl;
                }
            }
        else
            cout<<"Your spell misses the target"<<endl;
        }
    else if(!success)
        cout<<"You fail to caste the spell for some reason."<<endl;

	return success;
}

void chooseMagicType(Hero& attacker, bool& useClassMagic, bool& useRaceMagic)
{
    cout<<"+++ chooseMagicType function+++"<<endl;
     if(attacker.getHasMagic() == 'b')
        {
            cout<<"Do you want to use your race or class magic? Enter R for Race and C for Class."<<endl;
            char choice;
            cin>>choice;
            if(choice == 'r' || choice == 'R')
                useRaceMagic = true;
            else if(choice == 'c' || choice == 'C')
                useClassMagic = true;
            else
            {
                cout<<"invalid entry, will use class magic"<<endl;
                useClassMagic = true;
            }
            
        }
        else if(attacker.getHasMagic() == 'c')
            useClassMagic = true;
        else if(attacker.getHasMagic() == 'r')
            useRaceMagic = true;
}

Spell chooseSpell(Hero& attacker, bool useClassMagic, bool useRaceMagic, string& statName)
{
    cout<<"+++ chooseSpell function +++"<<endl;
    Spell aspell;
    int maxSpellLvl, maxId;
    string spellList;
    
   if(useRaceMagic)
            {
                maxSpellLvl = attacker.myRace->racemagic->getMaxSlotLevel();
                spellList = attacker.myRace->racemagic->casteableList();
                maxId = attacker.myRace->racemagic->getNumofKnown();
                statName = attacker.myRace->racemagic->getAbilitytype();
            }
            else if(useClassMagic)
            {
                maxSpellLvl = attacker.myClass->classmagic->getMaxSlotLevel();
                spellList = attacker.myClass->classmagic->casteableList();
                maxId = attacker.myClass->classmagic->getNumofKnown();
                statName = attacker.myClass->classmagic->getAbilitytype();
            }
    int m_spellId;
        cout<<"What spell to caste? chose the ID number next to the desired spell"<<endl;
        cout<<spellList;
        try  //not catching wrong type error properly
        {
            cin>>m_spellId;
            //throw(m_spellId);
        }
        
        catch(...)
        {
                cout<<"Error not valid, setting to first spell."<<endl;
                m_spellId = 1;
        }
        if(m_spellId>maxId)
            m_spellId = 1;
        if(useClassMagic)
        {
           // attacker.myClass->classmagic->getSpell(m_spellId).outputData();
          //  cout<<"press a button to continue ";
          //  int blank;
          //  cin>>blank;
            aspell = attacker.myClass->classmagic->getSpell(m_spellId);
            
        }
        else if(useRaceMagic)
           aspell = attacker.myRace->racemagic->getSpell(m_spellId);
        
    int m_spellLvl;
        cout<<"You have max slot level of "<<maxSpellLvl<<endl;
        cout<<"Which level slot to use?  Enter between "<<aspell.getMinLevel()<<" and "<<maxSpellLvl<<endl;
        try     //not catching wrong type error properly
        {
            cin>>m_spellLvl;
           // throw(m_spellLvl);
            if(m_spellLvl>maxSpellLvl)
                throw(m_spellLvl);
            else if(m_spellLvl< aspell.getMinLevel())
                m_spellLvl = aspell.getMinLevel();
        }
        
        catch(...)
        {
                cout<<"Error not valid, setting to max level spell slot."<<endl;
                m_spellLvl = maxSpellLvl;
        }
        
        //aspell.setCasterLvl(m_spellLvl);
        aspell.setSpellLvl(m_spellLvl);
        aspell.outputData();  
        
        return aspell;
}

int getSaveDC(Hero& attacker, Spell aspell, string statName)
{
    cout<<"+++ getSaveDC function +++"<<endl;
        int statMod, saveDC;
        //    cout<<"Looking for stat: "<<statName<<endl;
        for(int y = STR; y<=CHA; y++)
        {
         //   cout<<"index y: "<<y<<" with statname: "<<attacker.getStatName(y);
            if(attacker.getStatName(y) == statName)
            {
                statMod = attacker.getMod(y);
             //   cout<<", Found!"<<" with mod: "<<statMod;
            }
               // cout<<endl;
        }
        saveDC = 10 + aspell.getLevel() + statMod;
        cout<<"Saving throw DC to avoid spell is 10+"<<aspell.getLevel()<<"+"<<statMod<<" ="<<saveDC<<endl;
        
        return saveDC;
}

bool checkSpellHit(Hero& attacker, Monster& defender, Spell& aspell, int& hitRoll, int& MonsterAC, int& dmgCrit)
{
    hitRoll = 1;    //incase there is no touch attack roll, the spell will hit
        MonsterAC = 0;
        if(aspell.getHasTouch())
        {
            hitRoll = attacker.rangeRoll();	//some spells have touch (range) attack
            MonsterAC = defender.getTouchAC(); 
            cout<<" Your touch attack roll of "<<hitRoll<<" vs opponents touch AC of "<<MonsterAC<<endl;
            if(attacker.getCrit())
            {
                cout<<"Your spell makes a critical hit! Damage is doubled"<<endl;
                dmgCrit = 2;
            }
        }
        if(hitRoll >= MonsterAC)
            return true;
        else
            return false;
}
bool checkRange(int range, int distance)
{
    bool success = false;
    
    if(distance < (1*range) && range > 1)
    {
        cout <<"Range Spell attack"<< endl;	
        cout<<"Spell range is "<<range<<" and enemy is "<<distance<<" away."<<endl;
        success = true;
    }
    else if(range == 1 && distance == 1)
    {
        cout<<"melee Spell attack"<< endl;
        cout<<"Spell range is "<<range<<" and enemy is "<<distance<<" away."<<endl;
        success = true;
    }
    else
        cout <<"You are out of range. Maximum distance of spell is "<<1*range<<" but the monster is "<<distance<<"away. Try something else"<<endl;

    return success;
}

bool checkSpellSave(Hero& attacker, Monster& defender, Spell aspell, int DC, Saves saveType, float& dmgMod)
{
    bool success = false;   //if save succeeds
    int saveDC, saveRoll;
          
        if(aspell.getSaveType() != NONE)
        { 
       // saveDC = getSaveDC(attacker, aspell, statName);
	   saveDC = DC;
        
        Dice d20(1,20);
        int d20roll = d20.getValue();
        saveRoll = d20roll + defender.getSaveThrow(saveType);
        cout<<saveDC<<" DC, save Roll of "<<d20roll<<" + saving throw = "<<saveRoll<<endl; 
            if(saveRoll > saveDC)
            {
                success = true;
            dmgMod = aspell.getSaveEffect();
            cout<<defender.getName()<<" succeeded on saving throw, damage is adjusted by "<<dmgMod<<endl;
            }      
        }   
    return success;
}
 * */
bool checkSpellSave(Monster& attacker, Hero& defender)  //against monster special atk
{
    cout<<"Check save throw against attack DC."<<endl;
    bool success = false;   //if save succeeds
    int saveDC, saveRoll;
          Saves saveType = attacker.getSpecialSaveType();
        if(saveType != NONE)
        { 
        saveDC = attacker.getSpecialDC();
        
        Dice d20(1,20);
        int d20roll = d20.getValue();
        int savethrow = defender.getSaveThrow(saveType, attacker.getSpecialType());
        string savename = defender.aSavethrow.getSaveName(saveType);
        saveRoll = d20roll +  savethrow;  //overload to include specialType from monster
        cout<<saveDC<<" DC vs "<<savename<<" save Roll of "<<d20roll<<" + saving throw "<<savethrow<<" = "<<saveRoll<<endl; 
            if(saveRoll > saveDC)
            {
                success = true;
            //dmgMod = aspell.getSaveEffect();
            cout<<defender.getName()<<" succeeded on saving throw, negated."<<endl;
            }      
        }   
    return success;
}
