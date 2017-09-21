'''
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void OpenFiles(ifstream&,ofstream&);
void closeFiles(ifstream&,ofstream&);

int main()
{
  //Open files
    ifstream infile;
    ofstream outfile;
    OpenFiles(infile,outfile);
  
  //Declare variables
      int shipX , shipY;
      int asteroidX ,asteroidY;
      double size;
      int collect;
      
  //prompt user
      cout << "Enter coordinates of spaceship"<<endl;
      
  //User enters initial position of spaceship(keyboard)
      cin >> shipX >> shipY;
  
  //Read file for asteroids' location and size
      while(!infile.eof())
        {
          infile >> asteroidX  >> asteroidY >> size;
        }
  
  //Prompt user
      cout<<"How many asteroids should the spacship collect?"<<endl;
      
  //User inputs number of asteroids that need to be collected(keyboard)
      cin >> collect;
  
  //Check if there are enough asteroids in the file for desired amount
  
  //"Turn on spaceship" and let it fulfill responsibilities
  
  //Output number of asteroids collected
  
  //Ouput order in which asteroids were collected
  
  //Ouput order in asteroids' sizes
  
  //Output total distance
  
  //Output total size of asteroids
  
  
  //Close files
  
  return 0;
}

void CloseFiles(ifstream &infile, ofstream &outfile)
{
    infile.close();
    outfile.close();
}

void OpenFiles(ifstream &infile, ofstream &outfile)
{
    string ifile = "input.txt";
    infile.open(ifile);
    
    string ofile = "output.txt";
    outfile.open(ofile);
}
'''
