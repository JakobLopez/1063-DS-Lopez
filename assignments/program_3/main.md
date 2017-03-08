```
#include<iostream>
#include<string>
using namespace std;

class convert
{
private:
	int size;
	char *S;
	int top;
	char *Q;
	int front;
	int rear;
	int count;
	

public:
	convert(int length)
	{
		size = length;
		top = -1;
		front = rear = 0;
		S = new char[size];
		Q = new char[size];
		count = 0;
	}

	void stackpush(char in)
	{
		if (empty())
		{
			S[++top] = '(';

			if (digit(in))
				queuepush(in);
			if (in == '(')
				S[++top] = in;
		}
		else
		{
			// cannot get to work
			/*if (in == ' ')
				return;*/
			if (digit(in))
				queuepush(in);

			else if (in == '(')
				S[++top] = in;

			else if (op(in))
			{
				while (determine_precedence(S[top], in) && !empty() && S[top] != '(')
					queuepush(pop());
				
				S[++top] = in;
			}

			else if (in == ')')
			{
				while (S[top] != '(')
					queuepush(pop());

				pop();
			}
		}
		if (op(in) || digit(in))
			count++;
	}

	void queuepush(char post)
	{
		Q[rear++] = post;
	}
	

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
		else
			return flag;
		return flag;
	}

	char pop()
	{
		if (!empty())
			return S[top--];
		else
			return '(';
	}


	bool determine_precedence(char a, char b)
	{
		if (a == '*' || a == '/' || a == '%')
			return true;

		else if (b == '*' || b == '/' || b == '%')
			return false;

		return true;

	}

	bool empty()
	{
		return top == -1;
	}

	void print()
	{
		//displays stack
		for (int i = top; i >= 0; i--)
		{
			cout << S[i] << " ";
		}
		cout << endl;

		//displays queue
		for (int x = 0; x < count; x++)
		{
			cout << Q[x] << " ";
		}
		cout << endl;





	}

};



int main()
{
	string equation;

	cin >> equation;
	equation += ")";
	int num = equation.length();

	convert i(num);

	//reads individual characters of string to the stack
	for (int j = 0; j < num; j++)
	{
		char h = equation[j];
		i.stackpush(h);
	}
	i.print();

	system("pause");
	return 0;
}
```
