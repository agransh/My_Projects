/*****************************************
 ** File:    Proj1.cpp
 ** Project: CMSC 202 Project 1, Fall 2021
 ** Author:  Agransh Srivastava
 ** Date:    9/26/21
 ** Section: 10
 ** E-mail:  asrivas1@gumbc.edu 
 ** Description: This program will display a crossword
 ** puzzle to the user using which the user can play
 ** the game by adding coordinates and solving 
 ** the crossword 
 **
 ***********************************************/
//declaring libraries
#include <iostream>
#include <fstream>
#include <string>
#include<iomanip>
using namespace std;

//function prototypes
string Get_Filename();
bool Read_Grid(char Grid[15][15],string filename,string words[10]);
void Print_Grid(char Grid[15][15], string words[10]);
string Get_Word( char Grid[15][15], int Start_X, int Start_Y, int End_X, int End_Y);
bool Find_Word(string Word, string words[10]);

//main
int main()
{
  //declaring variables
  char Grid[15][15];
  string words[10];
  string Word=" " ;
  int Total_Words = 10;
  int Start_X, Start_Y, End_X, End_Y;
  string filename = Get_Filename();

  //reads the file from the txt file and asks user for the coordinates to find words on the crossword
  if (Read_Grid(Grid,filename,words))
    {
      while (Total_Words > 0)
	{
	  //this part gets coordinates from the user and stores them in variables
	  Print_Grid(Grid, words);
	  cout << "What is the starting X Y (seperated by space)? " << endl;
	  cin >> Start_X >> Start_Y;
	  cout << "What is the ending X Y (seperated by space)? " << endl;
	  cin >> End_X >> End_Y;

	  //checks if the coordinate is in the grid
	  if (Start_X <= 14 && Start_Y <= 14 && End_Y <= 14 && End_X <= 14 && Start_X >= 0 && Start_Y >= 0 && End_Y >= 0 && End_X >= 0)
	    {
	      //cout << "Start_X= " << Start_X << endl;
	      //cout << "Start_Y= " << Start_Y << endl;
	      //cout << "End_X= " << End_X << endl;
	      //cout << "End_Y= " << End_Y << endl;

	      Word = Get_Word(Grid, Start_X, Start_Y, End_X, End_Y);

	      //checks if the word that the user input coordinates for is on the grid
	      if (Find_Word(Word, words))
		{
		  cout << "Found the word: " << Word << "!" << endl;
		  Total_Words--;
		}
	      else
		{
		  cout << "You didn't find a word on the list" << endl;
		}

	    }
	  else
	    {
	      cout << "That Point is not in the grid" << endl;
	    }
	}
    }
  //this code executes when the file that the user entered is the wrong file
  else
    {
      cout << "Unable to create Grid" << endl;
    }
  cout << "Thank you for playing Word Search!" << endl;
}

//Get_Filename
//Gets the file that the user wants to run
string Get_Filename()

{

  string filename;
  cout << "What is name of file you want to load? " << endl;
  cin >> filename;
  return filename;
}
//returns the file name

//Read_Grid
//this will read the lines from the grid itself to find words
bool Read_Grid(char Grid[15][15],string filename,string words[10])
{
  //declaring variables
  int Total_Letters=0;
  int Total_Words = 0;
  ifstream indata;

  indata.open(filename);

  //checks for the file and if not found shows error
  if (!indata)
    {
      cout << "Error: file could not be opened" << endl;
      return false;
    }

  //temporary array to read a whole line
  char buff[100];
  for (int i = 0; i < 15; i++)
    {
      //reading whole line
      indata.getline(buff, 100, '\n');

      //counter
      int k = 0;
      //for loop to get data for grid from buff array
      for (int j = 0; j < 29; j++)
	{
	  if ((buff[j] >='a' && buff[j] <='z') || (buff[j] >= 'A' && buff[j] <= 'Z'))
	    {
	      Grid[i][k] = buff[j];
	      Total_Letters++;
	      k++;
	    }
	}
    }

  //for loops counts the total number of letters and words imported
  for (int i = 0; i < 10; i++)
    {
      indata >> words[i];
      Total_Words++;
    }
  cout << "Total Letters imported= " << Total_Letters << endl;
  cout << "Total Words imported= " << Total_Words << endl;
  return true;
}
//returns true or false

//Print_Grid
//This function will print the 15x15 grid
void Print_Grid(char Grid[15][15], string words[10])
{
  cout << "\n\n\n";
  cout << "       ";
  for (int i = 0; i < 15; i++)
    cout << i<<setw(4);
  cout << endl;
  for (int i = 0; i < 15; i++)
    {
      //cout << "   ";
      cout << i << setw(4);
      for (int j = 0; j < 15; j++)
	{
	  cout <<Grid[i][j] << setw(4);
	}
      cout << endl;
    }
  //prints the remaining words
  cout << "\n\n**************** REMAINING WORDS ********************\n" << endl;
  for (int i=0; i < 10; i++)
    {
      if(words[i]!=" ")
	cout << words[i]<<endl;
    }
}
//returns nothing

//Get_Word
//Checks the words in all 8 directions forwards and backwards
string Get_Word( char Grid[15][15], int Start_X, int Start_Y, int End_X, int End_Y)
{
  string Word;
  //checks for Horizontal Line
  if (Start_X == End_X)
    {
      if (Start_Y > End_Y)
	{
	  for (int i = Start_Y; i >= End_Y; i--)
	    {
	      Word+= Grid[Start_X][i];
	    }
	}
      else
	{
	  for (int i = Start_Y; i <= End_Y; i++)
	    {
	      Word += Grid[Start_X][i];

	    }
	}
    }

  //checks for vertical line
  else if (Start_Y == End_Y)
    {
      if (Start_X > End_X)
	{
	  for (int i = Start_X; i >= End_X; i--)
	    {
	      Word += Grid[i][Start_Y];

	    }

	}
      else
	{
	  for (int i = Start_X; i <= End_X; i++)
	    {
	      Word += Grid[i][Start_Y];

	    }
	}

    }

  //checks right down diagonal
  else if (Start_X < End_X && Start_Y < End_Y)
    {
      int k = Start_Y;
      for (int i = Start_X; i != End_X+1 && k != End_Y+1; i++,k++)
	{
	  Word += Grid[i][k];

	}
    }

  //checks right up diagonal
  else if (Start_X > End_X && Start_Y < End_Y)
    {
      int k = Start_Y;
      for (int i = Start_X; i != End_X - 1 && k != End_Y + 1; i--, k++)
	{
	  Word += Grid[i][k];

	}
    }

  //reads left down diagonal
  else if (Start_X < End_X && Start_Y > End_Y)
    {
      int k = Start_Y;
      for (int i = Start_X; i != End_X + 1 && k != End_Y - 1; i++, k--)
	{
	  Word += Grid[i][k];

	}
    }

  //checks left up diagonal
  else if (Start_X > End_X && Start_Y > End_Y)
    {
      int k = Start_Y;
      for (int i = Start_X; i != End_X - 1 && k != End_Y - 1; i--, k--)
	{
	  Word += Grid[i][k];

	}
    }
  return Word;
}
//returns the found Word

//Find_Word
//checks if the word that was requested by user through
//coordinates was found
bool Find_Word(string Word, string words[10])
{
  //this for loop checks if the word found
  //was the same as the word searched
  for (int i = 0; i < 10; i++)
    {
      if (Word == words[i])
	{
	  words[i] = " ";
	  return true;
	}
    }
  return false;
}
//returns true or false
