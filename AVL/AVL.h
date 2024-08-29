/****************
Template created by Kazumi Slott
CS311

Your name: Andrew Ortiz
Your programmer number: 25
Hours spent?: 3
Any difficulties?: using the libraries classes
*****************/

#ifndef BST_H
#define BST_H
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//forward declaration of BST class. We need this because BST class is used as a friend in Node. 
//Check your stack_L_T.h if you don't know what to put here.
template <class T>
class AVL;

//Make Node and BST template classes.
//You put the class definition and member function implementations in .h when you use template.  
//If you don't know how to make them template,
//Check page 3 of CS211 "Lec Notes on Exception Handling". I have a template stack class there.
//Also you made stack_L_T.h using template at the beginning of this semester.

template <class T>  //make it a templare class
class Node
{
  friend class AVL<T>; //BST wants to access private members of Node
private:
  T el;
  Node<T>* right;
  Node<T>* left;
  int BF;
  Node<T>* up;
public:
  Node() { up = right = left = NULL; BF = 0; }; //default constructor. set right and left to NULL
  Node(const T& e) { el = e; up = right = left = NULL; BF = 0; };
  T getEl() const {return el;} //returns el
};

//Make it a template class
template <class T>
class AVL
{
private:
    Node<T>* root; //check stack_L_T.h to see how to declare top

  //You will need 10 private functions here.  WHY private?
    void inOrderPrint(Node<T>*& p);
    int getMaxLength(Node<T>*& p);
    void destroy(Node<T>* p);
    Node<T>* rightRotation(Node<T>* p);
    Node<T>* leftRotation(Node<T>* p);
    void balanceTree(Node<T>* newNode);
    Node<T>* updateBF(Node<T>* Q);

 public:
     AVL() { root = NULL; } //implement constructor here
    ~AVL();
  void insertNodeI(const T& e);
  void inOrderPrint();
  int getMaxLength();
  void BFTprint();
};

//implement the member functions in the header if you are making a template class

//destructor.
//If you don't know how to make the destructor, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
AVL<T>::~AVL()
{
  destroy(root);
}

template <class T>
void AVL<T>::destroy(Node<T>* p) //private function. WHY?
{
  //destroy all nodes
    if (p == NULL)
    {
        return;
    }
    destroy(p->left);
    destroy(p->right);
    delete p;
}

//This is an insert function using iteration.
//You will see insert function using iteration is unwieldy compared to that using recursion above.
//The hemework document "HMWK BST - reveiw of cs211" has a diagram to show how this function works.
template <class T>
void AVL<T>::insertNodeI(const T& e)
{
    Node<T>* newNode = new Node<T>(e);  //Check stack_L_T.h to see how you made a new node.
    Node<T>* p = root;
    Node<T>* parent = NULL; //points to the parent of p. 

  //move p to NULL
  while(p != NULL)
    {
      //parent points to the parent node while p points to the left or right child.
      parent = p; 
      if (e < p->getEl())
          p = p->left;
      else //p->el <= e
	p = p->right;
    }

  if (parent == NULL) //tree is empty
  {
      root = newNode;
  }
  else if (e < parent->el) //insert a child as the parent's left child
  {
      parent->left = newNode;
      parent->left->up = parent; // update up now
      balanceTree(newNode); // call balance tree
  }  
  else //parent->el <= e //insert a child as the parent's left child
  {
      parent->right = newNode;
      parent->right->up = parent; // update up now
      balanceTree(newNode); // call balance tree
  }
}

template <class T>
void AVL<T>::balanceTree(Node<T>* newNode)
{
    // call updateBF and check to see if we need to balance
    Node<T>* p = updateBF(newNode);

    // if p is NULL then no need to balance tree
    if (p == NULL)
    {
        return; // do nothing
    }
    else if (p->BF == 2 && p->left != NULL && p->left->BF == 1) // LL violation
    {
        p = rightRotation(p); // call right to fix it 
    }
    else if(p->BF == -2 && p->right != NULL && p->right->BF == -1) // RR violation
    {
        p = leftRotation(p); // call left to fix it 
    }
    else if (p->BF == 2 && p->left != NULL && p->left->BF == -1) // LR violation
    {
       
        p->left = leftRotation(p->left);
        p = rightRotation(p);
    }
    else //if (p->BF == -2 && p->right != NULL && p->right->BF == 1) // RL violation
    {
        
        p->right = rightRotation(p->right);
        p = leftRotation(p); 
       
    }

    //check where the node is in tree and attach it back
    if (p->up == NULL)
    {
        root = p; // p is the new root
    }
    else if(p->el < p->up->el)
    {
        p->up->left = p;
    }
    else
    {
        p->up->right = p;
    }


}

