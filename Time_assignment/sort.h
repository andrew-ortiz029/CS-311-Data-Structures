/**************************************
Template created by Kazumi Slott
CS311

Your name:
Your programmer number:
Hours spent:
Any difficulties?:
**************************************/

#include <iostream>
using namespace std;

void swap(string& data1, string& data2)
{
  string temp = data1;
  data1 = data2;
  data2 = temp;
}

void print(const int ar[], int n)
{
  for(int i = 0; i < n; i++)
    cout << ar[i] << " ";
}


//https://www.youtube.com/watch?v=ROalU379l3U
//Implement the insertion sort by watching the above youTube video. Your algorithm has to match their dance.
void insertionSort(int ar[], int n)
{
  //call swap
    //nested for loop iterates from beggining of array to end 
    // second while loop starts off at i and runs back until it's in its correct place
    bool sorted = false; // while loop condition
    int currentIndex; // current index being checked for swap

    for (int i = 1; i < n; i++) // starts at index 1 because there's no value left of zero
    {
        sorted = false; // always set sorted to false before loop
        currentIndex = i; // currentIndex gets the current value of i 
        
        while (sorted == false)
        {
            if (currentIndex == 0) // check to make sure loop doesn't go out of scope
            {
                sorted = true;
            }
            else if (ar[currentIndex] < ar[currentIndex - 1]) // if the value is less than the previous index then swap
            {
                swap(ar[currentIndex], ar[currentIndex - 1]); // swap the values 
                currentIndex--; // iterate down the array
            }
            else
            {
                sorted = true; // end while loop as the value is now sorted
            }
        }
    }
}


//The following function sorts the array in ascending order by moving the largest value to the end.
//Change the code so the array gets sorted in ascending order by moving the smallest value to the beginning.
//Make sure you change varibale names and comments to suit your new code.
//<REQUIREMENT> don't change the structure.
//You can find more information in my homework document
void selectionSort(int array[], int N)
{
  int smallIndx; //the index of the largest value

  //last is the last index in unsorted part
  for (int first = 0; first < N; first++)
    {
      smallIndx = N-1; //assume the last item is the smallest
      //find the smallest in unsorted part ([frist..N-1])
      for (int i = N - 1; i >= first; i--)
	{
      if (array[i] < array[smallIndx]) //The current item is smaller
	    smallIndx = i;
	}

      //swap the smallest with the first item in the unsorted part
      swap(array[smallIndx],array[first]);
    }
}


//Replace the ????s.
//For more info on bubble sort, read my CS211 lec notes "Lec notes 2-2: bubble sort"
//You could also watch my CS211 lecture recording "Lecture 2/5(Fri) - bubble sort and enum" 
void bubbleSort(int ar[], int s)
{
  
  bool swapped = true; //true if there was swapping in the current iteration, false otherwise                                   
  int last = s - 2; //last is the index of the left element of the last pair to be checked in the current iteration.

  while(swapped == true) //swapping required in the previous iteration or the first iteration starts                        
    {
      swapped = false; //no swapping has happened yet when a new iteration starts.                                         

      for(int i = 0; i <= last; i++) //check each adjacent pair of items in the unsorted part                     
        {
	  if(ar[i] > ar[i+1]) //the pair is out of order                                                          
	    {
	      swap(ar[i], ar[i+1]);
	      swapped = true; //swapping required - meaning we need to proceed to the next iteration.                            
	    }
        }
      last--; //the area to be checked shrinks down after each iteration                                         
    }//end of while                                                                                               
}


int partition(int ar[], int start, int end)
{
    //I have 3 variables: pivot, i and swap_index. You may have any local variables.
    int pivot = end;
    int swap_index = start;

    //swap the middle element with the last element first (recall this would be a good idea in case the list is sorted already).
    swap(ar[end], ar[(start + end) / 2]); // i couldn't get this to work properly inside of partition (it would unsort my list last step) 
    //For implementation of this function, refer to my lecture notes "quick sort". 
    //If you used a different algorithm, I would assume you cheated and give you zero points.
    for (int i = start; i < end; i++)
    {
        if (ar[i] < ar[pivot])
        {
            swap(ar[swap_index], ar[i]); // swap red and green (lecture notes)
            swap_index++; // increment red after swapping
        }
    }

    swap(ar[pivot], ar[swap_index]); // swap red and pivot (lecture notes) this would put all elements less than the pivot to the left

    //This function returns the index where the pivot value went in.
    return swap_index;
}

template <class T>
void quickSort(T ar[], int start, int end)
{
    if (end - start >= 1) //If the partition has only one element or none, return. 
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


void merge(int ar[], int first, int last)
{
    //For implementation of this function, refer to my lecture notes "merge sort"
    //If you are using a different technique, I assume you cheated and will give you zero points.
      //create our dynamic temp array
    int length = last - first + 1;
    int* temp = new int[length];

    //fill temp array based on left and right 
    int left = first;
    int right = (first + last) / 2 + 1;
    int mid = (first + last) / 2; // for left out of bounds
    int i = 0;

    while (i != length) // loop will run until the temp array has been filled
    {
        // check values at the left and right indeces and fill based on condition
        if (ar[left] <= ar[right])
        {
            temp[i] = ar[left];
            i++;
            left++;
        }
        else
        {
            temp[i] = ar[right];
            i++;
            right++;
        }

        //now check left and right for bounds and fill/break loop if out of bounds
        if (left > mid) // copy remaining right half
        {
            while (i != length) // will iterate i to break the main loop as well
            {
                temp[i] = ar[right];
                i++;
                right++;
            }
        }
        else if (right > last) // copy remaining left half
        {
            while (i != length) // will iterate i to break the main loop as well
            {
                temp[i] = ar[left];
                i++;
                left++;
            }
        }
    }

    //load temp array into ar
    for (int i = 0; i < length; i++)
    {
        //cout << temp[i] << endl;
        ar[first + i] = temp[i]; // match the indeces
    }

    //Don't forget to destroy temp array, which is created dynamically
    delete[] temp;
}

void mergeSort(int ar[], int first, int last)

{
    //For implementation of this function, refer to my lecture notes "merge sort"
    if (last - first > 0) // if theres at least 2 elements
    {
        int middle = (first + last) / 2; // calculate middle 
        mergeSort(ar, first, middle); // left side (first to middle)
        mergeSort(ar, middle + 1, last); // right side (middle + 1 to last)
        merge(ar, first, last);
    }

    return; // once it passes the if statement return and end the recursion 
}


