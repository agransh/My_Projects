/*****************************************
** File:    FriendFinder.cpp
** Project: CMSC 202 Project 2, Fall 2021
** Author:  Agransh Srivastava
** Date:    10/13/2021
** Section: 14
** E-mail:  asrivas1@umbc.edu 
** Description: This file contains Friend Finder for the project where all 
** of the user's information is taken and stored as well as the menu function is displayed
******************************************/
//Libraries
#include <iostream>
#include <string>
#include "Organization.h"
#include "Person.h"
#include "FriendFinder.h"

using namespace std;

//FriendFinder 
//This is the function where the code originally starts
FriendFinder::FriendFinder(){
  //declaring variables
  Person p;
  m_me = p;

  Organization org;
  m_organization = org;

  cout
  <<"*****************************"
  <<endl
  <<"Welcome to UMBC Friend Finder"
  <<endl
  <<"*****************************"
  <<endl;
 //calls start() to start the code
  Start();
}

//GetDetails
//This function gets the Details from the user to store them
void FriendFinder::GetDetails(){
  //Variables
  string fname,lname;
  int age,ID;
  //Gets  Frist name
  cout<<"What is your first name?"<<endl;

  cin>>fname;
  //Gets Last name
  cout <<"What is your last name?" <<endl;

  cin>>lname;
  //Gets age
  cout <<"What is your age?" <<endl;

  cin>>age;
   //Gets ID
  cout <<"What is your ID?" <<endl;

  cin>>ID;
  //Sets them in the mutator SetDetails
  m_me.SetDetails(fname,lname,age,ID);
}

//Display Menu
//This function displays all of the options that are available to user 
void FriendFinder::DisplayMenu(int &choice){
  //options for the user to choose from
  cout
  <<"What would you like to do?"
  <<endl
<<"1. Display Entire Organization"
<<endl
<<"2. Display Friend List"
<<endl
<<"3. Search for a Friend"
<<endl
<<"4. Remove Friend"
<<endl
<<"5. Exit"
<<endl;

cin>> choice;

}

//Start
//Starts the code as well as displayes your information along with the switch cases
void FriendFinder::Start(){
  //getters and setters 
  GetDetails();
  m_organization.SetName();
  m_organization.LoadRoster();
  int choice=-1;
  //this loop runs until user exits the code
  while(choice!=5){
    DisplayMenu(choice);

    //swtich cases
    switch(choice){
      //This menu choice will display the entire organization
      case 1: {
        cout<<"You Are: ";
        m_me.DisplayDetails();
        cout<<endl;
        cout<<"****UMBC****"<<endl;
        m_organization.DisplayRoster();
      }
      break;

      //This case will display you friends list(people you made friends with)
      case 2:{
        m_me.DisplayFriends();
      }
      break;

      //This case will search for a friend from the given list of people
      case 3:{
        cout<<endl;
        cout<<"****UMBC****"<<endl;
        Person* friend_to_add = m_organization.GetPerson();
        m_me.AddFriend(friend_to_add);
      }
      break;

      //This case will remove a friend from the user's friends list
      case 4:{
        m_me.RemoveFriend();
      }
      break;

      //this case exits the code
      case 5: {
        cout<<"Thank you for using UMBC Friend Finder!"<<endl;
        return;
      }
      break;
    }
  }
}
