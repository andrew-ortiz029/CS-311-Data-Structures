#include <iostream>
using namespace std;
#include "stack_L_T.h"

//methods to check chars
bool isNum(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

// infix to postfix
string infixToPostfix(string pre, string post, Stack<char> s)
{
	// loop throught the input string
	for (int i = 0; i < pre.length(); i++)
	{
		// get char at index i
		char temp = pre[i];

		// check for invalid character
		if (!isNum(temp) && !isOperator(temp))
		{
			throw("The expression is in a wrong format");
		}
		
		// now create postfix notation
		// check if num first, else is operator
		if (isNum(temp))
		{
			post += temp;
		}
		else if (s.empty()) // if the stack is empty just push the operator 
		{
			s.push(temp);
			if (s.getTop() == ')')
			{
				throw("The expression is in a wrong format");
			}
		}
		else 
		{
			// check for '(' ')' first becuase it has the higest precedence
			if (temp == '(')
			{
				s.push(temp);
			}
			else if (temp == ')')
			{
				// while loop to pop and append to post until we get to a '('
				// try to get top and throw underflow if fail
				try {
					while (s.getTop() != '(')
					{
						char currentPop = s.getTop();
						post += currentPop;
						s.pop();
					}
					s.pop(); // pop the '('
				}
				catch (Stack<char>::Underflow)
				{
					throw("The expression is in a wrong format");
				}
			}
			// check for next precedence '*' '/'
			else if (temp == '*' || temp == '/')
			{
				// check top for same precedence, pop and append if it is then push temp
				try {
					// while condition is true for precedence pop and append to post
					int precedence = 1;
					while (precedence == 1)
					{
						if (s.empty() || s.getTop() == '(' || s.getTop() == '+' || s.getTop() == '-') // stop and push if current char is +- or ( or empty
						{
							precedence = 0;
							s.push(temp);
						}
						else // else pop the operator and append it to post
						{
							char currentPop = s.getTop();
							post += currentPop;
							s.pop();
						}
					}
				}
				catch (Stack<char>::Underflow)
				{
					throw("The expression is in a wrong format");
				}
			}
			// check for last precedence '+' '-'
			else if (temp == '+' || temp == '-')
			{
				// check top for same precedence, pop and append if it is then push temp
				try {
					// while condition is true for precedence pop and append to post
					int precedence = 1;
					while (precedence == 1)
					{
						if (s.empty() || s.getTop() == '(') // stop and push if current char is ( or empty
						{
							precedence = 0;
							s.push(temp);
						}
						else // else pop the operator and append it to post
						{
							char currentPop = s.getTop();
							post += currentPop;
							s.pop();
						}
					}
				}
				catch (Stack<char>::Underflow)
				{
					throw("The expression is in a wrong format");
				}
			}
		}
	}

	//pop the remainder of the stack and append
	while (!s.empty())
	{
		char currentPop = s.getTop();
		post += currentPop;
		s.pop();
	}

	// return postfix string
	return post;
}

// calculation of postfix
float calculatePost(string post, Stack<float> s)
{
	float answer = 0;

	// iterate through the post fix string to calculate 
	try
	{
		for (int i = 0; i < post.length(); i++)
		{
			char temp = post[i];

			// check temp for num and push
			if (isNum(temp))
			{
				float num = temp - '0'; // convert from char to int
				s.push(num);
			}
			else // when temp is operator pop two values and then compute and push it back to the stack
			{
				float op2 = s.getTop(); // op2 gets the top cause its first in last out
				s.pop();
				float op1 = s.getTop();
				s.pop();

				// find which operator and compute and push
				if (temp == '*')
				{
					op1 = op1 * op2;
					s.push(op1);
				}
				else if (temp == '/')
				{
					op1 = op1 / op2;
					s.push(op1);
				}
				else if (temp == '+')
				{
					op1 = op1 + op2;
					s.push(op1);
				}
				else
				{
					op1 = op1 - op2;
					s.push(op1);
				}
			}
		}
		// answer gets what should be the last value of stack and then pop
		answer = s.getTop();
		s.pop();
	}
	catch (Stack<float>::Underflow)
	{
		throw("The expression is in a wrong format");
	}
	// throw exception if the stack is not empty
	if (!s.empty())
	{
		throw("The expression is in a wrong format");
	}

	return answer;
}


int main()
{
	// first create our stack for postfix
	Stack<char> s;

	// ask for userinput

	string infix;
	//cout << "Enter an infix expression: " << endl;
	cin >> infix;

	// create postfix
	string postfix = "";

	Stack<float> stackInt;
	float answer = 0;

	// convert to postfix and calculate 
	try 
	{
		postfix = infixToPostfix(infix, postfix, s);
		cout << postfix << endl;
		answer = calculatePost(postfix, stackInt);
		cout << answer << endl;
	}
	catch(const char* msg)
	{
		cout << msg << endl;
	}

	return 0;
}