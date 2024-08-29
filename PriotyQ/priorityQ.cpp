/******************************************************
Template prepared by Kazumi Slott
CS311
Emergency room program - application of priority queue

If you decide to use my getNum(), you need to compile your program as follows.
g++ -std=c++11 priorityQ.cpp //stoi requires to be compiled with c++11

Program description: This program utilizes minHeap to create a queue based on first in first out and severity of injury
Your name: Andrew Ortiz
Your programmer number: 25
Hours spent making this application: 2
Are you rejecting invalid inputs?: yes
Any difficulties: none
********************************************************/
#include <iostream>
#include <stdexcept>//for exception, invalid_argument
#include <string>//for stoi()
using namespace std;
#include "minHeap.h"
//#include "/cs/slott/cs211/checkInput.h" //You might want to check this header to see if you could use getData(min, max, errorMessage). You don't have to use it.

//I made a total of 5 functions in addition to main(). You can make as many functions as you need.
void showMenu();
int getNum();
void checkIn(minHeap<int>& patients, int patientNum);
void seePatient(minHeap<int>& patients);


const int START = 1000; //assuming this number will not go over 9999

int main()
{
  //call showMenu() to show the menu

	minHeap<int> patients(1000); // create patients

  //You need to have the following prompt somewhere. You can move it to a different function.
  //cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
	
	// open the emergency room
	bool run = true;
	int patientNum = START; // patient counter

	while (run == true) // this loop handles inputs and directs the functions to be called
	{
		showMenu(); // displays menu
		bool validInput = false; // runs second while loop till valid input is read
		int choice = 0; // handles user choice

		while (validInput == false) // test if the input is valid and keep asking for a new input
		{
			choice = getNum();

			if (choice == 1 || choice == 2 || choice == 3)
			{
				validInput = true;
			}
			else
			{
				cout << "Invalid choice. The choice should be 1, 2, 3. ";
			}
		}

		if (choice == 1)
		{
			checkIn(patients, patientNum);
			patientNum++;
		}
		else if (choice == 2)
		{
			seePatient(patients);
		}
		else if (choice == 3)
		{
			run = false;
		}
	}

  return 0;
}

void checkIn(minHeap<int>& patients, int patientNum) // handles patient check ins
{
	bool validInput = false; 
	int num;

	while (validInput == false) // get valid input
	{
		cout << "Enter a severity, 1 most severe, .. 5 least severe: ";
		string choice; 
		cin >> choice;
		
		try
		{
			num = stoi(choice); //convert a C++ string to an integer.
		}
		catch (invalid_argument)
		{
			cout << "Your choice has to be a number. ";
		}

		if (num == 1 || num == 2 || num == 3 || num == 4 || num == 5)
		{
			validInput = true;
		}
		else
		{
			cout << "Invalid choice. The choice should be 1, 2, 3, 4, 5. " << endl;
		}
	}

	// concantenate integers and pass to a final patient num
	string severity = to_string(num);
	string currentPatient = to_string(patientNum);
	string fullNum = severity + currentPatient;
	int patient = stoi(fullNum);

	try
	{
		patients.insert(patient); // insert the patient now
	}
	catch (minHeap<int>::Overflow)
	{
		cout << "There are too many patients in queue." << endl;
	}

	cout << patients << endl;
}

void seePatient(minHeap<int>& patients) // handles which patient to be seen first
{
	try
	{
		int patient = patients.getMin();
		cout << patient << " is going to be treated now" << endl;
		cout << patients << endl;
	}
	catch (minHeap<int>::BadIndex)
	{
		cout << "Bad index" << endl;
	}
}

//Show the menu
void showMenu()
{
  cout << "---------------------------------------------------" << endl;
  cout << "1: Patient Check in" << endl;
  cout << "2: Doctor takes a next patient" << endl;
  cout << "3: End" << endl;
}

//You don't need to use this function. If you decide to use it, compile your program using -std=c++11 (check my homework instructions)
//This function rejects non-integers. It returns an integer only.
int getNum()
{
   string choice; //For example, when asking for 10, the user enters ab 
   bool bad;
   int num;

   do
     {
       bad = false;
       cout << "Enter a number: ";
       cin >> choice; 

       try
	 {
	   num = stoi(choice); //convert a C++ string to an integer. stoi() is in string.h of c++ version 11
	 }
       catch(invalid_argument) //stoi() throws an exception if it cannot convert the string to an integer. E.g. "ab" cannot be an integer.
	 {
	   cout << "Your choice has to be a number. ";
	   bad = true;
	 }
     }while(bad == true);

   return num;
}


