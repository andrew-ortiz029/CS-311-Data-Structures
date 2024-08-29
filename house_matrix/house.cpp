/******************************************
Template prepared by Kazumi Slott
CS311

Description of this program: This main tests our matrix class functions via a house multiplication funtion

Your name: Andrew Ortiz
Your programmer number: 25
Number of hours you spent: 30 min
Any difficulties?: none
*******************************************/
#include <iostream>
using namespace std;
#include "matrix.h"

int main()
{
    // create our matrices 
    Matrix<double> houses(4, 4);//4 rows x 4 columns
    Matrix<double> areas(4, 3);//4 rows x 3 columns
    
    // open the house info file
    ifstream fin;
    fin.open("house_info.in");

    // load the house matrix
    cout << "filling houses ----" << endl;
    fin >> houses;
    fin.close();

    // open the house function file
    fin.open("house_func.in");
    
    // load the house fucntion file
    cout << "filling areas ----" << endl;
    fin >> areas;
    fin.close();

    // test print our matrices
    cout << "printing houses ----" << endl;
    cout << houses << endl;
    cout << "printing areas ----" << endl;
    cout << areas << endl;

    // try catch the multiplication
    try
    {
        // create a result matrix and attempt multiplication
        Matrix<double> r = houses * areas;
        cout << "result of houses * areas is ------" << endl;
        cout << r << endl;
    }
    catch (Matrix<double>::size_error) // catch and print that multiplication cannot be done
    {
        cout << "imcomparable sizes" << endl;
        cout << "---------------------------------" << endl;
    }

    return 0;
}