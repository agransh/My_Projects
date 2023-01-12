//Name: Obstacle.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Obstavle which is the parent
// class for Banana and Shell

//libraries
#include <iostream>
#include <string>

#include "Obstacle.h"

using namespace std;

//Constructor
Obstacle::Obstacle(){}

//Overloaded constructor which sets color
Obstacle::Obstacle(string color){
    this->m_color=color;
}

//Destructor
Obstacle::~Obstacle(){}

//Name: GetColor
//Returns m_color
string Obstacle::GetColor(){
    return this->m_color;
}


//Name: SetColor
//Sets m_color to color
void Obstacle::SetColor(string color){
 this->m_color=color;
}


