//Name: Schedule.cpp
//Project: CMSC 202 Project 3, Fall 2021
//Author:  Agransh Srivastava
//Date:    10/26/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file helps make implimentations for class functions and manages all parts of the Schedule


//Libraries
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
//Including Item and Schedule
#include "Item.h"
#include "Schedule.h"
#include "Manager.h"
using namespace std;


//Setting up a constructor called Schedule with paramenters
Schedule::Schedule():m_name("Default"),m_head(nullptr),m_tail(nullptr),m_size(0){}
//Overloaded Schedule constructor with parameters
Schedule::Schedule(string name):m_name(name),m_head(nullptr),m_tail(nullptr),m_size(0){}

//Name: Schedule
//Deconstructor called schedule
//deletes the nodes once the programs finish running 
Schedule::~Schedule(){
    if(m_size==0){
        return;
    }

    //Derefrencing item here and making it point to null
    Item* currentItem=m_head;
    Item* temp=nullptr;
    //Checks if the Next item in the node is not pointing to null
    //and deletes that particular node and sets it equal to temp
    while(currentItem->GetNext()!=nullptr){
      temp=currentItem->GetNext();
      delete currentItem;
      currentItem=temp;
    }
    //Deletes tail
    delete m_tail;
}

//Name:InsertSorted
//InsertSorted is a public method of class Schedule
//Inserts the Sorted Schedules into the list of schedules by deferencing item
void Schedule::InsertSorted(Item* insertItem){
    //checks if list size is 0 in order to set up a linked list
    if(m_size==0){
        m_head=insertItem;
        m_tail=insertItem;
        m_size++;
        return;
    }

    //checks if inserItem's GetTime is less than the m_head GetTime
    if(insertItem->GetTime() < m_head->GetTime()){
      insertItem->SetNext(m_head);
      m_head=insertItem;
      m_size++;
      return;
    }
    
    //derefrences Item and sets it equal to m_head
    Item* currentItem = m_head;

    //Goes through the m_size list
    for(int i=0;i<m_size;i++){
        //derefrences each item and sets nextItem to currentItem's node 
        Item* nextItem = currentItem->GetNext();
        //checks if insertItem is greater than equal to currenItem
        if(insertItem->GetTime() >= currentItem->GetTime()){
            //checks if nextItem is equal to null in order to set the next node to insertItem
            if(nextItem == nullptr){
                currentItem->SetNext(insertItem);
                //insertItem node now becomes the tail
                m_tail=insertItem;
                m_size++;
                return;
            }else{
                //chckes if nextItem's node is greater than insertItem
                if(insertItem->GetTime() < nextItem->GetTime()){
                    //Sets the nodes accordingly
                  currentItem->SetNext(insertItem);
                  insertItem->SetNext(nextItem);
                  m_size++;
                  return;
                }
            }
        }

        currentItem = nextItem;
    }

}

//Name: GetName
//GetName is a public method of class Manager
//Returns m_name
string Schedule::GetName(){
    return m_name;
}

//Name: GetSize
//GetSizeis a public method of class Manager
//Returns m_size or the size of the list
int Schedule::GetSize(){
    return m_size;
}

//Name: ReverseSchedule
//ReverseSchedule is a public method of class Manager which reversed the schedule
void Schedule::ReverseSchedule(){
    //Derefrencing and setting nodes accordingly
    Item* currentItem = m_head;
    Item* pastItem = nullptr;
    Item* pastItemNext = nullptr;

    //Runs the loop through the linked list and reverses each node
    for(int i=0;i<m_size;i++){
        //using pastItem in order to save the next node in the reversed list
        pastItemNext=currentItem->GetNext();
        //Checks if pastItem is not equal to null and sets current item to pastItem
        if(pastItem!=nullptr){
            currentItem->SetNext(pastItem);
            //Otherwise we have reached the end of the linked list and we set it all eqal to null
        }else{
            currentItem->SetNext(nullptr);
        }
        pastItem=currentItem;
        currentItem=pastItemNext;
    }

    //Switches Tail with Head
    Item* temp=m_head;

    m_head=m_tail;

    m_tail=temp;
    return;
}

//Name: GetData
//Derefrenced Iteam class using Getdata to return data from the nodes
Item* Schedule::GetData(int nodeNum){

    //Returns null if nodeNum is greater than the size of the list
    if(nodeNum>m_size){
        return nullptr;
    }

    //Derefrences Item last and sets it equal to m_head
    Item* last=m_head;

    //This loops until the nodeNum and sets the name of the last node to GetNext
    for(int i=0;i<nodeNum;i++){
        last=last->GetNext();
    }

    return last;

}


//Ostream function to define a method and use schedule
ostream &operator<<(ostream &output, Schedule &mySchedule){

    //checks for nodes
    if(mySchedule.m_size==0){
        output<<"No Nodes"<<endl;
        return output;
    }

    //sets Item to mySchedules m_head
    Item* currentItem=mySchedule.m_head;

    //gives the informaiton about the schedule
    output<<"Schedule for "<<mySchedule.m_name<<endl;
    output<<mySchedule.m_size<<" activities scheduled"<<endl;
    for(int i=0;i<mySchedule.m_size;i++){
        output<<currentItem->GetTime() << " : " << currentItem->GetName() << endl;
        currentItem=currentItem->GetNext();
    }

    return output;
}