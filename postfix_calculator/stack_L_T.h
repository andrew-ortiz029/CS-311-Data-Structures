/***********************************
Template created by Kazumi Slott
CS311
Stack implemented with a LL

Your name here: Andrew Ortiz    
Your programmer number here: 25
Hours spent: 3 hours
Any problems you had? Explain here:
###### Don't forget to specify the complexity above each function. ######
******************************************************************************************************************/
#ifndef STACK_L_T_H
#define STACK_L_T_H

#include <iostream> 
using namespace std;

template < class T > //forward declaration needed so we can make stack class a friend of node
class Stack;

template < class T > //forward declaration needed so we can make operator<< a friend of node and Stack
ostream& operator<<(ostream& o, const Stack<T>& s);


template < class T >
class Node
{
  friend class Stack<T>; //Stack class accesses the private members of Node
  friend ostream& operator<< <T>(ostream& o, const Stack<T>& s); //operator<< accesses the private members of Node

 private:
  T elem;
  Node<T>* next;  //check how right and left pointers are declared in BST class --> /cs/slott/cs211/BST_T.h
 public:
     Node() { next = NULL; } //default constructor
     Node(const T& e) { elem = e; next = NULL; } //You should set next to NULL too.
};

template <class T>
class Stack
{
  friend ostream& operator<< <T>(ostream& o, const Stack& s); //operator<< accesses the private members of Stack

 private:
  //pointer to the top element of our stack (this address is how we access our stack)
     Node<T>* top;
 
 //helper functions - private because they won't be called from client
  void destroy();
  void copy(const Stack& source);

 public:
  Stack() { top = NULL; } //Implement a small function inside the class definition 
  Stack(const Stack& other);
  ~Stack();
  Stack& operator=(const Stack& rhs); //rhs = right hand side of the operator   LHS_obj = RHS_obj
  bool empty() const { return top == NULL; } //implement a small function inside the class definition
  void push (const T& val);
  void pop();
  T& getTop(); //Return type is T& so client can change the top value
  const T& getTop() const; //A const object needs to call a const member function

  //Make an empty exception class here. Underflow or/and Overflow? - You need to figure out where to throw an exception - I am throwing in 3 functions.
  class Underflow {};
};


//Complexity of this operation: O(1)
template <class T>
void Stack<T>::push(const T& val)
{
   //FYI, I have 3 lines of code here. You may have less or more.
   //To make a new Node when the Node class is a template class, check insertNode() in /cs/slott/cs211/BST_T.h 
   
    Node<T>* temp = new Node<T>(val); //create a temp node with the parameter value
    temp->next = top; // assign next to the current value of top (if it was empty then it gets NULL)
    top = temp; //assign new node to top
    //cout << val << "\n";
    //cout << top << "\n";
}



//Complexity of this operation: O(1)
template <class T>
void Stack<T>::pop()
{
  //throw an exception if the stack is empty. (You shouldn't call pop if the stack is empty.)
    if (empty()) // call empty funciton and if empty throw underflow
    {
        throw Underflow();
    }
  //if not empty then continue with a pop
    Node<T>* temp = top; // create a temp node and assign to top
    top = top->next; // assign top to the next node
    
    //cout << temp->elem << "\n";
    delete temp; // free memory from top
}



//Complexity of this operation: O(1)
template <class T>
T& Stack<T>::getTop()
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
   if (empty()) // call empty funciton and if empty throw underflow
    {
        throw Underflow();
    }

   return top->elem; //return the top element. Since the return type is T&, the client can change the top.
}



//Complexity of this operation: O(1)
template <class T>
const T& Stack<T>::getTop() const
{
  //thrown an exception if the stack is empty. You shouldn't call getTop if empty.
    if (empty()) // call empty funciton and if empty throw underflow
    {
        throw Underflow();
    }

    return top->elem; // same as the getTop() above. We need to provide this so a const object can call getTop(). Recall a const object can only call const member functions.
}




