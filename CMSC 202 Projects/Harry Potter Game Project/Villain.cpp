//Name: Villian.cpp
//Project: CMSC 202 Project 5, Fall 2021
//Author:  Agransh Srivastava
//Date:    12/6/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Villians and their functions

//libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Villain.h"

using namespace std;

//default constructor
Villain::Villain(){
  
}

//Villian overloaded constructor
Villain::Villain(string name, string desc, int hp, int combat, int rarity){
  m_name=name;
  m_desc=desc;
  m_combat=combat;
  m_hp=hp;
  m_rarity=rarity;
}

//Name: GetCombat
//returns the combat value of the villian wizard  
int Villain::GetCombat(){
  return m_combat;
}

//Name:GetHp
//REturns the hp of the villian
int Villain::GetHp(){
  return m_hp;
}

//Name: GetRarity
//Gets the rarity of teh villian
int Villain::GetRarity(){
  return m_rarity;
}

//Name:GetName
//Returns thename of the Villian
string Villain::GetName(){
  return m_name;
}

//Name:GetDesc
//Returns the description of the villian
string Villain::GetDesc(){
  return m_desc;
}

//Name:SetHp
//Sets the hp of the villian
void Villain::SetHp(int newHp){
  m_hp=newHp;
}

//Name: SetCombat
//Sets the combat value of the villian
void Villain::SetCombat(int newCombat){
  m_combat=newCombat;
}

///Name:Attack
//Displays the villians attack details
void Villain::Attack(){
  cout<<m_name<<" waves their wand and screams \"Sectumsempra\"!"<<endl;
}

//Overloaded << operator
ostream& operator<< (ostream& os, Villain &myVillain){
  os<<myVillain.GetName()<<"(hp:"<<myVillain.GetHp()<<" combat:"<<myVillain.GetCombat()<<")";
  return os;
}