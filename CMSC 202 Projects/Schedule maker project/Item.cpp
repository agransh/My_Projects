//Name: Item.cpp
//Project: CMSC 202 Project 3, Fall 2021
//Author:  Agransh Srivastava
//Date:    10/26/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains implementations for class functions

//libraries
#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

//calls item default class
Item::Item():m_name("Default"),m_time(0000),m_next(nullptr){}

//Overloaded item class
Item::Item(string name, int time):m_name(name),m_time(time),m_next(nullptr){}

//Getters

//Name: GetName
//Desc: returns the name of the schedule
string Item::GetName(){
	return m_name;
}

//Name: GetTime
//Desc: returns the time activity starts
int Item::GetTime(){
	return m_time;
}

//Name: GetNext
//Desc: Returs pointer to the next node in the linked list
Item* Item::GetNext(){
	return m_next;
}

//Setters

//Name: SetName
//Desc: Sets m_name to name
void Item::SetName(string name){
	m_name=name;
}

//Name: SetTime
//Desc: Sets m_time to time
void Item::SetTime(int time){
	m_time=time;
}

//Name: SetNext
//Sets m_next to next
void Item::SetNext(Item* next){
	m_next=next;
}

