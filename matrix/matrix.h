/**********************************
Template prepared by Kazumi Slott
CS311

matrix class

Replace the ?????s

For examples of matrix multiplication
https://matrix.reshish.com/multCalculation.php 

Your name:
Your programmer number:
Hours spent?:
Any difficulties?:
***********************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;

//This forward declaration of Matrix class is necessary because the following operator>> and << are using Matrix as a parameter
template <class T>
class Matrix;

//This forward declaration of operator>> is necessary Since operator<< is a template function.
template<class T>
ifstream& operator>>(ifstream& o, Matrix<T>& m);

//This forward declaration of operator<< is necessary Since operator<< is a template function.
template <class T>
ostream& operator<<(ostream& o, const Matrix<T> & m);

//Template class so we can have a matrix of any data types, int or double
template <class T>
class Matrix
{
  //friend functions so they can access the private members 
  friend ostream& operator<< <T>(ostream& o, const Matrix<T> & m);
  friend ifstream& operator>> <T>(ifstream& o, Matrix<T>& m);

private: 
  T** m; //2 dimensional dynamic array
  const int R; //number of rows
  const int C; //number of columns

public: 
  Matrix(int R, int C);
  Matrix();
  ~Matrix();
  Matrix operator*(const Matrix& other);// matrix multiplication
  class size_error{};//exception class 
};

//default constructor
template<class T>
Matrix<T>::Matrix() : R(0), C(0) //setting const R and C to initial value, 0.
{
  m = NULL;
}

//constructor to create a matrix, row x col 
template<class T>
Matrix<T>::Matrix(int row, int col) : R(row), C(col) //setting const R and C 
{
  if(row <= 0 || col <= 0)
    {
      m = NULL;
      return;
    }

  //m = new T[R][C]; //this doesn't compile
  m = new T*[R]; //create a single dimensional array of pointers of the T type
  for (int i=0; i<R; i++) //create a single dimensional array for each slot of m
    m[i] = new T[C];

  //initialize each element to 0
  for(int rw = 0; rw < R; rw++)
    for(int cl = 0; cl < C; cl++)
	m[rw][cl] = 0;
}

//fill a matrix using an input file
template<class T>
ifstream& operator>>(ifstream& fin, Matrix<T>& mrx)
{
  //itetate through indeces of the matrix and assign values to the indeces
  for(int r = 0; r < mrx.R; r++)
      for(int c = 0; c < mrx.C; c++)
          fin >> mrx.m[r][c];  
  
  return fin;
  
}

/*output the matrix to screen in the following format. Allocate 10 spaces for each value.
         1          1          1
         2          2          2
         3          3          3
         4          4          4 
*/
template<class T>
ostream& operator<<(ostream& o, const Matrix<T>& mrx)
{
    //iterate through matrix and output each value at every index
    for (int r = 0; r < mrx.R; r++)
    {
        for (int c = 0; c < mrx.C; c++)
        {
            //set width between each value to 10 and output data
            o << setw(10) << mrx.m[r][c];
        }
        // end line to achieve proper format
        cout << endl;
    }
  
   return o;
  
}

//matrix multiplication
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    //check if comparable throw exception if not
    if (C != other.R)
    {
        throw size_error();
    }
   
    //define result matrix as (R, other.C) to account for non square matrix multiplication
    Matrix<T> result(R, other.C);

    //multiply matrices with i being the current col of the m1 and j being the current row of m2 
    for (int i = 0; i < R; i++) // keeps track of what row of m1 is being multiplied to m2
    {
        for (int j = 0; j < other.C; j++) // keeps track with what column of m2 is being multiplied
        {
            for (int k = 0; k < other.R; k++) // k iterates to keep on track with the row-column rule of matrix multiplication
            {
                result.m[i][j] = result.m[i][j] + (m[i][k] * other.m[k][j]);
            } 
        }
    }

    return result;
}

//destructor                                                                                                                                                                                        
template<class T>
Matrix<T>::~Matrix()
{
  //destroy what is created in heap memory                                                                                                                          
  //if m is not NULL do the following                                   
     //HINT: delete each dynamic array pointed to by each slot of m                                                                                                                                   
     //delete m (m contains all rows)           
    if (m != NULL)
    {
        for (int i = 0; i < R; i++)
        {
            delete[] m[i]; // delete each array pointed to 
        }
        delete[] m; // delete m itself
    }
}
