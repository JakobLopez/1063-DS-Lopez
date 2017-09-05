/**
* @ProgramName: OrderSert (Extra Credit)
* @Author: Jakob Lopez
* @Description:
*     This program performs various methods to insert or delete nodes 
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 02/26/2017
*/
#include <iostream>


#include "DBList.h"

using namespace std;

//Public 
////////////////////////////////////////////

DBList::DBList()
{
	Head = NULL;
	Tail = NULL;
}


bool DBList::InsertFront(int Data)
{
	Node* Temp = _CreateNode(Data);
	if (!Head)
	{
		Head = Temp;
		Tail = Temp;
	}
	else
	{
		Temp->Next = Head;
		Head->Prev = Temp;
		Head = Temp;
	}
	return true;
}

bool DBList::InsertRear(int Data)
{
	if (!Head)
	{
		DBList::InsertFront(Data);
	}
	else
	{
		Node* Temp = _CreateNode(Data);
		Tail->Next = Temp;
		Temp->Prev = Tail;
		Tail = Temp;
	}
	return true;
}

bool DBList::InsertInOrder(int x)
{
	if (!Head)	
		DBList::InsertFront(x);
	else
	{		
		Node* Temp = _CreateNode(x);
		Node *C = Head;
		if (x < Head->Data)
		{
			Temp->Next = Head;
			Head->Prev = Temp;
			Head = Temp;
		}
		

		else
		{
			while (C->Next)
			{
				if (x < C->Data)
				{
					C->Prev->Next = Temp;
					Temp->Prev = C->Prev;
					Temp->Next = C;
					C->Prev = Temp;
				}

				C = C->Next;
				
			}
			C->Next = Temp;
			Temp->Prev = C;
		}	
		
	}
		
	return true;
}

bool DBList::Delete(int x)
{
	//One node 
	if (Head == Tail && Head->Data == x){
		delete Head;
		Head = NULL;
		Tail = NULL;
		return true;
		//Beginning of list
	}
	else if (Head->Data == x){
		Head = Head->Next;
		delete Head->Prev;
		Head->Prev = NULL;
		return true;
		//End of list
	}
	else if (Tail->Data == x){
		Tail = Tail->Prev;
		delete Tail->Next;
		Tail->Next = NULL;
		return true;
		//Middle of list
	}
	else
	{
		Node* Location = DBList::_Find(x);
		if (Location){
			Location->Prev->Next = Location->Next;
			Location->Next->Prev = Location->Prev;
			delete Location;
			return true;
		}
	}
	return false;
}


bool DBList::Update(int x, int y)
{
	return true;
}

void DBList::Print(){
	Node *Temp = Head;
	while (Temp){
		cout << Temp->Data << " ";
		Temp = Temp->Next;
	}
}

//Private 
////////////////////////////////////////////


Node* DBList::_Find(int key)
{
	Node* Temp = Head;

	while (Temp)
	{
		if (Temp->Data == key)
		{
			return Temp;
		}
		Temp = Temp->Next;
	}
	return NULL;
}

Node* DBList::_CreateNode(int data){
	Node *Temp = new Node;
	Temp->Data = data;
	Temp->Prev = NULL;
	Temp->Next = NULL;
	return Temp;
}
