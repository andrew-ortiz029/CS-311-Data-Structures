/*****************************************
Template written by Kazumi Slott
CS311

Your name: Andrew Ortiz
Your programmer number: 25
Hours spent: 2
Any difficulties?: understanding what bubbleUp was asking for
*******************************************/
#include <iostream>
#include <fstream>
#include <time.h> //for clock()
#include <cstdlib> //for exit()
using namespace std;
#include "sort.h"
#include "/cs/slott/cs211/checkInput.h" //for getData()

//print an integer array of size n
void print(int ar[], int n)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
  cout << endl;
}

//called from max_heapify and heapSort
void exchange(int ar[], int largest, int i)
{
  //I have 3 lines of code here.
    int temp = ar[i];
    ar[i] = ar[largest];
    ar[largest] = temp;
}

//turns a heap rooted at i into a max-heap, assuming the left and right subtrees are already max-heaps.
//n is the number of elements in the heap
void max_heapify(int ar[], int n, int i)
{
  
    int l = (2 * i) + 1; //the index of the left child of i
    int r = (2 * i) + 2; //the index of the right child of i
    int largest = i; //the index of the largest value amoung the values at i, l and r

  //look for the largest among 3 elements at i, l and r. largest gets the index of the largest value.
  //Make sure l and r don't go over the heap's range. 
  //I have 4 lines of code here. You can have more or less.
        if (ar[l] > ar[largest] && l < n) // if left is greater than the value at i and less than n
        {
            largest = l;
        }
        if (ar[r] > ar[largest] && r < n) // if right is greater than the value at i and less than n
        {                                // not else if because we want r to be larger
            largest = r;
        }

  //The largest is either the right or left child. We need to exchange the parent with it.
     if(largest != i) // if the largest is not equal to i (the parent) then swap
     {
         //exchange the 2 values
        exchange(ar, largest, i);
        //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
        max_heapify(ar, n, largest);
     }
}

//turns the entire array/tree into a max heap rooted at 0
//n is the number of elements we have in the array
void build_max_heap(int ar[], int n)
{
  //2 lines of code in this function
  //for each non-leaf node
     //call max_heapify (turn the smallest subtrees into max-heaps and work your way up)
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        max_heapify(ar, n, i);
    }
}

//a is an unordered list to start with
//use max_heapify to sort a
//n is the number of elements in the array
void heapSort(int a[], int n)
{
  //I have 6 lines of code in this function. You can have more or less.

  //build max heap from an unordered list
  //call build_max_heap
  build_max_heap(a, n);
  int size = n; //size of the unsorted portion of the array

  while(n > 0) //repeat until heap is empty
    {  
      //swap max element with last element - max element is now the last element
      exchange(a, 0, n-1);

      //root may violate max-heap property, but children are max heaps. run max_heapify to fix it.
      max_heapify(a, n-1, 0);

      //discard the last element from the heap
      n--;
    }
}

//this function corrects a violiation at i by bubbling it up to the correct place                             
//a is a heap                                                                                                
void bubbleUp(int a[], int i)
{
  //Write this function after you made insert() and while you are making remove().
    int start = i / 2 - 1;
    bool bubble = true;
    while (bubble == true)
    {
        max_heapify(a, i, start);
        start = start / 2 - 1;
        if (start < 0)
        {
            bubble = false;
        }
    }
}

//a is a max heap                                                                                            
//cap is the capacity of the heap                                                                            
//n is the number of elements the heap currently has before insertion                                        
//el is the new element to be inserted                                                                       
void insert(int a[], int cap, int& n, int el)
{
   //refer to lecture notes
  //throw "The array is full" if the array is full.
  //write this function without calling bubbleUp() first. When you work on remove(), you will notice you will
  //have to have the same code there. Move the code into bubbleUp() and call it to avoid redundancy.
    if (n == cap) // test if the array is full
    {
        throw ("The array is full");
    }
    else
    {
        a[n] = el; // next index gets the value inserted
        n++; 
        bubbleUp(a, n); // remax heap 
    }
}

//This function returns the index where key was found or throws an exception if key is not found.                                   
//a is a max heap.                                                                                 
//n is the number of elements in the heap.                                                                                
//key is the element we are looking for.                                                                                             
int find(const int a[], int n, int key)
{
  //This function is completed for you. Don't change it.

  for(int i = 0; i < n; i++)                                                                                            
    if(a[i] == key)
      return i;

  throw "The element doesn't exist";
}

//a is a max heap                                                                                            
//n is the number of elements the heap currently has before deletion, then decrememted after deletion                                         
//i is the index of the element to be removed.                                             
void remove(int a[], int& n, int i)
{
    //refer to lecture notes
    //throw "The index to be removed is invalid" if i is an invalid index.
    //Call bubbleUp or max_heapify (the lecture notes show 2 possibilities).
    //FYI, I have a total of 12 lines of code in this function. You can have more or less.
    if (i >= n || i < 0) // if i is above n or less than 0 index is invalid
    {
        throw "The index to be removed is invalid";
    }
    else
    {
        exchange(a, i, n - 1); // swap last and remove index
        n--; // shift n to heap
        build_max_heap(a, n);
    }
}

int main()
{
    clock_t start, end;
    ifstream fin;

    cout << "How many numbers do you want to put into the array?: ";
    //the number of elements we can accept is 1 to 1 million. The input file has 1 million numbers. You might want to open it to see.
    int s = getData(1, 1000000, "Please enter a number between 1 and 1000000: ");//getData() is in /cs/slott/cs211/checkInput.h
    const int MAX = 1000000; //the input file has 1000000 numbers
    int ar[MAX];
    fin.open("/cs/slott/cs311/sort.in"); //sort.in has 1000000 numbers

    //fill the array
    for (int i = 0; i < s; i++)
        fin >> ar[i];
    fin.close();

    cout << " selection sort ";
    start = clock();
    heapSort(ar, s);
    end = clock();
    
  return 0;
}
