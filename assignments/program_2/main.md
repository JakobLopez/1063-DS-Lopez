```
#include "Spaceship.h"
#include<iostream>
#include<math.h>
using namespace std;

Ship::Ship()
{
	x = 0;
	y = 0;
	toCollect = 0;
	totalTravelled = 0;
}

Ship::Ship(int X, int Y, int collect)
{
	x = X;
	y = Y;
	toCollect = collect;
	totalTravelled = 0;
}

void Ship::collectAsteroid(Asteroid &target)
{
	int asteroidX = target.getX();
	int asteroidY = target.getY();
	cout << "asteroid is: " << asteroidX << "," << asteroidY << endl;
	cout <<"spaceship is: "<< x << "," << y << endl;
	movePosition(asteroidX, asteroidY);
	cout << "Now spaceship is: "<< x << "," << y << endl;
	
		target.changeStatus();
		if(target.isCollected())
			cout << "its collected" << endl;;
	}

}

double Ship::distanceToAsteroid(int x2, int y2)
{
	int differenceX = x2 - x;
	int distanceX = pow(differenceX, 2);

	int differenceY = y2 - y;
	int distanceY = pow(differenceY, 2);

	double calcDistance = static_cast<double>(sqrt(distanceX + distanceY));


	return calcDistance;
}

int Ship::getX()
{
	return x;
}

int Ship::getY()
{
	return y;
}

void Ship::movePosition(int newX, int newY)
{
	totalTravelled += distanceToAsteroid(newX, newY);

	x = newX;
	y = newY;
}

Asteroid Ship::searchField(AsteroidList aList)
{
	Asteroid closest = aList.get(0);

	for (int i = 0; i < toCollect; i++)
	{
	  while(closest.isCollected())
	  {
	    closest = aList.get(i);
	  }
		int closestX = closest.getX();
		int closestY = closest.getY();

		int asteroidX = aList.get(i).getX();
		int asteroidY = aList.get(i).getY();
    
    if(!aList.get(i).isCollected())
    {
		if (distanceToAsteroid(asteroidX, asteroidY) < distanceToAsteroid(closestX,closestY))
			closest = aList.get(i);	
    }
	}
	return closest;
}

double Ship::totalDistance()
{
	return totalTravelled;
}

Ship::~Ship()
{

}

```
