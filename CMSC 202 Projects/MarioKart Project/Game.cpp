//Name: Game.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains the main class
//game which organizes the race

//Libraries
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Game.h"

using namespace std;

//Name: Game
//Constructor
//Initiates Game
Game::Game(){
    cout<<"Welcomes player to UMBC Mario Kart"<<endl;
    this->m_numLaps=1;
    this->m_numRacers=1;
}

//Destructor for Game
Game::~Game(){
    //deletes all 
    for(int i=0;i<m_Racers.size();i++){
        delete m_Racers[i];
  }
}

//Name: LoadTrack
//Asks the user what track they want to use
void Game::LoadTrack(){
    cout<<"Which track would you like to use?"<<endl;

    //Runs through the tracks and sets it to i to display
    for(int i=1;i<NUM_TRACKS+1;i++){
        cout<<i<<". "<<TRACK[i-1][0]<<endl;
        }

    //choice
    int choice;
    cin>>choice;

    //Loads in the track
     for(int i=0;i<this->m_numLaps;i++){
         this -> myTrack.LoadTrack(TRACK[choice-1][1]);
            }
    }

//Name: RaceSetup
// Sets up the race for the user
void Game::RaceSetup(){
    //Asks the user for their name
    cout<<"What is your name?"<<endl;
    string name;
    cin>>name;

    //this while loops asks user to select a racer for them
    int index;
    do{
        cout<<"Select a Racer"<<endl;
        cout<<"1. Mario"<<endl;
        cout<<"2. Toad"<<endl;
        cout<<"3. Wario"<<endl;

        cin>>index;
    }while(index<1&index>3);

    //swtich cases according to user choice and sets in their stats accordingly
    switch(index){
        case 1: this -> m_Racers.push_back(new Mario(name,MARIO_STATS[0],MARIO_STATS[2],MARIO_STATS[1]));
        break;
        case 2: this -> m_Racers.push_back(new Toad(name,TOAD_STATS[0],TOAD_STATS[2],TOAD_STATS[1]));
        break;
        case 3: this -> m_Racers.push_back(new Wario(name,WARIO_STATS[0],WARIO_STATS[2],WARIO_STATS[1]));
        break;
    }

    //asks user for how many racers they want to compete agaiinst and sets it up
    cout<<"How many other competitors would you like?"<<endl;
    int nCpu;
    cin>>nCpu;

    //sets up the stats for the CPU using random
    for(int i=0;i<nCpu;i++){ 
        index=rand() % 3+1;
        
        switch(index){
            case 1: this -> m_Racers.push_back(new Mario("CPU"+to_string(i),MARIO_STATS[0],MARIO_STATS[2],MARIO_STATS[1]));
            break;
            case 2: this -> m_Racers.push_back(new Toad("CPU"+to_string(i),MARIO_STATS[0],TOAD_STATS[2],TOAD_STATS[1]));
            break;
            case 3: this -> m_Racers.push_back(new Wario("CPU"+to_string(i),WARIO_STATS[0],WARIO_STATS[2],WARIO_STATS[1]));
            break;
            }
        }

    //asks user for how many laps they want for the race
    cout<<"How many laps would you like to complete for the race?"<<endl;
    int nLaps;
    cin>>nLaps;

    this->m_numLaps=nLaps;
    }

//Name: StartRace
// Starts the race with all the information that would normally 
// be shown in a real mario kart game
void Game::StartRace(){
  
  //Shows who user will be racing and how many laps, total length of the race
  // and the start of the race track
  cout<<"You will be racing "<<this->m_numLaps<<" lap"<<endl;
  cout<<"The total length of the race is "<<this->myTrack.GetTotalLength()<<" meters."<<endl;
  cout<<"Start of the Race Track"<<endl<<endl;

  //race start
  cout<<"*********ON YOUR MARKS*********"<<endl<<endl;
  cout<<"*********GET SET*********"<<endl<<endl;
  cout<<"*********GO! GO! GO!*********"<<endl<<endl;
  
  //shows what the racer sees ahead of them
  cout<<"You currently see:"<<endl;
  cout<<myTrack.DisplayPiece(0)<<endl<<endl;

  int nRound=0;

  bool forceStop = false;

  //checks if the user didn't forcestop the code
  while(!forceStop){
      if(this -> Action(nRound)==0){
         return;
        }
        
        this->CpuRandom();
        //iteratres through the rounds 
        nRound++;
        cout<<"************************"<<endl;
        cout<<"Round : "<<nRound<<endl;
        cout<<"************************"<<endl;
        cout<<"You currently see:"<<endl;
        //shows the racer whats ahead of them
        cout<<myTrack.DisplayPiece(myTrack.GetPiece(m_Racers[this->FindPlayer()]-> GetCurLocation()))<<endl;
        cout<<"Ahead is:"<<endl;
        cout<<myTrack.DisplayPiece(myTrack.GetPiece(m_Racers[this->FindPlayer()]-> GetCurLocation())+1)<<endl<<endl;
        
        //Uses Tick to iterate to the next set round 
        this -> Tick(myTrack.GetMaxSpeed(myTrack.GetPiece(m_Racers[this->FindPlayer()]-> GetCurLocation())));
        cout<<"************************"<<endl;
        this->Display();
        cout<<"************************"<<endl;
        forceStop=this -> CheckFinish();
        }
    }

