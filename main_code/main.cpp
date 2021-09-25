#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <unistd.h>		//for usleep()
//#include "magic.h"
//#include "Condition.h"
//#include "Actor.h"
//#include "Race.h"
//#include "charClass.h"
#include "Hero.h"
#include "Monster.h"
#include "caste.h"
#include "loadfromDBtemplate.cpp"
#include "SaveThrow.h"
//#include "Combatant.h"
#include "Initiative.h"
#include "TurnUndead.h"


using namespace std;

void createHeros(Hero& champ);
int load(Hero& myHero);
void save(Hero myHero);
//Spell caste(Hero& attacker, Monster& defender, int distance);  //returns spell used so can check for area effect
//Spell caste(Hero& attacker, Monster& defender, int distance, Spell& aspell);  //area effect
//bool caste(Hero& attacker, Hero& defender, int distance);
//Spell caste(Hero& attacker, Monster& defender, int distance,  bool& success);
//bool caste(Hero& attacker, Hero& defender, int distance);
//bool caste(Hero& attacker, Monster& defender, int distance, Spell& aspell);

bool fight(Hero& attacker, Monster& defender, int distance);
bool fight(Monster& attacker, Hero& defender, int distance);

int getFileline2(string filename);
//bool getFromDB(Spell& x);
//bool getFromDB(Monster& x, int cmd);

void fillInventory(Hero& champ);  //in loadfromDBtemplate file
 

