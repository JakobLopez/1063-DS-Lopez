```
#include<iostream>
#include<fstream>
#include<math.h>
#include "Asteroid.h"
#include "AsteroidList.h"
#include "Spaceship.h"
using namespace std;

void closeFiles(ifstream&, ofstream&);
int getNumCollect();
void initList(ifstream&,AsteroidList&);
void openFiles(ifstream&, ofstream&);
int placeShipX();
int placeShipY();
void readFile();


int main()
{
	//Declare variables

	int collect;
	int shipX, shipY;
	int index;

	//Open files
	ifstream infile;
	ofstream outfile;
	openFiles(infile, outfile);

	//User sets spaceship's coordinates
	shipX = placeShipX();
	shipY = placeShipY();

	//Number of asteroids that the user wants collected
	collect = getNumCollect();

	//Initiates AsteroidList
	AsteroidList astArray(collect);
  
  initList(infile,astArray);
  
	//"Turn on spaceship" and let it fulfill responsibilities
	Ship spaceship(shipX, shipY,collect);
	//Check if there are enough asteroids in the file for desired amount
	
for(int i =0;i<3;i++)
{
	Asteroid target = spaceship.searchField(astArray);


	spaceship.collectAsteroid(target);
	
	//cout<<target.isCollected()<<endl;
}

	//cout<<spaceship.distanceToAsteroid(asteroidX, asteroidY)<<endl;
	//Output number of asteroids collected

	//Ouput order in which asteroids were collected

	//Ouput order in asteroids' sizes

	//Output total distance

	//Output total size of asteroids


	//Close files
	closeFiles(infile, outfile);


	return 0;
}

void closeFiles(ifstream &infile, ofstream &outfile)
{
	infile.close();
	outfile.close();
}

int getNumCollect()
{
	int num;

	//Prompt user
	cout << "How many asteroids should the spaceship collect?" << endl;

	//User inputs number of asteroids that need to be collected(keyboard)
	cin >> num;

	return num;
}

void initList(ifstream &ifile,AsteroidList &astArray)
{
  int asteroidX, asteroidY;
	double weight;
	int index = 0;
	
  //Read file for asteroids' location and size
	ifile >> asteroidX >> asteroidY >> weight;
	while (!ifile.eof())
	{
		Asteroid anAsteroid(asteroidX, asteroidY, weight);

		astArray.add(index,anAsteroid);

		ifile >> asteroidX >> asteroidY >> weight;
		index++;
	}
  
}

void openFiles(ifstream &infile, ofstream &outfile)
{
	string ifile = "input.txt";
	infile.open(ifile);

	string ofile = "output.txt";
	outfile.open(ofile);
}

int placeShipX()
{
	int shipX;

	//prompt user
	cout << "Enter X coordinate : " << endl;

	//User enters initial position of spaceship(keyboard)
	cin >> shipX;

	return shipX;
}

int placeShipY()
{
	int shipY;

	//prompt user
	cout << "Enter Y coordinate : " << endl;

	//User enters initial position of spaceship(keyboard)
	cin >> shipY;

	return shipY;
}



```
