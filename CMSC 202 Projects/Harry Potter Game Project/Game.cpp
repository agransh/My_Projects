//Name: Game.cpp
//Project: CMSC 202 Project 5, Fall 2021
//Author:  Agransh Srivastava
//Date:    12/6/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This class includes most of the key functions and manages most of the game. 

//libraries
#include "Hero.h"
#include "Villain.h"
#include "Lqueue.cpp"
#include "Game.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//Constructor to open up files
Game::Game(string f_fileName){
  m_fileName=f_fileName;
}

//destructor
Game::~Game(){
    for(Hero* hero:m_heroes){
        delete hero;
        }

    for(Villain* villain:m_villains){
        delete villain;
        }
    }
  // Name: LoadFile
  // Loads in Heros 
  // Should be: Heros loaded: 230 Villains Loaded: 94 Total Loaded: 324
void Game::LoadFile(){
    
    //opens up the file
    ifstream database;
    database.open (m_fileName, ifstream::in);
    string data = "";
    int heroesCount, villainsCount;
    //reads the file and sets up the data accordingly for starting and ending index
    while(getline(database, data)){
        string values[6];
        int currIndex = 0, i = 0;  
        int startIndex = 0, endIndex = 0;
        
        //runs the while loop till the file size
        while (i <= data.length()){
            //checks for | in the data so it knows when to seperate it
            if ( (currIndex!=6) & (data[i] == '|' || i == data.length()))  { 
                endIndex = i;  
                string subStr = "";  
                subStr.append(data, startIndex, endIndex - startIndex);  
                values[currIndex] = subStr;  
                currIndex += 1;  
                startIndex = endIndex + 1;
                    }
                i++;
            }

        //Create the piece and insert it in the track
        if(values[1]!=""){
            //Insert for Villian
            if(values[0]=="VILLAIN"){
                Villain* newVillain= new Villain(values[1],values[2],stoi(values[3]),stoi(values[4]),stoi(values[5]));
                m_villains.push_back(newVillain);
                villainsCount++;
                }
            //Insert for Hero
            if(values[0]=="HERO"){
                Hero* newHero= new Hero(values[1],values[2],stoi(values[3]),stoi(values[4]),stoi(values[5]));
                m_heroes.push_back(newHero);
                heroesCount++;
                }
            }
    }
    //closes the file
    database.close();

    cout<<"Heros loaded: "<<heroesCount<<" Villains Loaded: "<<villainsCount<<" Total Loaded: "<<villainsCount+heroesCount<<endl;
    }



//Name: PrintHeros
//Prints the heros stored in m_hero
void Game::PrintHeroes(){
    int i=1;
    //uses for loop to loop through the heros
    for(Hero* hero:m_heroes){
        cout<<i<<". "<<*hero<<endl;
        i++;
        }    
    }   

//Name: PrintVillians
//Prints villians from m_villians
void Game::PrintVillains(){
    int i=1;
    //Uses for loop to loop through the villians
    for(Villain* villain:m_villains){
        cout<<i<<". "<<*villain<<endl;
        i++;
        }
    }

///Name:PrintMyHeros
//Prints heros from the myHeros list
void Game::PrintMyHeroes(){
    //checks to see if the user has heros
    if(m_myHeroes.size()==0){
        cout<<"You have no heroes yet! You should try to acquire some first!"<<endl;
        }
        //prints heros from myHeros
        for(int i=0;i<m_myHeroes.size();i++){
            cout<<i+1<<". "<<*m_myHeroes.operator[](i)<<endl;
        }
    }

//Name: AcquireHero
//Menu for acquiring Heros of different rarities
void Game::AcquireHero(){
    int rarity;
    //menu choices for hero rarirty
    cout<<"How rare of a wizard would you like to recruit?:"<<endl;
    cout<<"1. Very Common (Very High Probability)"<<endl;
    cout<<"2. Common (High Probability)"<<endl;
    cout<<"3. Uncommon (Normal Probability)"<<endl;
    cout<<"4. Rare (Low Probability)"<<endl;
    cout<<"5. Ultra Rare (Extremely Low Probability)"<<endl;

    cin>>rarity;

    //sets the random percentage
    int percRand=RARITY[rarity-1];

    cout<<"You ask around to see if anyone would be willing to join you."<<endl;  

    //Randon chance for rarer heros
    if((rand() % 100 + 1)<=percRand){
        FoundHero(rarity);
        }
    else{
        cout<<"mission failed :("<<endl;
        }


    }

//Name: FoundHero
//Checks to see if a hero is found in AcquireHero, then the rarity is passed to this function 
void Game::FoundHero(int rarity){
    //makes a vector for hero pointers
    vector<Hero*> heroesPool;
    bool duplicate=false;
    //Runs until the m_hero list ends
    for(Hero* hero:m_heroes){
        //checks for duplicates
        if(hero->GetRarity()==rarity){
            duplicate=false;
            //turns true if there are duplicates
            for(int i=0;i<m_myHeroes.size();i++){
                if(hero->GetDesc()==m_myHeroes.operator[](i)->GetDesc()){
                    duplicate=true;
                    }
                }
                if(!duplicate){
                    heroesPool.push_back(hero);
                }  
            }
        }
        //checks to see if herosPool is empty
        if(heroesPool.size()!=0){
            Hero* tempHero=heroesPool[rand() % heroesPool.size()];
            m_myHeroes.Push(tempHero);
            cout<<"With some amount of effort,  "<<tempHero->GetName()<<" has agreed to join you!"<<endl;
        }
    }