//Name: CheckFinish
//checks if the racer has finsihed the race
bool Game::CheckFinish(){
    //uses a for loop to check the racers position and determines who won the race
    for(Entity* entity:this->m_Racers){
        //if the current location of a racer is equal to the length of the track
        //then that player won the race
        if(entity->GetCurLocation()>=this->myTrack.GetTotalLength()){
        cout<<"The race is over!"<<endl;
        cout<<entity->GetType()<<" ("<<entity->GetName()<<") won the race!"<<endl;
        return true;
        }
    }
    return false;
    }

//Name: CpuRandom
//Generates Random values for the CPU
void Game::CpuRandom(){
    for(Entity* entity:this->m_Racers){
        if(entity->GetName().find("CPU")!=string::npos){
            double gas=(rand() % 4 + 1)*0.25;
            entity->CalcSpeed(gas);
            }
        }
    }

//Name: Tick
//Determines max speed for the racers
void Game::Tick(double maxSpeed){
    for(Entity* entity:this->m_Racers){
        entity->Tick(maxSpeed);
        }
    }

//Name: Order
// Swaps the racers when one gets ahead of the other 
void Game::Order(){
    bool swap = true;
    //runs while swap is true
    while(swap){
        swap = false;
        //runs till the total numbers of racers
        for(int i=0;i<m_Racers.size()-1;i++){
            //swaps the racers
            if(m_Racers[i]->GetCurLocation()<m_Racers[i+1]->GetCurLocation()){
             iter_swap(m_Racers.begin() + (i+1), m_Racers.begin() + (i));
             swap = true;
            }
        }
    }
    }


//LATER extra credit
void Game::Attack(){
  
}

//Name: Display
//Displays the racers racing
void Game::Display(){
    //displays the racers racing
    for(Entity* entity:this->m_Racers){
        *entity << cout << endl;
        }
    }

//Name: FindPlayer
//Finds players positons in the track 
int Game::FindPlayer(){
    this->Order();
    int index=0;
    //uses entity in a for loop to get the name of the racer and return their index
    for(Entity* entity:this->m_Racers){
        if(!(entity->GetName().find("CPU")!=string::npos)){
            return index;
            }
            index++;
        }
        return -1;
    }

//Name: Action
//Allows the player to choose an action of what they want to do
//depending on where they are on the track
int Game::Action(int nRound){
    //user choices
    while(true){
        cout<<"What would you like to do?"<<endl;
        cout<<"1. Max Speed"<<endl;
        cout<<"2. Pretty Fast"<<endl;
        cout<<"3. Fast"<<endl;
        cout<<"4. Slow"<<endl;
        cout<<"5. Use Obstacle"<<endl;
        cout<<"6. Quit"<<endl;
        int choice;
        cin>>choice;

        //switch cases based on the choice that the user chooses
        switch(choice){
            case 1:{
                m_Racers[this->FindPlayer()]->CalcSpeed(1);
                return 1;
                }
            break;
            case 2:{ 
                m_Racers[this->FindPlayer()]->CalcSpeed(0.75);
                return 1;
                }
            break;
            case 3:{ 
                m_Racers[this->FindPlayer()]->CalcSpeed(0.50);
                return 1;
                }
            break;
            case 4:{ 
                m_Racers[this->FindPlayer()]->CalcSpeed(0.25);
                return 1;
                }
            break;
            //LATER extra credit
            case 5:{
                int choice2=0;
                int target;
                while(choice2!=1 & choice2!=2){
                    cout<<"What would you like to do?"<<endl;
                    cout<<"1. Banana"<<endl;
                    cout<<"2. Shell"<<endl;
                    cin>>choice2;
            
                    switch(choice2){
                        case 1:{
                            Obstacle* newBanana = new Banana();
                            target=this-> FindPlayer() + 1;
                            if(target<0){
                                cout<<"You cant use it, your are last."<<endl;
                                choice2=-1;
                            }else{
                                m_Racers[target]->SetCurSpeed(m_Racers[target]->GetCurSpeed()-newBanana->Crash());
                                cout<<m_Racers[target]->GetName()<<" got hit by a banana"<<endl;
                            if(m_Racers[target]->GetCurSpeed()<0){
                                m_Racers[target]->SetCurSpeed(0);
                                }
                                }
                        } 
                        break;
                        case 2:{
                        Obstacle* newShell = new Shell();
                        target=this -> FindPlayer() - 1;
                        if(target>=m_numRacers){
                            cout<<"You cant use it, your are First."<<endl;
                            choice2=-1;
                        }else{
                            m_Racers[target]->SetCurSpeed(m_Racers[target]->GetCurSpeed()-newShell->Crash());
                            cout<<m_Racers[target]->GetName()<<" got hit by a shell"<<endl;
                            if(m_Racers[target]->GetCurSpeed()<0){
                            m_Racers[target]->SetCurSpeed(0);
                                }
                            }
                        }
                        break;
                    }
                } 
                return 1;
                }
            break;
            case 6: return 0;
            break;
            case 7:{
                // (if FindPlayer()-m_numRacers = 0 it means that player is at last position)
                if(m_Racers[this -> FindPlayer()]->SpecialMove(nRound,FindPlayer()-m_numRacers)){
                    cout<<"You utilized your ability!"<<endl;
                    return 1;
                }else{
                    cout<<"Ability cant be utlizied!"<<endl;
                 }
            }
            break;
            }
        }
    }