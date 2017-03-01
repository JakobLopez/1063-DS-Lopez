```
/**
* @Homework: Homework-3
* @Author: Jakob Lopez 
* @Description: 
*     This function prints out the contents of a circular queue.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 02/28/2017
*/
/**
	* @FunctionName: Print
	* @Description:
	*     The if statement prints out the first number of the queue when full 
	*     because the while loop will not print a list at all when Front == Rear
	* @Params:
	*    NONE
	* @Returns:
	*    NONE
	*/
	void Print()
	{
		int Index = Front;

		if (Index == Rear)
		{
			cout << Q[Index] << " ";
			Index = ((Index + 1) % (ArraySize));
		}
		while (Index != Rear)
		{
			cout << Q[Index] << " ";
			Index = ((Index + 1) % (ArraySize));
		}
		cout << endl;
	}
```
