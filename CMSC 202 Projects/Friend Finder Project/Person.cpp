/*****************************************
** File:    Person.cpp
** Project: CMSC 202 Project 2, Fall 2021
** Author:  Agransh Srivastava
** Date:    10/13/2021
** Section: 14
** E-mail:  asrivas1@umbc.edu 
** Description: This fiel contains the Person information
******************************************/
//Libraries including Person.h
#include <iostream>
#include <string>
#include "Person.h"

using namespace std;

//default constructor
Person::Person() {}

//default constructor with parameters
Person::Person(string fname, string lname, int age, int ID) : m_fName(fname),m_lName(lname),m_age(age),m_ID(ID),m_friendCount(0){}

//AddFriend
//adds a friend when the user asks
void Person::AddFriend(Person* new_friend){
  //Adds friend to the friends list
  if(m_friendCount < MAX_FRIENDS){
    cout<<"You are now friends with "<<new_friend -> m_fName<<"!"<<endl;
    m_friends[m_friendCount]=new_friend;
    m_friendCount++;
    //tells uf if we reached max friends
  }else{
    cout<<"Max Freind Reached"<<endl;
  }
}


//RemoveFriend
// Removes Friends from the friend list
void Person::RemoveFriend(){
  //checks if you have any friends to remove from the list
  if(m_friends[0]==NULL){
    cout<<"You don't have any friends to remove"<<endl;
    return;
  }

  //shows the list of friends and ask who do you want to remove
  DisplayFriends();
  cout<<"Who would you like to remove?"<<endl;
  
  int x;
  cin >> x;

  //Error checking
  if(x<0 || x>=MAX_FRIENDS || m_friends[x-1]==NULL){
    cout<<"ERROR Reinsert another action"<<endl;
    return;
  }

  //removes friend from the roster using member variables
  Person* p_toRemove = m_friends[x-1];

  bool move=false;
  Person* next_person;

  //iteratres through the friend count
  for(int i=0;i<m_friendCount;i++){
    next_person=m_friends[i+1];

    // checks to see if toRemove is equal to m_friends
    //move is set to true
    if(p_toRemove==m_friends[i]){
      move=true;
    }

    //this if will remove that person from the list and set that equal to NULL
    if(move){
      if(i!=m_friendCount-1){
        m_friends[i]=m_friends[i+1];
      }else{
        m_friends[i]=NULL;
        m_friendCount--;
      }
    }

  }
}


//CheckID
//This function will check if the person has friends
bool Person::CheckID(int ID){
  //this checks if person has frinends
  if( m_friends[0]!=NULL){
    for(Person* person:m_friends){
      if(person -> m_ID==ID){
        return true;
      }
    }
  }else{
    cout<<"Error, no friends"<<endl;
    return false;
  }

  return false;
}

//Person
//Displays the user's friends list
void Person::DisplayFriends(){
  //Check if person has frinends
  if( m_friends[0]!=NULL){
    cout<<endl<<"Friend List for "<<m_fName<<endl;
    //This loop prints out the users friends that they chose
    for(int i=1;i<=m_friendCount;i++){
      cout
      <<i
      <<". "
      <<m_friends[i-1]->m_fName
      <<" "
      <<m_friends[i-1]->m_lName
      <<" ("
      <<m_friends[i-1]->m_age
      <<") "
      <<m_friends[i-1]->m_ID
      <<endl;
    }
  }else{
    cout<<"You don't have any friends yet"<<endl;
    return;
  }
}

//DisplayDetails
//Displays details about a specific person from the friends list
void Person::DisplayDetails(){
  //if m_ID is 0 then display error
  if(m_ID==0){
    cout<<"Error, no information about this person"<<endl;
    return;
    //else it will display all of that individuals info
  }else{
    cout
    <<m_fName
    <<" "
    <<m_lName
    <<" ("
    <<m_age
    <<" yrs) "
    <<m_ID
    <<endl;
  }
}


//SetDetails
//Sets up all the member variables up
void Person::SetDetails(std::string fname, std::string lname, int age, int ID){
  m_fName=fname;
  m_lName=lname;
  m_age=age;
  m_ID=ID;
}

