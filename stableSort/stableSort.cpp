/***************************************                                           
Template prepared by Kazumi Slott                                                  
CS311                                                                              
This program sorts an array of persons.                                            
                                                                                   
Your name: Andrew Ortiz                                                                 
Your programmer number: 25                                                      
Hours spent: 1 hour                                                            
Any difficulties?: none                                                           
****************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "swap.h"  //<=== include your swap.h if you made it so you can call your mySwap() in stableSort(). 
                      //     If you didn't make it, you can make a swap function in this file or call the library's swap(). 
using namespace std;

const int SIZE = 13;

struct person
{
  string fN;
  string lN;
  int grade;
};

bool fillAr(person a[])
{
  ifstream fin;
  fin.open("stableSort3.in");

  if(!fin)
    {
      cout << "You don't have the input file" << endl;
      return false;
    }
  string f, l;
  int g;
  int i = 0;

  fin >> f >> l >> g;
  while(fin)
    {
      a[i].fN = f;
      a[i].lN = l;
      a[i++].grade = g;
      fin >> f >> l >> g;
    }
  fin.close();
  return true;
}

void printAr(const person a[])
{
  for(int i = 0; i < SIZE; i++)
    cout << a[i].grade << "  " << left << setw(10) << a[i].lN << setw(10) << a[i].fN << endl;
}

//You need to create some functions here, which will be called from stableSort()
bool compGrade(person p1, person p2) // sort by grade then FN then LN 
{                                    // all have the same parameters so they can be passed by stableSort
    if (p1.grade > p2.grade)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool compFN(person p1, person p2) 
{
    if (p1.fN > p2.fN) 
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool compLN(person p1, person p2)
{
    if (p1.lN > p2.lN)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void stableSort(person ar[], int SIZE, bool (&func)(person, person)) // passing our comparison fucntions as last parameter
{
  //You can use a stable sort algorithm of your choice                             
  //use the technique shown in my lecture notes "Lec on passing functions"         
  //Include your swap.h at the top so you can call your mySwap() to swap persons in this function.           
  //If you didn't make swap.h, you can make a swap function in this file or call the library's swap().
    //utilizing bubble sort because probably less code to change to make it fit stableSort
    bool swapped = true; //true if there was swapping in the current iteration, false otherwise                                   
    int last = SIZE - 2; //last is the index of the left element of the last pair to be checked in the current iteration.

    while (swapped == true) //swapping required in the previous iteration or the first iteration starts                        
    {
        swapped = false; //no swapping has happened yet when a new iteration starts.                                         

        for (int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
            if (func(ar[i], ar[i+1])) //the pair is out of order                                                          
            {
                swap(ar[i], ar[i + 1]);
                swapped = true; //swapping required - meaning we need to proceed to the next iteration.                            
            }
        }
        last--; //the area to be checked shrinks down after each iteration                                         
    }//end of while                      
}

int main()
{
  person ar[SIZE];
  if(fillAr(ar))
    {
      cout << "--- original ---" << endl;
      printAr(ar);

      //You need to sort the array here
      //HINT: call stableSort multiple times.

      stableSort(ar, SIZE, compGrade); // sort by grade first although the order they're called doesn't really matter
      stableSort(ar, SIZE, compFN);
      stableSort(ar, SIZE, compLN);

      cout << "--- result ---" << endl;
      printAr(ar);
    }
  return 0;
}


