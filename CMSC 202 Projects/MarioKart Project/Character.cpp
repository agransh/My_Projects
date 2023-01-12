//Name: Entity.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: Child of the Entity class with all of its functions

//libraries
#include "Entity.h"
#include "Character.h"

using namespace std;

//Default Constructor
Character::Character():Entity("default"),m_topSpeed(0),m_handling(0),m_acceleration(0){}


//Overloaded Constructor
Character::Character(string name, double topSpeed, double handling, double acceleration):Entity(name),m_topSpeed(topSpeed),m_handling(handling),m_acceleration(acceleration){}

//Destructor TO FINISH
Character::~Character(){

}

//Name: GetCurLocation
//Getter for Current location, retruns current location of the racer
double Character::GetCurLocation(){
	return this->m_curLocation;
}

//Name: SetCurLocation
//Sets current locaiton of the racer
void Character::SetCurLocation(double curLocation){
	this->m_curLocation=curLocation;
}

//Name: GetCurSpeed
//Gets the racers current speed
double Character::GetCurSpeed(){
	return this->m_curSpeed;
}

//Name: SetCurSpeed
//Sets racers current speed 
void Character::SetCurSpeed(double curSpeed){
	this->m_curSpeed=curSpeed;
}

//Name: GetTopSpeed
//Gets players current top speed of the racer
double Character::GetTopSpeed(){
	return this->m_topSpeed;
}

//Name: SetTopSpeed
//Sets players current top speed of the racer
void Character::SetTopSpeed(int topSpeed){
  this->m_topSpeed=topSpeed;
}
//Name: GetHandling
//Returns handling of the racer
double Character::GetHandling(){
	return this->m_handling;
}

//Name: GetAcceleration
//Returns the racers acceleration
double Character::GetAcceleration(){
	return this->m_acceleration;
}


//extra credit
//void Character::SpecialMove(){

//}

//Name: CalcSpeed
// Calculates the current speed of the racer
void Character::CalcSpeed(double gas){
    //users speed determinded using gas * curSpeed (accel *handling)
	double temp = gas * (m_curSpeed +(this->m_acceleration*this->m_handling) );
	
    //if the calucalted speed is less than the top speed
    //then set that speed to curSpeed otherwise its temp
    if(temp>=this->m_topSpeed){
		this->m_curSpeed = this->m_topSpeed;
	}else{
		this->m_curSpeed = temp;
	}
}

//Name: Tick
// This function will check for the racers max speed and tell them if they crashed
void Character::Tick(double maxSpeed){
    // c irrSpeed is greater than maxSpeed
	if(this->m_curSpeed>maxSpeed){
        //print statements
        cout<<this->GetType()<<" ("<<this->GetName()<<") "<<this->m_curSpeed<<" vs Max: "<<maxSpeed<<endl;
        cout<<this->GetType()<<" ("<<this->GetName()<<") has crashed!"<<endl;
        //resetting curSpeed
		this->m_curSpeed=0;
	}

    //iterates curLocation 
    this -> m_curLocation += m_curSpeed;
}