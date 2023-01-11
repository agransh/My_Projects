/*****************************************
** File:    Organization.cpp
** Project: CMSC 202 Project 2, Fall 2021
** Author:  Agransh Srivastava
** Date:    10/13/2021
** Section: 14
** E-mail:  asrivas1@umbc.edu 
** Description: This file contains Organization informationof the user including the name of the people
** their Id's and their age. We fill up a roster using this function as well as store information regarding 
**  wether the user wants to add anyone from the list to their friends list.
******************************************/
//Libraries including Person.h and Organization.h
#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"
#include "Organization.h"

using namespace std;

//This line will get the user desired file
Organization::Organization():m_fileName(FILE_NAME),m_numRoster(0){}


//len
//finds the length of the string
int len(string str)  
{  
    int length = 0;  
    for (int i = 0; str[i] != '\0'; i++)  
    {  
        length++;  
          
    }  
    return length;     
}  

//Create Person
//this function will create a person list  
Person createPerson(string str, char seperator)  
{  
  string values[4];
  int currIndex = 0, i = 0;  
  int startIndex = 0, endIndex = 0;  
  //this loop runs until i reaches the end of str
  while (i <= len(str)){  
    if (str[i] == seperator || i == len(str))  {  
      endIndex = i;  
      string subStr = "";  
      //adds the current value, start of index and the lenght of the indext to the list
      subStr.append(str, startIndex, endIndex - startIndex);  
      values[currIndex] = subStr;  
      currIndex += 1;  
      startIndex = endIndex + 1;
    }
    i++;
  }
  //stores value in a variable p
  Person p(values[0],values[1],stoi(values[2]),stoi(values[3]));

  return p;
}  

//Set Name
//This function helps set the name for the user organization
void Organization::SetName(){

  string name;
  cout<<"Set A Name For The Organization:"<<endl;
  cin>>name;

  m_name=name; 
}

//Load Roster
//this function will Load the roster of people from the user given file
void Organization::LoadRoster(){
  string name;
  cout<<"Select A Name For The Organization Load File:"<<endl;
  cin>>name;
  m_fileName=name;

  //code for opening the file and reading in the file data
  ifstream database;
  string values[4];
  int i=0;
  database.open (m_fileName, ifstream::in);
  string data = "";
  //This loop will store the people from the text file into the roster
  while(getline(database, data))
  {
    m_roster[i]= createPerson(data,',');
    i++;
  }
  database.close();

  cout<<i<<" people loaded into the roster"<<endl;

}

//DisplayRoster
//This function will display the roster that was made with the people in it
void Organization::DisplayRoster(){
  //Error check, chekcs if the file loaded is empty or not
    if(sizeof(m_roster)==0){
    cout<<"The Organization Hasn't Been Loaded:"<<endl;
    return;
  }
  // This for loop will display the details of the person from the roaster
  int i=1;
  for(Person person:m_roster){
    cout<<i<<". ";
    person.DisplayDetails();
    i++;
  }
}

//GetPerson
//This function will check if the people from the text file got loaded and also ask the user who
//they want to friend
Person* Organization::GetPerson(){
  //Error checking for empty roster
    if(sizeof(m_roster)==0){
    cout<<"The Organization Hasn't Been Loaded:"<<endl;
    return NULL;
  }
  DisplayRoster();
  //Asks user who they want to friend
  int n;
  cout<<"Who would you like to friend?"<<endl;
  cin>>n;
  return &(m_roster[n-1]);
}




