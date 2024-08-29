/*****************************************************
Template prepared by Kazumi Slott
CS311
min heap class

Your name: Andrew Ortiz
Your programmer number: 25
Hours spent making and testing your min heap class: 1
Any difficulties?: no
*******************************************************/
#ifndef MINHEAP_H
#define MINHEAP_H
#include <iostream> //for operator<<()
using namespace std;


template <class T>
class minHeap;

template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h);

template <class T>
class minHeap
{
  friend ostream& operator<< <T>(ostream& o, const minHeap<T>& h);
private:
  T* ar; //dynamic array
  int capacity; //the size of ar
  int num; //the number of elements I have in ar
public:
  minHeap(){ar = NULL; capacity = 0; num = 0;}
  minHeap(int c);
  ~minHeap(){if(ar!=NULL)delete [] ar;}
  void min_heapify(int* curDist, int* locator, int i);
  void build_min_heap(int* curDist, int* locator); //no need to implement this. We won't use it for our application.
  void bubbleUp(int* curDist, int* locator, int i);
  void insert(const T& el, int* curDist, int* locator);
  int find(const T& key) const;
  void remove(int* curDist, int* locator, int i);
  T getMin(int* curDist, int* locator);
  int getNum() const;
  void fixHeap(int* curDist, int* locator, int i);

  class Overflow{};
  class BadIndex{};
  class NotFound{};
};


//You need to implement all the memeber functions above.  Don't forget operator<<().
template <class T>
ostream& operator<<(ostream& o, const minHeap<T>& h)
{
    if (h.num == 0)
    {
        cout << "The queue has none" << endl;
        return o;
    }
    
    cout << "The queue has ";
    for (int i = 0; i < h.num; i++)
    {
        o << h.ar[i] << " ";
    }
    return o;
}

template <class T>
minHeap<T>::minHeap(int c) // im assuming were creating a minHeap the size of c
{
    capacity = c;
    num = 0;
    ar = new T[c];
}

template <class T>
void minHeap<T>::min_heapify(int* curDist, int* locator, int i)
{
    int l = (2 * i) + 1; //the index of the left child of i
    int r = (2 * i) + 2; //the index of the right child of i
    int smallest = i;

  //look for the smallest among 3 elements at i, l and r. smallest gets the index of the smallest value.
  //Make sure l and r don't go over the heap's range. 
  //I have 4 lines of code here. You can have more or less.
    if (curDist[ar[l]] < curDist[ar[smallest]] && l < num) // if left is greater than the value at i and less than n
    {
        smallest = l;
    }
    if (curDist[ar[r]] < curDist[ar[smallest]] && r < num) // if right is greater than the value at i and less than n
    {                                // not else if because we want r to be larger
        smallest = r;
    }

    //The smallest is either the right or left child. We need to exchange the parent with it.
    if (smallest != i) // if the smallest is not equal to i (the parent) then swap
    {
        //swap locations 
        locator[ar[i]] = smallest;
        locator[ar[smallest]] = i;
        
        //exchange the 2 values in to be Checked
        T temp = ar[i];
        ar[i] = ar[smallest];
        ar[smallest] = temp;

        //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
        min_heapify(curDist, locator, smallest);
    }
}

template <class T>
void minHeap<T>::build_min_heap(int* curDist, int* locator)
{
    //for each non-leaf node
    //call min_heapify (turn the smallest subtrees into min-heaps and work your way up)
    for (int i = num / 2 - 1; i >= 0; i--)
    {
        min_heapify(curDist, locator, i);
    }
}

template <class T>
void minHeap<T>::bubbleUp(int* curDist, int* locator, int i)
{
    int parent = (i-1) / 2;

    while (curDist[ar[i]] < curDist[ar[parent]]) // bubble up as long as the distance is lower
    {

        locator[ar[i]] = parent;
        locator[ar[parent]] = i; // fix the locator

        //exchange the 2 values in to be Checked
        T temp = ar[i];
        ar[i] = ar[parent];
        ar[parent] = temp;

        i = parent;
        parent = (i - 1) / 2;
    }
}

template <class T>
void minHeap<T>::insert(const T& el, int* curDist, int* locator)
{
    if (num >= capacity) // throw overflow if it at max capacity
    {
        throw Overflow();
    }
    else
    {
        ar[num] = el; // next index gets the value inserted
        num++;
        if (num > 1)
        {
            bubbleUp(curDist, locator, num - 1); // bubble up if needed 
        }
        //build_min_heap();
    }
}

template <class T>
void minHeap<T>::remove(int* curDist, int* locator, int i)
{
    if (i >= num || i < 0) // if i is above n or less than 0 index is invalid
    {
        throw BadIndex();
    }
    else
    {
        locator[ar[i]] = num - 1;
        locator[ar[num - 1]] = i; // fix locator


        T temp = ar[i];
        ar[i] = ar[num - 1];
        ar[num - 1] = temp; // swap last and remove index

        num--; // shift n to heap

        fixHeap(curDist, locator, i);
    }
}

template <class T>
int minHeap<T>::find(const T& key) const
{
  for(int i = 0; i < num; i++) 
    if(ar[i] == key)
      return i;

  //The element doesn't exist 
  throw NotFound();// "The element doesn't exist";                                                                                             
}

template <class T>
T minHeap<T>::getMin(int* curDist, int* locator)
{
  //This function removes the top element and returns it.
  //You should be calling remove()
    T min = ar[0];
    remove(curDist, locator, 0);

    return min;
}


/******************************************************************************
Make a copy of minHeap.h and name it minHeap-graph.h (dash not underscore)
Add the following 2 functions to your minHeap-graph.h
A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.
To see why, check minHeap::fixHeap() below.
Don't forget to include minHeap-graph.h to graph.h
******************************************************************************/

//return the number of elements in the heap.
template <class T>
int minHeap<T>::getNum() const
{
    return num;
}

//i is the index (within heap) of the vertex whose distance was changed. 
//For example, if vertex 0's distance changed when it is located at 3, i is 3. This is where the heap needs to be fixed by either going up or down.
//curDist is the array that contains the shortest distance from start to every other vertex.                                           
//locator is the array that contains the location of each vertex within the heap. Make sure you understand the homework document posted on Canvas to understand how locator works.                                               
template <class T>
void minHeap<T>::fixHeap(int* curDist, int* locator, int i)
{

    //We need to maintain the min heap based on curDist. When 2 vertices swap within the heap, their locations will change, hence you need to update the locator array. Make sure you understand how each array works by reading the homework document (there are pictures to explain). 
    //From i, either bubble up or down.                                                                                           
    //For up, call bubbleUp(). For down, call min_heapify()    
        // if i distance is less than parent call bubble up and bubble up will fix it until its in its proper space
        // even if its distance isnt less call bubble up and it will sort it out regardless

    if (i < num && i >= 0)
    {
        if (curDist[ar[i]] < curDist[ar[(i - 1) / 2]])
        {
            bubbleUp(curDist, locator, i);
        }
        else 
        {
            min_heapify(curDist, locator, i);
        }
    }

    //Reminder: A lot of the member functions in minHeap class need to have 2 more parameters, int* curDist, int* locator.
    //Since I have the same code inside minHeap::remove(), I am now calling fixHeap() from remove() so I won't have duplicate code.	
}

#endif
