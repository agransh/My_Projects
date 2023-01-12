//Name: Mario.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Mario which is the child of character
// as well as it has all its functions

//libraries
#include "Character.h"
#include "Mario.h"

using namespace std;


//Default Constructor
Mario::Mario(){

}

//Overloaded Constructor 
Mario::Mario(string name, double topSpeed, double handling, double acceleration):Character(name,topSpeed,handling,acceleration){}

//Dstructor TO FINISH
Mario::~Mario(){}


//Name: SpecialMove
//Description: Speed will raise to max
//Extra Values:
//-cooldown
bool Mario::SpecialMove(int position, int turn){
    //checks if special move is available
    if(IsSpecialMoveAvailable(position,turn)){
      SetLastTurnSM(turn);
      this->SetCurSpeed(this->GetTopSpeed());
      return true;
    }
    return false;
}

//Name: IsSpecialMoveAvailable 
//Check if special move is available
bool Mario::IsSpecialMoveAvailable(int position, int turn){
    //checks if special move is available
    if(this->lastTurnSM+MARIO_COOLDOWN<turn){
        return true;
    }else{
        return false;
        }
    }
//Name: SetLastTurnSM
///Sets lastTurnSM to lTurn
void Mario::SetLastTurnSM(int lTurn){
    this->lastTurnSM=lTurn;
    }

//Name: GetLastTurn
//Returns lastTurnSM
int Mario::GetLastTurnSM(){
    return lastTurnSM;
    }

//Name: GetType
//Return Character Type
string Mario::GetType(){
    return "Mario";
    }


//Overloaded << operator
ostream& Mario::operator<<(ostream &output){
    output<<"Mario ("<<this->GetName()<<") has gone "<< this->GetCurLocation() <<" meters and is currently going "<<this->GetCurSpeed()<<" m/s";
    return output;
}