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
  void min_heapify(int i);
  void build_min_heap(); //no need to implement this. We won't use it for our application.
  void bubbleUp(int i);
  void insert(const T& el);
  int find(const T& key) const;
  void remove(int i);
  T getMin();

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
void minHeap<T>::min_heapify(int i)
{
    int l = (2 * i) + 1; //the index of the left child of i
    int r = (2 * i) + 2; //the index of the right child of i
    int smallest = i;

  //look for the smallest among 3 elements at i, l and r. smallest gets the index of the smallest value.
  //Make sure l and r don't go over the heap's range. 
  //I have 4 lines of code here. You can have more or less.
    if (ar[l] < ar[smallest] && l < num) // if left is greater than the value at i and less than n
    {
        smallest = l;
    }
    if (ar[r] < ar[smallest] && r < num) // if right is greater than the value at i and less than n
    {                                // not else if because we want r to be larger
        smallest = r;
    }

    //The smallest is either the right or left child. We need to exchange the parent with it.
    if (smallest != i) // if the smallest is not equal to i (the parent) then swap
    {
        //exchange the 2 values
        T temp = ar[i];
        ar[i] = ar[smallest];
        ar[smallest] = temp;

        //There might be a violation at the position that was exchanged. Call max_heapify to fix it.
        min_heapify(smallest);
    }
}

template <class T>
void minHeap<T>::build_min_heap()
{
    //for each non-leaf node
    //call min_heapify (turn the smallest subtrees into min-heaps and work your way up)
    for (int i = num / 2 - 1; i >= 0; i--)
    {
        min_heapify(i);
    }
}

template <class T>
void minHeap<T>::bubbleUp(int i)
{
    int start = i / 2 - 1;
    bool bubble = true;
    while (bubble == true)
    {
        min_heapify(start);
        start = start / 2 - 1;
        if (start < 0)
        {
            bubble = false;
        }
    }
}

template <class T>
void minHeap<T>::insert(const T& el)
{
    if (num >= capacity) // throw overflow if it at max capacity
    {
        throw Overflow();
    }
    else
    {
        ar[num] = el; // next index gets the value inserted
        num++;
        bubbleUp(num); // remax heap 
        //build_min_heap();
    }
}

template <class T>
void minHeap<T>::remove(int i)
{
    if (i >= num || i < 0) // if i is above n or less than 0 index is invalid
    {
        throw BadIndex();
    }
    else
    {
        T temp = ar[i];
        ar[i] = ar[num - 1];
        ar[num - 1] = temp; // swap last and remove index

        num--; // shift n to heap
        build_min_heap();
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
T minHeap<T>::getMin()
{
  //This function removes the top element and returns it.
  //You should be calling remove()
    T min = ar[0];
    remove(0);

    return min;
}

#endif
