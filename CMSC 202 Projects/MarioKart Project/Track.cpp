//Name: Track.cpp
//Project: CMSC 202 Project 4, Fall 2021
//Author:  Agransh Srivastava
//Date:    11/18/21
//Section: 14
//Email: asrivas1@umbc.edu
//Desc: This file contains pieces of Tracks for the game


//libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Track.h"


using namespace std;

//Default constructor
Track::Track(){}

//Destructor
Track::~Track(){
    for(int i=0;i<m_track.size();i++){
        delete m_track[i];
        }
    }

//Name: LoadTrack
//loads in tracks from the given files
void Track::LoadTrack(string fileName){
    string current_info[4];

    ifstream database;


    //reads in the file
    database.open (fileName, ifstream::in);
     string data = "";

    int x=0;

    while(getline(database, data)){
        if(x==0){
            this->m_name=data;
            x++;
    }
    
    if(x==1){
        this->m_name=data;
        x++;
    }
    
    if(x==2){
        string values[4];
        int currIndex = 0, i = 0;  
        int startIndex = 0, endIndex = 0;



      //Separate all the 4 values and insert them in values array
        while (i <= data.length()){
            if ( (currIndex!=4) & (data[i] == '|' || i == data.length()))  { 
            endIndex = i;  
            string subStr = "";  
            subStr.append(data, startIndex, endIndex - startIndex);  
            values[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;
            }
         i++;
        }

      //Create the piece and insert it in the track
        if(values[1]!=""){
            Piece* newPiece= new Piece(stoi(values[0]),values[1],stoi(values[2]),stoi(values[3]));
            this->m_track.push_back(newPiece);
            }
        }
    }
    //closes the file
    database.close();

    cout<<"Opened File"<<endl;

    int totDistance=0;

    //sets m_totalLength to total distance
    for(Piece* piece : this->m_track){
        totDistance+=piece->m_length;
        }
        this->m_totalLength=totDistance;
    }

//Name: GetPiece
//Returns the corresponding distance of the piece  
int Track::GetPiece(int distance){
    int totDistance=0;
    int index=0;
    //sets total distance to m_length
    for(Piece* piece : this->m_track){
        totDistance+=piece->m_length;
        //returns index if totDistance is greater than or equal to distance
        if(totDistance>=distance){
            return index;
        }
        index++;
        }

        return m_track.size()-1;
    }

//Name: DisplayPiece
//Retrusn the descriptiojn for a particualr piece of the track
string Track::DisplayPiece(int index){
    //checks if index is greater than track size
    if(index>=m_track.size()){
        //returns the description at that given track size
        return this->m_track.at(m_track.size()-1)->m_desc;
    }else{
        //else returns the desc at that index
        return this->m_track.at(index)->m_desc;
  }
}

//Name: GetMaxSpeed
//Gets max speed at a specific index
double Track::GetMaxSpeed(int index){
  return this->m_track.at(index)->m_maxSpeed;
}

//Name: GetTotalLength
//Returns total length of the track
int Track::GetTotalLength(){
  return this->m_totalLength;
}

//Name: GetDesc
//Gets description
string Track::GetDesc(){
  return this->m_desc;
}