template <class T>
Node<T>* AVL<T>::leftRotation(Node<T>* p)
{
    Node<T>* subRoot = p->right;
    Node<T>* temp = subRoot->left;

    //make the rotation
    p->right = temp;

    if (subRoot->left != NULL) // update this up before it gets overwritten
    {
        subRoot->left->up = p;
    }

    subRoot->left = p;

    //update ups
    subRoot->up = p->up;
    p->up = subRoot;

    //update BF 
    p->BF = getMaxLength(p->left) - getMaxLength(p->right);
    subRoot->BF = getMaxLength(subRoot->left) - getMaxLength(subRoot->right);

    //update root
    if (subRoot->up == NULL)
    {
        this->root = subRoot;
    }

    return subRoot;
}

template <class T>
Node<T>* AVL<T>::rightRotation(Node<T>* p)
{
    Node<T>* subRoot = p->left;
    Node<T>* temp = subRoot->right;

    //make the rotation
    p->left = temp;
    
    if (subRoot->right != NULL) // update this up before it gets overwritten
    {
        subRoot->right->up = p;
    }

    subRoot->right = p;

    //update ups
    subRoot->up = p->up;
    p->up = subRoot;

    //update BF 
    p->BF = getMaxLength(p->left) - getMaxLength(p->right);
    subRoot->BF = getMaxLength(subRoot->left) - getMaxLength(subRoot->right);

    //update root
    if (subRoot->up == NULL)
    {
        this->root = subRoot;
    }

    return subRoot;
}

template <class T>
Node<T>* AVL<T>::updateBF(Node<T>* Q)
{
    Node<T>* q = Q;
    Node<T>* parent = Q->up;
    
    if (q->up != NULL) // update if Q isnt the Root
    {
        if (q == parent->left)
        {
            parent->BF++;
        }
        else
        {
            parent->BF--;
        }
    }
    
    while (parent->up != NULL && parent->BF != -2 && parent->BF != 2) // find a violation or find the root
    {
        q = parent;
        parent = parent->up;

        if (q->BF == 0)
        {
            return NULL;
        }
        if (q == parent->left)
        {
            parent->BF++;
        }
        else
        {
            parent->BF--;
        }
    }

    if (parent->BF == -2 || parent->BF == 2) // if theres a violation return parent node 
    {
        return parent;
    }

    return NULL; // return NULL if no violation
}

//If you don't how to make this, check the following
//CS211 Lec notes on BST recursive functions - destroy and in order traversal
//CS211 Lecture recording - Lecture 4/28(Wed) - BST:: inOrderPrint(), destroy()

template <class T>
void AVL<T>::inOrderPrint()
{
    inOrderPrint(root);
}

template <class T> //private function. WHY?
void AVL<T>::inOrderPrint(Node<T>*& p)
{
    if (p == NULL)
    {
        return;
    }
    inOrderPrint(p->left);
    cout << p->el << "-->";
    inOrderPrint(p->right);
}

//This function return the maximum length from the root. If there is only one node, this function returns 1.
template <class T>
int AVL<T>::getMaxLength()
{
    return getMaxLength(root);
}

template <class T>
int AVL<T>::getMaxLength(Node<T>*& p) //private function. Why?
{
    if (p == NULL)
    {
        return 0;
    }
    
    int l = getMaxLength(p->left);
    int r = getMaxLength(p->right);

    if (l > r)
    {
        return l + 1;
    }
    else
    {
        return r + 1;
    }
}


template <class T>
void AVL<T>::BFTprint()  //Breadth First Traversal Print
{
  //Use the library's queue. https://cplusplus.com/reference/queue/queue/

  //Make sure to include <queue> at the top
  //create a queue obj of POINTERS to Nodes
    queue<Node<T>*> q;
  //algorithm is discussed in lecture
    q.push(root); // push root onto queue
    while (!q.empty()) // while q is not empty
    {
        Node<T>* p = q.front();
        q.pop(); //pop first element
        
        if (p->up != NULL)
        {
            cout << p->el << " " << p->BF << " " << p->up->el << "-->"; // print the first element
        }
        else
        {
            cout << p->el << " " << p->BF << " " << "-->"; // print the first element
        }

        //now push if theres a child
        if (p->left != NULL)
        {
            q.push(p->left);
        }
        if (p->right != NULL)
        {
            q.push(p->right);
        }
    }
  //NOTICE
  //front() gives you the front element but it doesn't remove it from the queue.
  //pop() removes the front element
}

#endif
