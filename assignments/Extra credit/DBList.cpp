```
//Jakob Lopez
//String Stack
#include<iostream>
#include<string>
using namespace std;

class Stack
{
  private:
    string *S;
    int Top;
    int Size;
  public:
    Stack(int size)
    {
      Size = size;
      Top = -1;
      S = new string[Size];
    }
    
    void Push(string x)
    {
      if(!Full())
        S[++Top] = x;
      else
        cout<< "Stack over flow"<<endl;
    }
    
    string Pop()
    {
      if(!Empty())
        return S[Top--];
      else
        return "?";
    }
    
    bool Full()
    {
      return Top == Size - 1;
    }
    
    bool Empty()
    {
      return Top == - 1;
    }
    
    void print()
    {
      for(int i = Top; i > -1 ; i--)
      {
        cout<<S[i]<<endl;
      }
    }  
};

int main()
{
  Stack stack(5);
  
  //testing Stack methods
  stack.Push("food");
  stack.Push("dog");
  stack.Push("mom");
  stack.Push("bike");
  stack.Push("money");
  stack.print();
  cout<<endl;
  stack.Pop();
  stack.print();
  
  
  return 0;
}

```