//This function will show all the elements in the stack in the following format.
//cout << stackObj; <== This cout is calling the following function. same as operator<<(cout, stackObj); 
//Recall operator<< cannot be a member function because the LHS of the operator (<<) is not a stack object (it's cout, an ostream object). 
//     --- Top ---
//     2
//     1
//     --- Bottom ---

//Complexity of this operation: O(n)
template <class T>
ostream& operator<<(ostream& o, const Stack<T>& s)
{
  //print from top to bottom.
  cout << "--- Top ---" << endl;
  
  Node<T>* temp = s.top; // create a temp node pointer that gets the value of the top pointer
  while (temp != NULL) // iterate till temp gets to the bottom
  {
      o << temp->elem << "\n"; // print value
      temp = temp->next; // give temp the address of the next node
  }
  cout << "--- Bottom ---" << endl;
 
  return o;
}



template <class T>
Stack<T>::~Stack()
{
  destroy(); 
}

//helper function - called from destructor and operator=
//Complexity of this operation: O(n)
template<class T>
void Stack<T>::destroy() //This function will be called by destructor and operator=
{
  //destroy all nodes
  //while stack is not empty pop until its gone (pop already deletes the node when its done
      //throw an exception if the stack is empty. (You shouldn't call pop if the stack is empty.)
    while (top != NULL) // while top isn't null just pop and pop will delete the node
    {
        pop();
    }
}


//Complexity of this operation: O(n)
template <class T>
Stack<T>& Stack<T>::operator=(const Stack& rhs) //rhs = right hand side of the operator
{
  //good reading from cal tech
  //http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html
  //Notice that the returned reference is not declared const (Stack<T>&). 
  //This can be a bit confusing, because it allows you to write crazy stuff like this: (s1 = s2) = s3;


  //deep copy
    if (top == rhs.top) //Check the addresses of the left and right objects. If they are the same, you are trying to assign the same object   s = s;
    {
        return *this; //You copy only if the left object is not the same as the right object.
    } 
    {
      //destroy any memory space "this" is using. "this" may have elements already. call destroy
      //I already call destroy in my copy function if top is not NULL
      //call copy
      copy(rhs);
    }
  return *this; //return the "this" object (not the address of the "this" object). Notice the return type is not void. 
                  //By returning the this object, we can use multiple assignment operators. 
                  //s1 = s2 = s3; same as s1 = s2.operator=(s3);  Now you can see why operator=() needs to return the this object (s2). 
}



//Complexity of this operation: O(n)
//helper fuction. called from operator= and copy constructor
template <class T>
void Stack<T>::copy(const Stack& source) //source is the stack object copied from. 
{
  //"this" object ends up having the same values from source
  //Make sure this function won't crush when the source stack is empty. If the source stack is empty, "this" stack is also empty 
  //The complexity of this function should be O(n). If you implement this function by calling push(), the complexity will probably be O(n^2).
  //Make this function without calling push().

    //check if source is empty first
    if (source.empty())
    {
        destroy();
        top = NULL;
        return;
    }

    //destroy THIS stack first if not empty that way the copy can work properly
    if (top != NULL)
    {
        destroy();
    }

    Node<T>* temp = source.top; // create a new node pointer that points to source stack top
    Node<T>* current = new Node<T>(temp->elem); // create a new node pointer that gets source stacks top
    current->next = top; // assign current next to NULL
    top = current; //assign new node to top

    current->elem = temp->elem; // give new pointers element the value of top
    temp = temp->next; // give temp the address of the next node in source stack to account for line before

    while (temp != NULL)
    {
        Node<T>* n = new Node<T>(temp->elem); // new node with the current value of source stack
        current->next = n; // current next gets the value of the pointer just created
        current = current->next; // current pointer gets the address of the node just created (the next is now null).
        temp = temp->next; // give temp the address of the next node in source stack
    }

}



//copy constructor
template <class T>
Stack<T>::Stack(const Stack& other)
{
  //This is a copy constructor. This new object will get the same values as the other object. 
  //You still need to initialize the data member, top.
    top = NULL; // initialize top

  //Then you can call the copy function
    copy(other);
}



#endif // end the definition here
