/**************************************************************************
~/cs311/stack_L_T_client.cpp
Implemented by Kazumi Slott
9-2-2021
Testing my stack_L_T.h - stack implemented with a linked list with an exception class
**************************************************************************/
#include <iostream>
using namespace std;
#include "stack_L_T.h"

int main()
{
	
	Stack<int> s;

	s.push(1);
	s.push(2);

	s.pop();
	s.pop();

	try 
	{
		s.pop();
	}
	catch(Stack<int>::Underflow)
	{
		cout << "Stack is empty" << endl;
	}

	try 
	{
		s.getTop();
	}
	catch (Stack<int>::Underflow)
	{
		cout << "Stack is empty" << endl;
	}

	for (int i = 1; i <= 50; i++)
	{
		s.push(i);
	}

	cout << s << endl;

	Stack<int> s1(s);

	cout << s1 << endl;

	Stack<int> s2;
	s2 = s;

	cout << s2 << endl;

	return 0;
}
