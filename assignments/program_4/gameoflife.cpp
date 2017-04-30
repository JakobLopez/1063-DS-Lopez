#include <iostream>
#include <string>
#include <fstream>

// #ifdef __cplusplus__
// #include <cstdlib>
// #else
// #include <stdlib.h>
// #endif

#include <windows.h>

using namespace std;

class GameOfLife{
private:
	int **Board;
	int **Board2;
	int **Board3;
	int Rows;
	int Cols;
public:
	GameOfLife(string filename){
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

	void InitBoardArray(int **&b)
	{
		b = new int*[Rows];
		for (int i = 0; i < Rows; i++)
		{
			b[i] = new int[Cols];
		}
		ResetBoardArray(b);
	}

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

	bool OnBoard(int row, int col)
	{
		return (row >= 0 && row < Rows && col >= 0 && col < Cols);
	}

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

	void SetCell(int r, int c, int val)
	{
		Board[r][c] = val;
	}

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

	void clear_screen(int lines)
	{
		for (int i = 0; i < lines; i++)
		{
			cout << endl;
		}
	}

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

	bool Stable()
	{
		int area = Rows * Cols;
		return (sameItems() == area);
	}
};

int main()
{
	GameOfLife G("gen_one.txt");
	
	G.GliderGun();
	G.Run(100);
	G.Stable();

	system("pause");
	return 0;
}