int main(int argc, char **argv)
{
	printf("hello world\n");
	
	/*
		//Test condition
	Condition testCondition;
	cout<<"Test condition, is Normal? "<<testCondition.getIsNormal()<<" getCondition() is: "<<testCondition.getCondition()<<endl;
	cout<<"Assign a condition, enter a number:";
	int code;
	cin>>code;
	testCondition.setCondition(code);
	cout<<"New condition set."<<endl;
	cout<<"Is Normal? "<<testCondition.getIsNormal()<<endl;
	cout<<"Condition number is: "<<testCondition.getCondition()<<endl;
	cout<<"Return to normal"<<endl;
	testCondition.setCondition(0); */
	
	/*
	//Test magic class
	MagicCreator magicMachine;
	Magic * myMagic;
	
	myMagic = magicMachine.getMagic();
	myMagic->outputdata(); 
	//myMagic->bonusSpell(5);
	//myMagic->outputdata();
	for(int lvl = 2; lvl<=5; lvl++)
	{
		cout<<" == New Level "<<lvl<<" =="<<endl;
		myMagic->levelUp(lvl);
		myMagic->outputdata();
	}
	*/
	
	
	/*	//Test spell creation etc
	Spell aSpell;
	aSpell.outputData();
	Spell bSpell("Acid Splash", Conj, Attack);
	bSpell.outputData();
	Spell cSpell("cure minor wounds", Conj, Heal);
	cSpell.outputData();
	myMagic->addSpell(aSpell);
	myMagic->addSpell(bSpell);
	cout<<"Spells added to spellbook."<<endl;
	 */
	 
	 /*
	 //Test spell loading
	 const char Quit = 'q';
	 char input = 'i';
	 while(input != Quit)
	 {
	 Spell aSpell;
	 getFromDB(aSpell);
	 myMagic->addSpell(aSpell);
	 cout<<"enter q to quit or anything else to add another spell: ";
	 cin>>input;
	}
	myMagic->outputdata(); */
	
	/*cout <<endl<<"Save Spell to a file"<<endl;
ofstream outFile;
	outFile.open("Spell.txt");
  		 if(!outFile.good())
     		 cout << "File could not be opened" << endl;
  	 	else
   			{
		outFile << aSpell;
		outFile << bSpell;
		cout << "Saved"<< endl;
			} */
			
			/*
				//Test spell on condition
				cout<<"choose a spell, enter desired spell entry:";
				int indexNum;
				cin>>indexNum;
				Spell test;
				test = myMagic->getSpell(indexNum);
				cout<<"Caste "<<test.getName()<<endl;
				unsigned int effect = test.getEffectCode();
				testCondition.setCondition(effect);
				cout<<"Spell caste, target condition is now..."<<endl;
				cout<<testCondition.getStatus()<<endl; */
				
		/*
		//Test condition on Actor class
		Actor test;
		test.outputData();
		
		test.condition.setCondition(25780);
		test.outputData();
		*/
		
		/*
		//Test magic on race (gnome)
		Race *racetest;
		RaceCreator racemachine;
		racetest = racemachine.getRace();
		racetest->outputData();
		cout<<"press key to continue"<<endl;
		char blank;
	cin>>blank;
		racetest->racemagic->setAbilityScore(14, 2);
		racetest->racemagic->bonusSpell();
		cout<<endl<<endl;
		racetest->outputData();
			cout<<racetest->racemagic->getSpellList()<<endl;
			*/
			/*
		charClass *chartest;
		CharClassCreator classmachine;
		chartest = classmachine.getClass();
		cout<<endl;
		chartest->outputData();  
		cout<<"test destructor"<<endl;
		delete chartest;
		*/
		
		//Test new hero with magic and fight with favoured enemies
//		Hero champ("Bob");
		//champ.outputData(); 
      /*  cout<<" Do you know magic?? ";
        if(champ.getHasMagic() == 'n')
            cout<<" No!"<<endl;
        else
           cout<<" YES! "<<endl;
		    */
//	cout<<"press key to continue"<<endl;
//	char blank;
//	cin>>blank;
 //       Monster amonster; //, bmonster, cmonster;
//        Spell aspell;
       // getFromDB(amonster, 12); //vargouille
      //      getFromDB(amonster, 11);
 //       getFromDB(bmonster, 4); //scorpiion
 //       getFromDB(amonster, 6); //goblin (gnome/dwarf favoured enemy)
            //fight against goblin
          //  fight(champ, cmonster, 1);
 //       amonster.outputData();
//	cout<<"press key to continue"<<endl;
	//char blank;
//	cin>>blank;
	/*
        for(int round=1; round<=3; round++)
        {   cout<<"!! Round: "<<round<<endl;
            fight(amonster, champ, 1);  //this monster may include poison
			//need time delay for randon gen
				usleep(100000);
            //champ.outputShortData();
            //champ.condition.update();
			fight(champ, amonster, 1);
			//amonster.outputData();
				usleep(100000);
        } 
		 */
//		 cout<<"press key to continue"<<endl;
		//char blank;
//	cin>>blank;
	//bool success;
/*		//caste test
	Caste* caste = new Caste(&champ, &amonster, 2);
	bool isHit = caste->checkSpellHit();
	if(isHit)
		cout<<"Nice! Hit..."<<endl;
	else
		cout<<"You suck."<<endl; 
		caste->casteSpell();
		cout<<"Monster status is "<<amonster.condition.getStatus()<<endl;
		amonster.outputData();
	cout<<"Use caste then delete..."<<endl;
	delete caste;
		cout<<"press key to continue"<<endl;
		cin>>blank; 
		//Test self caste spells
		           cout<<endl<<"    Caste spell, choose speed asjust spell"<<endl;
	Caste* caste2 = new Caste(&champ);
	caste2->casteSpell();
	champ.outputData();
			cout<<" current speed is "<<champ.getCurrentSpeed()<<endl;
	delete caste2;
	*/
        //aspell = caste(champ, amonster, 2, success);
		/*
        if(success && !aspell.getIsSingleTarget())
        {
            cout<<"  !!!!Area affect spell, hits other targets too!!!!"<<endl;
            caste(champ, amonster, 3, aspell);  //distance most be from location of original caste
            //distance from first monster  
        } 
		 */
//		cout<<"press key to continue"<<endl;
		//char blank;
//	cin>>blank;
 //       amonster.outputData();
      //  bmonster.outputData();
      
 /*       //Spell aspell;
        Hero champ2;
        champ2.outputData();
		champ2.receiveHealing(1);
//            cout<<endl<<"    Caste spell, choose speed asjust spell"<<endl;
        Caste* caste3 = new Caste(&champ, &champ2, 1);  //, aspell);
		caste3->casteSpell();
        champ2.outputData();  
		cout<<"Current AC is "<<champ2.getAC()<<endl;
//		cout<<" current speed is "<<champ2.getCurrentSpeed()<<endl;
		delete caste3;
       // champ.outputData();
	   */
        //string output;
      //  cout<<"Write champ to cout as we would for to file"<<endl;
      //  cout<< champ.saveData();
      //  cout.flush();
      //  cout<<"Finished output"<<endl;
        //cout<<output<<endl;
        //save(champ);
		//champ.setCondition(3256);
		//champ.outputData();
	/*	champ.setCondition(256);
        cout<<"--Round number 1"<<endl;
        champ.condition.setDuration(2);
        champ.outputShortData();
        for(int round=2; round < 5; round++)
        {   cout<<"--Round number "<<round<<endl;
            champ.condition.update();
            champ.outputShortData();
        } */
        
	//	champ.levelUp();
	//	champ.outputData();
		//cout<<"Spells are: "<<champ.getSpellList()<<endl;
		 
         
         //Test starting gear
       // Hero champ("Bob");
        // fillInventory(champ);
		/*
		SaveThrow aSave;
		aSave.setFields(1,2,3);
		aSave.setRaceFields(0, 0, 2);
		aSave.outputData();
		cout<<endl;
		cout<<"Save against FORT: "<<aSave.getSaveThrow(FORT)<<endl;
		int values[6] = {0, 1, 2, 3, 4, 5};
		aSave.setSpecialFields(values);
		cout<<"Save against FEAR: "<<aSave.getSaveThrow(NONE, FEAR)<<endl;
		cout<<"Add some bonus values"<<endl;
		aSave.updateTempBonus(1, 1, 1);
		aSave.outputData();
		cout<<"Save against WILL: "<<aSave.getSaveThrow(WIL)<<endl;
		//cout<<"Test invlaid Save type:"<<endl;
		//cout<<"Save against BARB: "<<aSave.getSaveThrow(BARB)<<endl;	//does not compile
		*/
		/*
		Hero aHero("Bill");
		cout<<"FORT save throw: "<<aHero.aSavethrow.getSaveThrow(FORT)<<endl;
		cout<<"will and fear saving: "<<aHero.aSavethrow.getSaveThrow(WIL, FEAR)<<endl;
		aHero.aSavethrow.outputData();
		aHero.setCondition(8192);	//improved resistance
		aHero.condition.setDuration(3);
		aHero.aSavethrow.outputData();
		cout<<endl;
		aHero.outputShortData();
		cout<<endl;
		aHero.outputData(); 
		 */
		 /*
		 Combatant person("Jill");
		 cout<<person.getName()<<": attack is "<<person.getAtk()<<", with roll: "<<person.getAtkRoll()<<endl;
		*/
		/*
		Hero ahero[2];
		ahero[0].setName("Bill");
		ahero[1].setName("Jill");
		Encounter anEncounter;
		int heroNumber = 2;
		string heronames[heroNumber];
	for(int i=0; i<heroNumber; i++)
		heronames[i] = ahero[i].getName();
	Party ourParty(heronames, heroNumber);
	Initiative anInitiative;
	anInitiative.createList(ourParty, ahero, anEncounter);
	cout<<anInitiative.getList()<<endl;
//	anInitiative.sortList();
//	cout<<anInitiative.getList()<<endl;
	for(int x = 0; x<7; x++)
		cout<<x<<"st: "<<anInitiative.getNext()<<endl;
	*/
	//test level up
/*	for(int x=0; x<=5; x++)
	{
		champ.setExp(600);
	} 
	champ.outputData();
	cout<<"# of level 0 spells = "<<champ.myClass->classmagic->getNumofKnown(0)<<endl;
	cout<<"# of level 1 spells = "<<champ.myClass->classmagic->getNumofKnown(1)<<endl;
	
	 */
	 
	 //Test turn undead
	// TurnUndead turn;
	// turn.setFields(1,-1);
	Hero champ("Bob");	//choose cleric to try turning
	Monster amonster[13];
//        Spell aspell;
	for(int x=0; x<13; x++)
        getFromDB(amonster[x], 7); //skeleton
		//getFromDB(bmonster, 7);
		//getFromDB(cmonster, 7);
		cout<<amonster[0].getName()<<" has HD = "<<amonster[0].getHitDice()<<endl;
		cout<<"--Try to turn--"<<endl;
		
		for(int y=0; y<13; y++)
		{
			champ.myClass->turning->turnMonster(amonster[y], y);
			
		}
		champ.myClass->turning->finishTurn();
		champ.myClass->outputData();
		//turn.turnMonster(amonster[y], y);
		//turn.turnMonster(bmonster, 7);
		//turn.turnMonster(cmonster, 10);
		amonster[12].outputData();
	cout<<"Finished"<<endl;
	return 0;
}

