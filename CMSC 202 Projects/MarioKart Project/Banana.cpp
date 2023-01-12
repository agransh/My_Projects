//Name: Banana.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Banana which is the child of obstacle
// as well as it has all its functions

//Libraries
#include "Obstacle.h"
#include <string>
#include "Banana.h"

using namespace std;
  
//Constructor
Banana::Banana(){}
  
//Destructor
Banana::~Banana(){}

//Name: Tick
// checks to see if racer ran into a banana
void Banana::Tick(bool){
  
    }

//Name: Crash
//Checks to see if racer crashed into a banana and the racer spins out and speed reduces
int Banana::Crash(){
    return SPEED_LOST;
        }

//Name: GetType
//Returns Banana as type
string Banana::GetType(){
    return "Banana";
        }

//overloaded operator
ostream& Banana::operator<<(ostream& output){
    output<<"Leaves a banana behind you, the first racer behind you will have his speed recued by 20."<<endl;
    return output;
        }