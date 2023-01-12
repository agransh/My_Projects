//Name: Shell.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Wario which is the child of character
// as well as it has all its functions

//libraries
#include "Obstacle.h"
#include <string>
#include "Shell.h"

using namespace std;
  
//Constructor
Shell::Shell(){}

//Destructor
Shell::~Shell(){}

//Name: Tick
//checks to see if a racer ran into a shell
void Shell::Tick(bool){
  
}

//Name: Crash
//Checks to see if racer crashed into a shell and the racer spins out and speed reduces
int Shell::Crash(){
  return SPEED_LOST;
}

//Name: GetType
//Returns Shell as type
string Shell::GetType(){
  return "Shell";
}

//Overloaded operator
ostream& Shell::operator<<(ostream& output){
  output<<"Launches a Shell ahed you, the first racer ahed you will have his speed recued by 20."<<endl;
  return output;
}