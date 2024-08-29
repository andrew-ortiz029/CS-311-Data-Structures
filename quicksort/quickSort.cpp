/**********************************
Templated created by Kazumi Slott
CS311

Your name: Andrew Ortiz
Your programmer number: 25
Hours spent: 1
Any difficulties?: none
***********************************/
#include <iostream>
using namespace std;
#include "swap.h"

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
}

int partition(int ar[], int start, int end)
{
    //I have 3 variables: pivot, i and swap_index. You may have any local variables.
    int pivot = end;
    int swap_index = start;

    //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).
    mySwap(ar[end], ar[(start + end) / 2]); // i couldn't get this to work properly inside of partition (it would unsort my list last step) 
    //For implementation of this function, refer to my lecture notes "quick sort". 
    //If you used a different algorithm, I would assume you cheated and give you zero points.
    for (int i = start; i < end; i++)
    {
        if (ar[i] < ar[pivot])
        {
            mySwap(ar[swap_index], ar[i]); // swap red and green (lecture notes)
            swap_index++; // increment red after swapping
        }
    }

    mySwap(ar[pivot], ar[swap_index]); // swap red and pivot (lecture notes) this would put all elements less than the pivot to the left

  //This function returns the index where the pivot value went in.
    return swap_index;
}

void quickSort(int ar[], int start, int end)
{
  
  if(end - start >= 1) //If the partition has only one element or none, return. 
                   //In other words, if the partition has at least 2 elements, go inside the if.
                   //use start and end to figure out how many elements you have in the partition.
    {
      //printAr(ar, end+1);
      //call partition.
      int pivot = partition(ar, start, end);
      //quickSort on the left partition
      quickSort(ar, start, pivot - 1);
      //quickSort on the right partition
      quickSort(ar, pivot + 1, end);
    }
    return;
  
}

int main()
{
  int ar[] = {15, 10, 5, 7, 1, 4, 12, 8, 6};
  quickSort(ar, 0, 8);
  printAr(ar, 9); //1 4 5 6 7 8 10 12 15

  int ar1[] = {1, 7, 5, 3, 9, 4};
  quickSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  quickSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
