#include <iostream>
#include <string>
#include <fstream>


#include <windows.h>

using namespace std;

class GameOfLife
{
private:
	int **Board;
	int **Board2;
	int **Board3;
	int Rows;
	int Cols;
public:
	GameOfLife(string filename)
	{
		string line;
		char ch;
		ifstream fin;
		fin.open(filename);
		fin >> Rows >> Cols;
		InitBoardArray(Board);
		InitBoardArray(Board2);
		InitBoardArray(Board3);
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				fin.get(ch);
				if (ch == 10)
				{
					continue;
				}
				Board[i][j] = int(ch) - 48;
			}
		}
	}

	/**
	* @FunctionName: InitBoardArray
	* @Description:
	*     Initializes columns for each row
	* @Params:
	*    int **&b - address to a 2d array
	* @Returns:
	*    void
	*/
	void InitBoardArray(int **&b)
	{
		b = new int*[Rows];
		for (int i = 0; i < Rows; i++)
		{
			b[i] = new int[Cols];
		}
		ResetBoardArray(b);
	}

	/**
	* @FunctionName: ResetBoardArray
	* @Description:
	*     Sets every coordinate to 0
	* @Params:
	*    int **&b - address to a 2d array
	* @Returns:
	*    void
	*/
	void ResetBoardArray(int **&b)
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				b[i][j] = 0;
			}
		}
	}

	/**
	* @FunctionName: PrintBoard
	* @Description:
	*     Prints the board with character 'X' as life
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void PrintBoard()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Board[i][j] == 1)
					cout << char('X');
				else
					cout << " ";
			}
			cout << endl;
		}
	}

	/**
	* @FunctionName: CountNeighbors
	* @Description:
	*     Counts the amount of life around a coordinate.
	*     Causes the wrap around functionality, or never ending plane
	* @Params:
	*    int row - row number
	*	 int col - column number
	* @Returns:
	*    int - Number of neighbors
	*/
	int CountNeighbors(int row, int col)
	{
		int neighbors = 0;

		if (Board[(row + 1) % Rows][col] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][col] == 1)
			neighbors++;

		if (Board[(row + 1) % Rows][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + 1) % Rows][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[(row + Rows - 1) % Rows][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		if (Board[row][(col + 1) % Cols] == 1)
			neighbors++;

		if (Board[row][(col + Cols - 1) % Cols] == 1)
			neighbors++;

		return neighbors;
	}

	/**
	* @FunctionName: OnBoard
	* @Description:
	*     determines if a coordinate is within boundaries
	* @Params:
	*    int row - row number
	*	 int col - column number
	* @Returns:
	*    bool - true if on board / false otherwise
	*/
	bool OnBoard(int row, int col)
	{
		return (row >= 0 && row < Rows && col >= 0 && col < Cols);
	}

	/**
	* @FunctionName: RandomPopulate
	* @Description:
	*     Randomly sets a cell on the game board
	* @Params:
	*    int num - amount of random cells to set
	* @Returns:
	*    void
	*/
	void RandomPopulate(int num)
	{
		int r = 0;
		int c = 0;
		for (int i = 0; i < num; i++)
		{
			r = rand() % Rows;
			c = rand() % Cols;
			Board[r][c] = 1;
		}
	}

	/**
	* @FunctionName: SetCell
	* @Description:
	*     places a cell on the game board
	* @Params:
	*    int r - row
	*    int c - column
	*    int val - value that will be set for the coordinate
	* @Returns:
	*    void
	*/
	void SetCell(int r, int c, int val)
	{
		Board[r][c] = val;
	}

	/**
	* @FunctionName: AddGens
	* @Description:
	*     Adds Board2 to Board, and then resets Board2
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void AddGens()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Board[i][j] += Board2[i][j];
			}
		}
		ResetBoardArray(Board2);
	}

	/**
	* @FunctionName: clear_screen
	* @Description:
	*     Outputs blank lines
	* @Params:
	*    int lines - number of lines that will be blank
	* @Returns:
	*    void
	*/
	void clear_screen(int lines)
	{
		for (int i = 0; i < lines; i++)
		{
			cout << endl;
		}
	}

	/**
	* @FunctionName: Run
	* @Description:
	*     Sets the rules for the Game of Life.
	*     Corners die and when generations are consecutively the same it stops.
	*     The board is printed and runs for a explicit amount of generations.
	* @Params:
	*    int generations - number of times game will loop
	* @Returns:
	*    void
	*/
	void Run(int generations = 99999)
	{
		int neighbors = 0;
		int g = 0;

		int same_generations = 0;

		while (g < generations)
		{
			replicate();

			for (int i = 0; i < Rows; i++)
			{
				for (int j = 0; j < Cols; j++)
				{
					neighbors = CountNeighbors(i, j);

					if (Board[i][j] == 1 && (neighbors < 2 || neighbors > 3))
					{
						Board2[i][j] = -1;
					}
					if (Board[i][j] == 0 && neighbors == 3)
					{
						Board2[i][j] = 1;
					}
					if (Board[i][j] == 1 && Corner(i, j))
					{
						Board2[i][j] = -1;
					}
				}
			}

			AddGens();
			Sleep(100);
			clear_screen(30);
			PrintBoard();
			g++;
			cout << g << endl;
			cout << endl;

			if (Stable())
			{
				return;
			}

		}
	}

	/**
	* @FunctionName: Corner
	* @Description:
	*     Determines if a coordinate is in the corner of the 2d array
	* @Params:
	*     int r - row
	*     int c - column
	* @Returns:
	*    bool - true if coordinate is in corner/ false otherwise
	*/
	bool Corner(int r, int c)
	{
		if (r == 0 && c == 0)
			return true;
		if (r == 0 && c == Cols - 1)
			return true;
		if (r == Rows - 1 && c == 0)
			return true;
		if (r == Rows - 1 && c == Cols - 1)
			return true;

		return false;

	}

	/**
	* @FunctionName: GliderGun
	* @Description:
	*     Copies a 2d array to the game board.
	*	  The 2d array will create a never ending glider spawn
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void GliderGun()
	{
		ResetBoardArray(Board);

		int glider_gun[11][38]
		{
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0 },
			{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		};

		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 38; j++)
			{
				Board[i][j] = glider_gun[i][j];
			}
		}
	}

	/**
	* @FunctionName: replicate
	* @Description:
	*     Copies a board to another 2d array
	* @Params:
	*    None
	* @Returns:
	*    void
	*/
	void replicate()
	{
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				Board3[i][j] = Board[i][j];
			}
		}
	}

	/**
	* @FunctionName: sameItems
	* @Description:
	*     Counts the amount of same values from 2 seperate boards
	* @Params:
	*     None
	* @Returns:
	*    int - Number of same values
	*/
	int sameItems()
	{
		int n = 0;
		for (int i = 0; i < Rows; i++)
		{
			for (int j = 0; j < Cols; j++)
			{
				if (Board3[i][j] == Board[i][j])
					n++;
			}

		}
		return n;
	}

	/**
	* @FunctionName: Stable
	* @Description:
	*     determines if the same number of items on 2 seperate boards
	*	  is equivalent to the area
	* @Params:
	*     None
	* @Returns:
	*    bool - true if every item is the same / false otherwise
	*/
	bool Stable()
	{
		int area = Rows * Cols;
		return (sameItems() == area);
	}
};

int main()
{
	GameOfLife G("gen_one.txt");

	//G.Run(100);

	/* new functions*/
	//G.GliderGun();	
	//G.Stable();

	system("pause");
	return 0;
}
