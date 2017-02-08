```
/**
* @ProgramName: Homework-1
* @Author: Jakob Lopez
* @Description:
*     This program creates a single linked list and adds nodes to the front or end.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 02/08/2017
*/

#include <iostream>

struct Node
{
	int Data;
	Node *Next;
};

using namespace std;

class List
{
private:
	Node *Head;
	Node *Tail;
public:
	List()
	{
		Head = NULL;
		Tail = NULL;
	}

	/**
	* @FunctionName: FrontSert
	* @Description:
	*     Finds the Head pointer and adds new node to front of list
	* @Params:
	*    int x - number that is read in
	* @Returns:
	*    void
	*/
	void FrontSert(int x)
	{
		Node *Temp = new Node;
		Temp->Data = x;
		Temp->Next = NULL;
		if (!Head)
		{
			Head = Temp;
			Tail = Temp;
		}
		else
		{
			Temp->Next = Head;
			Head = Temp;
		}
		
	}

	/**
	* @FunctionName: EndSert
	* @Description:
	*     Finds the Tail pointer and adds new node to end of list
	* @Params:
	*    int x - number that is read in
	* @Returns:
	*    void
	*/
	void EndSert(int x)
	{
		Node *Temp = new Node;
		Temp->Data = x;
		Temp->Next = NULL;
		
		if (!Tail)
		{
			Head = Temp;
			Tail = Temp;
		}
		else
		{

			Tail->Next = Temp;
			Tail = Temp;
		}

	}

	/**
	* @FunctionName: PrintList
	* @Description:
	*     Prints out the linked list as long as Temp exists
	* @Params:
	*	  None
	* @Returns:
	*    void
	*/
	void PrintList()
	{
		if (!Head)
		{
			cout << "Empty" << endl;
			return;
		}
		else
		{
			Node *Temp = Head;
			while (Temp != NULL)
			{
				cout << Temp->Data << "->";
				Temp = Temp->Next;
			}
		}
	}

};


int main()
{
	srand(97097807);
	List L;
	for (int i = 0; i < 5; i++)
	{
		L.FrontSert(rand() % 100);
	}
	L.PrintList();
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		L.EndSert(rand() % 100);
	}
	L.PrintList();
	cout << endl;
	



	system("pause");
	return 0;
}
```
