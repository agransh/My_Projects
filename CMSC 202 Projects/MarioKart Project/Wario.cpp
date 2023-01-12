//Name: Wario.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Wario which is the child of character
// as well as it has all its functions

//libraries
#include "Character.h"
#include "Wario.h"

using namespace std;


//Default Constructor
Wario::Wario(){

}

//Overloaded Constructor 
Wario::Wario(string name, double topSpeed, double handling, double acceleration):Character(name,topSpeed,handling,acceleration){}

//Dstructor TO FINISH
Wario::~Wario(){}


//Name: SpecialMove
//Description: Raise curLocation
//Extra Values:
//-cooldown
bool Wario::SpecialMove(int position, int turn){
    if(IsSpecialMoveAvailable(position,turn)){
      SetLastTurnSM(turn);
      this->SetCurLocation(this->GetCurLocation()+120);
      return true;
    }
    return false;
}

//Name: IsSpecialMoveAvailable
//Check if special move is available
bool Wario::IsSpecialMoveAvailable(int position, int turn){
    //checks if special move is available
    if(this->lastTurnSM+WARIO_COOLDOWN<turn){
        return true;
    }else{
        return false;
        }
    }

//Name: SetLastTurnSm
//Sets lastTurnSM to lTurn
void Wario::SetLastTurnSM(int lTurn){
    this->lastTurnSM=lTurn;
    }

//Name: GetLastTurnSM
//Returns lastTurnSM
int Wario::GetLastTurnSM(){
  return lastTurnSM;
}

//Name: GetType
//Return Character Type
string Wario::GetType(){
	return "Toad";
}


//Overloaded << operator
ostream& Wario::operator<<(ostream &output){
	output<<"Wario ("<<this->GetName()<<") has gone "<< this->GetCurLocation() <<" meters and is currently going "<<this->GetCurSpeed()<<" m/s";
  return output;
}