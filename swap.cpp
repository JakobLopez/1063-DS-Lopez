//Jakob Lopez
//This program uses a templated non-member
//function to swap the value of two argument

#include<iostream>
using namespace std;


template<class T>
void swapVal(T &arg1, T &arg2)
{
  T temp = arg1;
  
  arg1 = arg2;
  
  arg2 = temp;
  
}


int main()
{
  int a = 2;
  int b = 3;
  
  
  cout<<a<<endl;
  cout<<b<<endl;
  cout<<endl;
  
  swapVal(a,b);
  
  cout<<a<<endl;
  cout<<b<<endl;
  cout<<endl;
  
  
  string c = "Hello";
  string d = "World";
    
  cout<<c<<endl;
  cout<<d<<endl;
  cout<<endl;
  
  swapVal(c,d);
    
  cout<<c<<endl;
  cout<<d<<endl;
  cout<<endl;
  
  char e = 'A';
  char f = 'B';
  
  cout<<e<<endl;
  cout<<f<<endl;
  cout<<endl;
  
  swapVal(e,f);
    
  cout<<e<<endl;
  cout<<f<<endl;
  cout<<endl;

  system("pause");
  return 0;
}
