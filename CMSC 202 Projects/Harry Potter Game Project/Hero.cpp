//Name: Hero.cpp
//Project: CMSC 202 Project 5, Fall 2021
//Author:  Agransh Srivastava
//Date:    12/6/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains Heros and their functions


//libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "Hero.h"

using namespace std;

//Default constructor
Hero::Hero(){}

//Overloaded Constructor
Hero::Hero(string name, string desc, int hp, int combat, int rarity){
  //initializing member variables
  m_name=name;
  m_desc=desc;
  m_combat=combat;
  m_hp=hp;
  m_rarity=rarity;
}

//Name:GetCombat
//REturns combat value of the hero
int Hero::GetCombat(){
  return m_combat;
}

//Name:GetHp
//Returns hero's hit points
int Hero::GetHp(){
  return m_hp;
}

//Name:GetRarity
//Returns hero's rarity
int Hero::GetRarity(){
  return m_rarity;
}

//Name:GetName
//Returns the name of the hero
string Hero::GetName(){
  return m_name;
}

//Name:GetDesc
//Returns description of the hero
string Hero::GetDesc(){
  return m_desc;
}

//Name:SetHp
//Sets m_hep to newHP
void Hero::SetHp(int newHp){
  m_hp=newHp;
}

//Name:SetCombat
//Sets m_combat to newCombat
void Hero::SetCombat(int newCombat){
  m_combat=newCombat;
}

//Name:Train
//Increases combat value of the hero by 10
void Hero::Train(){
  m_combat+=10;
}

//Name: Attack
//Displays attack details
void Hero::Attack(){
  cout<<m_name<<" waves their wand and screams \"Sectumsempra\"!"<<endl;
}

//Overloaded << opperator
ostream& operator<<(ostream& os, Hero &myHero){
  os<<myHero.GetName()<<"(hp:"<<myHero.GetHp()<<" combat:"<<myHero.GetCombat()<<")";
  return os;
}