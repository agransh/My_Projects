//Name: Toad.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Toad which is the child of character
// as well as it has all its functions

//libraries
#include "Character.h"
#include "Toad.h"

using namespace std;


//Default Constructor
Toad::Toad(){

}

//Overloaded Constructor 
Toad::Toad(string name, double topSpeed, double handling, double acceleration):Character(name,topSpeed,handling,acceleration){}

//Dstructor TO FINISH
Toad::~Toad(){}



//Name: SpecialMove
//Description: if toad is in last position topSpeed will raise to 100 for the rest of the game
bool Toad::SpecialMove(int position,int turn){
    //checks if special move is available
    if(IsSpecialMoveAvailable(position,turn)){
        SetLastTurnSM(turn);
        this->SetTopSpeed(100);
        return true;
    }
    return false;
}

//Name: IsSpecialMoveAvailable
//Check if special move is available
bool Toad::IsSpecialMoveAvailable(int position,int turn){
  return position;
}

//Name: GetType
//Return Character Type
string Toad::GetType(){
	return "Toad";
}

//Name: SetLastTurnSM
//Sets lastTurnSM to lTurn
void Toad::SetLastTurnSM(int lTurn){
  this->lastTurnSM=lTurn;
}

//Name: GetLastTurnSM
//returns lastTurnSM
int Toad::GetLastTurnSM(){
  return lastTurnSM;
}

//Overloaded << operator
ostream& Toad::operator<<(ostream &output){
    output<<"Toad ("<<this->GetName()<<") has gone "<< this->GetCurLocation() <<" meters and is currently going "<<this->GetCurSpeed()<<" m/s";
    return output;
}