/*
int getFileline2(string filename)
{
	string x;
	int filelines=0;
	ifstream inFile;
	inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
		}   
	else 
	{
	while(getline(inFile,x) && !inFile.eof())
		filelines++;
	}
	inFile.close();
	return filelines;
} 
*/
/*
bool getFromDB(Spell& x)  //to search through database for objects
{
	const int QUIT = 0;
	bool success = 0;
	int cmd;

	string filename = "Spell.txt";
	ifstream inFile;

	int filelines = getFileline(filename);
cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
QUIT << " to exit and use selected object ";
cin >> cmd;
	cout <<"-----id entered = " <<cmd<<endl;
	while(cmd != QUIT)
	{

inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
		cmd = QUIT;
		success = 0;
		} 
	else 
			{

	while(cmd > filelines)
				{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
				}
		
int linenumber = 1;
	while( inFile>>x && linenumber != cmd && !inFile.eof())
				{	
	linenumber++;
				}
		success = 1;
	x.outputData();
cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
QUIT << " to exit and use selected object";
cin >> cmd;
	cout <<"-----id entered = " <<cmd<<endl;
			}  //else
inFile.close();
	}

	return success;
} */
/*
bool getFromDB(Monster& x, int cmd)  //to search through database for objects
{
	const int QUIT = 0;
	bool success = 0;
	//int cmd;

	string filename = "Monster.txt";
	ifstream inFile;

	int filelines = getFileline2(filename);
//cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
//QUIT << " to exit and use selected object ";
//cin >> cmd;
	cout <<"-----id entered = " <<cmd<<endl;
	while(cmd != QUIT)
	{

inFile.open(filename, ios::in);// | ios::binary);
if(!inFile.good())
		{      
		cout << "File could not be opened" << endl;
		cmd = QUIT;
		success = 0;
		} 
	else 
			{

	while(cmd > filelines)
				{
			cout <<" you entered a number larger then the entries in the file,"<<endl<<"enter a number between 1 and "<<filelines;
		cin >> cmd;
				} 
		
int linenumber = 1;
	while( inFile>>x && linenumber != cmd && !inFile.eof())
				{	
	linenumber++;
				}
		success = true;
	x.outputData();
//cout << "Enter ID number from 1 to "<<filelines <<" of "<<filename<<" to view or " <<
//QUIT << " to exit and use selected object";
//cin >> cmd;
	//cout <<"-----id entered = " <<cmd<<endl;
    cmd = QUIT;
			}  //else
inFile.close();
	}

	return success;
} */