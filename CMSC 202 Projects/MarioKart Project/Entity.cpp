//Name: Entity.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: Abstract parent class that is common to Character Mario Wario and Toad

//libraries
#include <string>
#include <iostream>
#include <iomanip>
#include "Entity.h"

using namespace std;

//Default constructor
Entity::Entity(){
  
}

//Overloaded constructor
//sets m_name
Entity::Entity(string name){
	this->m_name=name;
}

//destructor
Entity::~Entity(){
  
}

//Name: GetName
//Gets the name
string Entity::GetName(){
	return this->m_name;
}

//Name: SetName
//Sets the name to m_name
void Entity::SetName(string name){
	this->m_name=name;
} 