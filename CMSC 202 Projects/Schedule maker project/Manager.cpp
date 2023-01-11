//Name: Manager.cpp
//Project: CMSC 202 Project 3, Fall 2021
//Author:  Agransh Srivastava
//Date:    10/26/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file helps make implimentations for class functions as well as uses menu
//      in order to perform the intended user funciton

//includes for calling Item,Schedule and Manager .h files
#include "Item.h"
#include "Schedule.h"
#include "Manager.h"

//libraries
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

//Name: Manager
//Accesses the Manager class to read files and calls MainMenu
//Manager is a public method of class Manager
Manager::Manager(string fileName):m_fileName(fileName){

  ReadFile();
  MainMenu();
}

//Name: ~Manager 
//Class call to delete schedules when the program ends
Manager::~Manager(){
  //deletes the schedules
  for(int i=0;i<m_schedules.size();i++){
    delete m_schedules[i];
  }

  cout<<"Deleting Schedules"<<endl;
  cout<<"Schedules removed from memory"<<endl;
}

//Name: DisplaySchedules
//This function will display the Schedules available
void Manager::DisplaySchedules(){
  //loops through each schedule, derefrences them and then displayes them
  for(Schedule* schedule : m_schedules){
    cout << *schedule;
  }
}

//Name: ReadFile
//This Manager class call will use the ReadFile function to read the contents of the specified file
// and located nodes
void Manager::ReadFile(){
 
  //Create a var to help the schedule push_back
  string current_info[4];

  ifstream database;

 
 //Reads in data from the file
  database.open (m_fileName, ifstream::in);
  string data = "";

  int nodes=0;

  //Reads data from the files and sets their values
  while(getline(database, data)){
    
    string values[3];
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;


    //Separate all the 3 values from the file and insert them in values array
    while (i <= data.length()){
      //Seperates data according to the ; 
      if (data[i] == ';' || i == data.length())  { 
        endIndex = i;  
        string subStr = "";  
        subStr.append(data, startIndex, endIndex - startIndex);  
        values[currIndex] = subStr;  
        currIndex += 1;  
        startIndex = endIndex + 1;
      }
    i++;
    }

    //Create the item and inserts it in the right schedule
    if(values[1]!=""){
      nodes++;
      //Derefrences newItem here
      Item* newItem= new Item(values[2],stoi(values[1]));
      int k=FindSchedule(values[0]);
      //Checks if k is equal to -1 and adds a new schedule to the list
      if(k==-1){
        //derefrences newSchedule and inserts it into the sorted list
        Schedule* newSchedule=new Schedule(values[0]);
        m_schedules.push_back(newSchedule);
        newSchedule->InsertSorted(newItem);
      }else{
        m_schedules[k]->InsertSorted(newItem);
      }
    }
  }
  //closes the database
  database.close();



  cout<<"Opened File"<<endl;
  cout<<nodes<<" nodes loaded across "<<m_schedules.size()<<" schedules."<<endl;
}

//Name: InsertNewItem
//Inserts NewItems into the schedule
//InsertNewItem is a public method of class Manager
void Manager::InsertNewItem(){
  string scheduleName,activityName;
  int scheduleTime;
  //Asks user for the name of the acticity, where the user would want it inserted and the time  of the activity
  cout<<"What is the name of the schedule you would like to insert into?"<<endl;
  cin>>scheduleName;
  cout<<"What is the start time of the activity?"<<endl;
  cin>>scheduleTime;
  cout<<"What is the name of the activity?"<<endl;
  cin>>activityName;
  //Derefrences newItem here
  Item* newItem= new Item(activityName,scheduleTime);

  int i=FindSchedule(scheduleName);

  //checks if i is -1 in order to derefrence schedules and add them to the 
  //m_schedules list or else put them into InsertSorted
  if(i==-1){
    Schedule* newSchedule=new Schedule(scheduleName);
    m_schedules.push_back(newSchedule);
    newSchedule->InsertSorted(newItem);
  }else{
    m_schedules[i]->InsertSorted(newItem);
  }



}

//Name: FindSchedule
//FindSchedule is a public method of class Manager
//Uses the function FindSchedule to  find the number of schedules
int Manager::FindSchedule(string schedName){
  //This loops runs through the whole schedules list and returns the schedules
  for(int i=0;i<m_schedules.size();i++){
    if(m_schedules[i]->GetName()==schedName){
      return i;
      i++;
    }
  }
  return -1;
}

//Name: MainMenu
//MainMenu is a public method of class Manager
//Displayes the main menu to the user and takes in the users choice in order to perform
//the appropriate action
void Manager::MainMenu(){
  int choice=-1;
  //runs until user exits the program (choice 4 in this case)
  //also asks for users choice
  while(choice!=4){
    cout<<"What would you like to do?:"<<endl;
    cout<<"1. Display Schedules"<<endl;
    cout<<"2. Reverse Schedules"<<endl;
    cout<<"3. Insert New Item"<<endl;
    cout<<"4. Exit"<<endl;
    cin>>choice;
    //Here switich cases are used in order to perform the appro
    switch(choice){
      case 1:{
        DisplaySchedules();
      }
      break;
      case 2:{
        ReverseSchedule();
      }
      break;
      case 3:{
        InsertNewItem();
      }
      
      break;
    }
  }
}

//Name: ReverseSchedule
//ReverseSchedule is a public method of class Manager
//Reverses a given schedule and saves it in m_schedules
void Manager::ReverseSchedule(){
  //this loop calls ReverseSchedule function which Reverses a given schedule and tells the user when its done reversing
  for(int i=0;i<m_schedules.size();i++){
    m_schedules[i]->ReverseSchedule();
    cout<<"Done reversing Schedule "<<m_schedules[i]->GetName()<<endl;
  }
}
