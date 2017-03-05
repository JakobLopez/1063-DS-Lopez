```
#include<iostream>
#include<string>
using namespace std;

class stack
{
private:
	string *eq;
	int size;
	int top;
	int bot;
public:
	stack(int n)
	{
		size = n + 2 ;
		top = -1;
		eq = new string[size];
	}

	void push(char in)
	{
		if (empty())
		{
			eq[++top] = '(';
			eq[size - 1] = ')';
			eq[++top] = in;
		}
		else 
		{
			eq[top] = in;
		}
		top++;
	}

	bool empty()
	{
		return top == -1;
	}
	bool full()
	{
		return top == size - 1;
	}
	void print()
	{
		cout << top << endl;
		for (int i = top; i >= 0; i--)
		{
			cout << eq[i] << " ";
		}
		cout << endl;
		
	}
	

};

int main()
{
	string infix;
	int num = infix.length();

	cin >> infix;

	stack i(num);

	//reads individual characters of string to the stack
	for (int j = 0; j < infix.length(); j++)
	{
		char h = infix[j];
		i.push(h);
	}
	i.print();


	system("pause");
	return 0;
}
```
