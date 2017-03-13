/**
* @ProgramName: Infix Calculator
* @Author: Jakob Lopex
* @Description:
*     This program uses an array to implement a basic stack and queue.
*	  The stack represents the infix equation and pops the characters
*	  to a queue in order to represent the postfix equation.
*	  After the postfix equation is made, the characters are pushed
*     back onto the stack in order to be evaluated.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: Mar 2017
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class convert
{
private:
	int size;

	////////////////Stack/////////////////////
	char *S;
	int top;
	int paranthesis_num;
	//////////////////////////////////////////

	////////////////Queue/////////////////////
	char *Q;
	int front;
	int rear;
	int count;
	//////////////////////////////////////////
	
	/////////////Result Stack/////////////////
	double *newS;
	//////////////////////////////////////////
public:
	convert(int Size)
	{
		size = Size;

		////////////////Stack/////////////////////
		top = -1;
		S = new char[size];
		paranthesis_num = 0;
		//////////////////////////////////////////
		
		////////////////Queue/////////////////////
		front = rear = 0;
		Q = new char[size];
		count = 0;
		//////////////////////////////////////////
		
		/////////////Result Stack/////////////////
		newS = new double[size];
		//////////////////////////////////////////
		
		
	}

	/**
	* @FunctionName: stack
	* @Description:
	*     Pushes character onto a stack and then pops them onto a queue.
	*	  Converts infix to postfix.
	* @Params:
	*    char in - single character of equation
	* @Returns:
	*    void
	*/
	void stack(char in)
	{
		//pushes beginning paranthesis and deals with first character read 
		if (empty())
		{
			//pushes left paranthesis to beginning of stack
			S[++top] = '(';

			//pushes digit character on to queue  
			if (digit(in))
				queue(in);
			//pushes paranthesis on to stack 
			if (in == '(')
				S[++top] = in;
		}
		else
		{
			if (digit(in))
				queue(in);

			else if (in == '(')
			{
				S[++top] = in;
				//updates count for number of paranthesis
				paranthesis_num++;
			}

			else if (op(in))
			{
				while (!empty() && S[top] != '(' && determine_precedence(S[top], in))
					//pops and pushes top from stack to queue
					queue(pop());
				//pushes on to stack	
				S[++top] = in;
			}

			else if (in == ')')
			{
				//update paranthesis count
				paranthesis_num++;
				//pops everything from stack and pushes to queue until left paranthesis
				while (S[top] != '(')
					queue(pop());
				//pops remaining paranthesis
				pop();

			}
		}

	}

	/**
	* @FunctionName: queue
	* @Description:
	*     adds a character to the queue. Contains the postfix equation.
	* @Params:
	*    char post - single character from stack
	* @Returns:
	*    void
	*/
	void queue(char post)
	{
		//pushes argument onto queue and updates rear
		Q[rear++] = post;

		count++;
	}

	/**
	* @FunctionName: _queue
	* @Description:
	*     dequeues items from the queue into a new stack
	* @Params:
	*    none
	* @Returns:
	*    void
	*/
	void _queue()
	{
		while (!emptyQ())
		{
			//sends dequeued character to new stack
			if (digit(Q[front]))
				_stack(dequeue());
			//sends dequeued operator onto new stack
			else
				_stack(dequeue());	
		}
	}

	/**
	* @FunctionName: _stack
	* @Description:
	*     pushes digits onto a stack and then, when an operator is encountered,
	*	  calculates the top two numbers.
	*	  Result is displayed when queue is empty
	* @Params:
	*    char postfix - single character from the queue
	* @Returns:
	*    void
	*/
	void _stack(char postfix)
	{
		if (digit(postfix))
		{
			//gets integer value
			double number_value = postfix - 48;

			//puts integer value on stack
			newS[++top] = number_value;
			
		}
		else if (op(postfix))
		{
			//pops top two numbers into variables
			double x = _pop();
			double y = _pop();
			double result = 0.0;

			if (postfix == '+')
			{
				result = y + x;
				newS[++top] = result;
			}
			else if (postfix == '-')
			{
				result = y - x;
				newS[++top] = result;
			}
			else if (postfix == '*')
			{
				result = y * x;
				newS[++top] = result;
			}
			else if (postfix == '/')
			{
				result = y / x;
				newS[++top] = result;
			}
			else if (postfix == '%')
			{
				result = (int)y % (int)x;
				newS[++top] = result;
			}
			else if (postfix == '^')
			{
				result = pow(y, x);
				newS[++top] = result;
			}

			//last value in stack is the answer
			if (emptyQ())
				cout << result << endl;
		}
	}

	/**
	* @FunctionName: digit
	* @Description:
	*     determines if a character is a digit
	* @Params:
	*    char in - single character from infix equation
	* @Returns:
	*    bool - true if digit / false otherwise
	*/
	bool digit(char in)
	{
		bool flag = false;

		if (in == '0')
			flag = true;
		else if (in == '1')
			flag = true;
		else if (in == '2')
			flag = true;
		else if (in == '3')
			flag = true;
		else if (in == '4')
			flag = true;
		else if (in == '5')
			flag = true;
		else if (in == '6')
			flag = true;
		else if (in == '7')
			flag = true;
		else if (in == '8')
			flag = true;
		else if (in == '9')
			flag = true;
		else
			return flag;
		return flag;

	}

	/**
	* @FunctionName: op
	* @Description:
	*     determines if a character is an operator
	* @Params:
	*    char in - single character from infix equation
	* @Returns:
	*    bool - true if operator / false otherwise
	*/
	bool op(char in)
	{
		bool flag = false;

		if (in == '+')
			flag = true;
		else if (in == '-')
			flag = true;
		else if (in == '/')
			flag = true;
		else if (in == '*')
			flag = true;
		else if (in == '%')
			flag = true;
		else if (in == '^')
			flag = true;
		else
			return flag;
		return flag;
	}

	/**
	* @FunctionName: pop
	* @Description:
	*     Returns a character from the top of the stack
	* @Params:
	*    None
	* @Returns:
	*    char - returns top of stack
	*/
	char pop()
	{
		if (!empty())
			return S[top--];
		else
			return ' ';
	}

	/**
	* @FunctionName: _pop
	* @Description:
	*     Returns an integer value from the top of the stack
	* @Params:
	*    None
	* @Returns:
	*    int - returns top of stack
	*/
	double _pop()
	{
		if (!empty())
			return newS[top--];
		else
			return -1;
	}

	/**
	* @FunctionName: empty
	* @Description:
	*     Checks to see if stack is empty.
	* @Params:
	*    None
	* @Returns:
	*    bool - true if empty / false otherwise
	*/
	bool empty()
	{
		return top == -1;
	}

	/**
	* @FunctionName: fullQ
	* @Description:
	*     determines if queue is full
	* @Params:
	*    none
	* @Returns:
	*    bool - true if full / false otherwise
	*/
	bool fullQ()
	{
		if (rear == size - paranthesis_num)
			return true;
		else
			return false;
	}

	/**
	* @FunctionName: emptyQ
	* @Description:
	*     determines if queue is empty
	* @Params:
	*    none
	* @Returns:
	*    bool - true if empty / false otherwise
	*/
	bool emptyQ()
	{
		if (front == rear)
			return true;
		return false;
	}

	/**
	* @FunctionName: dequeue
	* @Description:
	*     Returns front of queue and then updates front
	* @Params:
	*    None
	* @Returns:
	*    char - returns front of queue
	*/
	char dequeue()
	{
		if (emptyQ())
		{
			cout << "Queue Empty!" << endl;
			return false;
		}
		char Temp = Q[front];
		//update front
		front = (front + 1) % size;
		count--;
		return Temp;
	}

	/**
	* @FunctionName: determine_precedence
	* @Description:
	*     determines if operator in stack has precedence over infix character
	* @Params:
	*    char a - operator in the stack
	*	 char b - operator being read in
	* @Returns:
	*    bool - true if precedence / false otherwise
	*/
	bool determine_precedence(char a, char b)
	{
		if (a == '*' || a == '/' || a == '%' || a == '^')
			return true;

		else if (b == '*' || b == '/' || b == '%' || b == '^')
			return false;

		return true;

	}


	
};

/*
This main reads each individual character from an infix equation
for a specified number of times. The equation is displayed along
with the result.
*/
int main()
{
	string equation;
	ifstream infile;
	infile.open("exp.txt");

	int numSet;

	//reads in amount of loops
	infile >> numSet;
	

	for (int index = 0; index < numSet; index++)
	{
		//reads equation
		infile >> equation;

		cout << equation;

		//appends ending paranthesis to equation
		equation += ")";

		double num = equation.length();

		//calls instance of class convert
		convert i(num);

		//	reads individual characters of string to the stack
		for (int j = 0; j < num; j++)
		{
			char h = equation[j];
			i.stack(h);
		}

		cout << " = ";
		//calls queue once it is full and displays answer
		i._queue();
	}

	infile.close();
	system("pause");
	return 0;
}
