/**********************************
Templated created by Kazumi Slott
CS311

Your name: Andrew Ortiz
Your programmer number: 25
Hours spent: 1 hour
Any difficulties?: none
***********************************/
#include <iostream>
using namespace std;

void printAr(const int ar[], int s)
{
 for(int i = 0; i < s; i++)
    cout << ar[i] << " ";
  cout << endl;
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

int main()
{
  int ar[] = {1, 8, 6, 4, 10, 5, 3, 2, 22}; //the array used in my lecture notes
  mergeSort(ar, 0, 8);
  printAr(ar, 9); //1 2 3 4 5 6 8 10 22

  int ar1[] = {1, 7, 5, 3, 9, 4};
  mergeSort(ar1, 0, 5);
  printAr(ar1, 6); //1 3 4 5 7 9 

  int ar2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  mergeSort(ar2, 0, 9);
  printAr(ar2, 10); //1 2 3 4 5 6 7 8 9 10

  return 0;
}