//Name: MainMenu
//Calls different functions based on what the user puts in as their choice
void Game::MainMenu(){
    int choice;

    //runs a do while loop to get the user choice 
    //runs until user calls exit
    do{
        cout<<"What would you like to do?:"<<endl;
        cout<<"1. See All Heroes"<<endl;
        cout<<"2. See All Villains"<<endl;
        cout<<"3. See Your Heroes"<<endl;
        cout<<"4. Try to Acquire a New Hero"<<endl;
        cout<<"5. Train a Hero"<<endl;
        cout<<"6. Enter a Wizard Battle"<<endl;
        cout<<"7. Exit"<<endl;

        cin>>choice;
        //switch cases according to the user choice
        switch(choice){
        case 1:{
            PrintHeroes();
        }
        break;
        case 2:{
            PrintVillains();
        }
        break;
        case 3:{
            PrintMyHeroes();
        }
        break;
        case 4:{
            AcquireHero();
        }
        break;
        case 5:{
            TrainHero();
        }
        break;
        case 6:{
            Battle();
        }
        break;
        }
    }while(choice!=7);
        }

//Name:PrepareVillians
//Prepares villians for battle
void Game::PrepareVillains(){
    //asks user how many villains they want to battle
    cout<<"How many villains would you like to battle?"<<endl;
    int choice;
    cin>>choice;

    //checks if choice is greater than max villians
    if(choice>MAX_VILLAINS)choice=MAX_VILLAINS;

    cout<<SEP<<endl;
    cout<<"The enemy wizards stand ready to battle"<<endl;
    //puts a random villian in the battle using rand
    for(int i=0;i<choice;i++){
        Villain* tempVillain = m_villains[rand() % m_villains.size()];
        cout<<*tempVillain<<endl;
        m_bVillains.Push(tempVillain);
        }
        cout<<SEP<<endl;
    }


//Name: PrepareHeros
// Prepares the Heros to attack the villians
void Game::PrepareHeroes(){
    int choice;
    //asks user for a chooice
    //runs through the hero choices
    for(int i=0;i<5;i++){
        cout<<"Add from 1 to 5 heroes to your battle roster"<<endl;
        cout<<"Enter -1 when done"<<endl;

        //calls the printMyHeroes Function here to print the heroes
        PrintMyHeroes();

        cin>>choice;

        ////choice that exits the program
        if(choice==-1){
            i=5;
        }
        else{
            m_bHeroes.Push(m_myHeroes.operator[](choice-1));
        }
    }
    cout<<SEP<<endl;
    cout<<"The hero wizards stand ready to battle"<<endl;
    //runs throught the battle Heroes List to put those heroes into battle
    for(int i=0;i<m_bHeroes.size();i++){
        cout<<*m_bHeroes.operator[](i)<<endl;
        }
        //seperator
        cout<<SEP<<endl;
    }


//Name: Battle
//Battles Heroes and Villians Together
//If hp of the hero is below 0 then hero or villian is dequeued from their battle queue
void Game::Battle(){
    //Calls both Prepare Hero and Villian Functions to get them ready for battle
    PrepareVillains();
    PrepareHeroes();
    cout<<"Done Preparing"<<endl;
    cout<<*m_bHeroes.Front()<<" vs "<<*m_bVillains.Front()<<endl;
    
    //checks if both battle fields are empty
    while(!m_bHeroes.IsEmpty() && !m_bVillains.IsEmpty()){
        // here is Hero's Turn
        m_bHeroes.Front()->Attack();
        m_bVillains.Front()->SetHp(m_bVillains.Front()->GetHp()-m_bHeroes.Front()->GetCombat());
        //checks to see if the villian was defeated
        if(m_bVillains.Front()->GetHp()<=0){
            cout<<m_bVillains.Pop()->GetName()<<" is defeated!"<<endl;
            }
            else{
                //Here is the villain's Turn
                m_bVillains.Front()->Attack();
                m_bHeroes.Front()->SetHp(m_bHeroes.Front()->GetHp()-m_bVillains.Front()->GetCombat());
                //checks to see if the hero was defeated
                if(m_bHeroes.Front()->GetHp()<=0){
                    cout<<m_bHeroes.Pop()->GetName()<<" is defeated!"<<endl;
                }
            }
        }
        //Calls reseolve Battle function to end the battle
        ResolveBattle();
    }


//Name:ResolveBattle
//Fucntion to see who won the battle
void Game::ResolveBattle(){
    cout<<SEP<<endl;
    //checks if bVillians is empty to tell that heroes won
    if(m_bVillains.IsEmpty()){
        cout<<"The hero wizards win the battle!"<<endl;
    }
    //otehrwise villians win
    else{
        cout<<"The villains wizards win the battle!"<<endl;
    }
    cout<<SEP<<endl;
    }


//Name: TrainHero
//Trains a hero chosen by the user
void Game::TrainHero(){
  cout<<"Which of your wizards would you like to train?:"<<endl;
  
  //runs through the hero list
  for(int i=0;i<m_myHeroes.size();i++){
    cout<<i+1<<". "<<*m_myHeroes.operator[](i)<<endl;
  }

  int choice;
  cin>>choice;
  //tells the user that the hero they picked is trained and ready for combat
  cout<<"Your "<<m_myHeroes.operator[](choice-1)->GetName()<<" trained."<<endl;
  m_myHeroes.operator[](choice-1)->Train();
  cout<<"Your combat is now "<<m_myHeroes.operator[](choice-1)->GetCombat()<<"."<<endl;
}