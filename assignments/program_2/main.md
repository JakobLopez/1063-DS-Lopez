```
/**
* @ProgramName: Image_prog2
* @Author: Jakob Lopez
* @Description:
*     This program reads in images stored as rgb values in a space delimited file format.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 02/12/2017
*/
/**
* TXT Image Manipulation Starter
*
* This code is a simple way to read in color information stored in a space
* delimited txt format. The expected file format is:
*                ---------------------------
*                | width height            |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                | R G B R G B R G B R G B |
*                ---------------------------
* So a 10x10 img would have 11 total rows, 10 rows of data, with 30 values in row.
*/

#include<iostream>
#include<fstream>
#include<math.h>

using namespace std;

/**
Structure to hold an rgb value
*/
struct rgb{
	int r;
	int g;
	int b;
};

class ImageManip
{
private:
	rgb** imgArray;
	int width;
	int height;
	ifstream infile;
	ofstream ofile;
	string ifile_name;
	string ofile_name;

	void readFile(string ifile_name)
		{
			infile.open(ifile_name);
			       
			infile >> width >> height;   //Read in width and height from top of input file
			//We need this so we can make the array the right 
			//size.

			imgArray = new rgb*[height];    //This array points to every row

			for (int i = 0; i < height; i++)
			{
				imgArray[i] = new rgb[width]; //Now allocate each row of rgb's
			}

			//Read the color data in from our txt file
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					infile >> imgArray[i][j].r >> imgArray[i][j].g >> imgArray[i][j].b;
				}
			}
			infile.close();
	}

	void writeFile(string ofile_name)
	{
		ofile.open(ofile_name);
		//Write out our color data to a new file
		ofile << width << " " << height << endl;
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " " << imgArray[i][j].b << " ";
			}
			ofile << endl;
		}

		
		ofile.close();
	}

public:
	ImageManip()
	{
		ifile_name = "Bot1.txt";
		ofile_name = "Bot1.txt";
	}
/**
* @FunctionName: flipVert
* @Description:
*     Loops through a 2D array and flips each row across height/2.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/	
	void flipVert(string ifile_name, string ofile_name)
	{
		readFile(ifile_name);
		
		for (int row = 0; row < height / 2; row++)
		{
			for (int col = 0; col < width; col++)
			{
				rgb *top = new rgb;
				rgb *bot = new rgb;

				*top = imgArray[row][col];
				*bot = imgArray[height - 1 - row][col];

				imgArray[height - 1 - row][col] = *top;
				imgArray[row][col] = *bot;
			}
		}
		writeFile(ofile_name);
	}
/**
* @FunctionName: flipHorz
* @Description:
*     Loops through a a 2D array and flips each column across width/2.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/	
	void flipHorz(string ifile_name, string ofile_name)
	{
		readFile(ifile_name);

		for (int row = 0; row < height; row++)
		{
			for (int col = 0; col < width / 2; col++)
			{
				rgb *left = new rgb;
				rgb *right = new rgb;

				*left = imgArray[row][col];
				*right = imgArray[row][width - 1 - col];

				imgArray[row][width - 1 - col] = *left;
				imgArray[row][col] = *right;
			}
		}

		writeFile(ofile_name);
	}
/**
* @FunctionName: grayScale
* @Description:
*     Loops through a 2D array and turns every RGB value into its grayscale equivalent.
* @Params:
*    rgb** image - 2D array holding rgb values
*    int width - width of image
*    int height - height of image
* @Returns:
*    void
*/
	void grayScale(string ifile_name, string ofile_name)
	{
		readFile(ifile_name);

		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				int gray = (imgArray[i][j].r + imgArray[i][j].g + imgArray[i][j].b) / 3;
				imgArray[i][j].r = gray;
				imgArray[i][j].g = gray;
				imgArray[i][j].b = gray;
			}
		}
		writeFile(ofile_name);
	}
	~ImageManip(){
	}
};


int main()
{

	ImageManip j;
	j.flipVert("Bot1.txt", "Bot2.txt");
	j.flipHorz("Bot1.txt", "Bot2.txt");
	j.grayScale("Bot1.txt", "Bot2.txt");



	return 0;
}
```
