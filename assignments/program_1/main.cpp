#/**
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
void flipVert(rgb** image, int width, int height)
{
	for (int row = 0; row < height / 2; row++)
	{
		for (int col = 0; col < width; col++)
		{
			rgb *top = new rgb;
			rgb *bot = new rgb;

			*top = image[row][col];
			*bot = image[height - 1 - row][col];

			image[height - 1 - row][col] = *top;
			image[row][col] = *bot;
		}
	}
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
void flipHorz(rgb** image, int width, int height)
{
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width / 2; col++)
		{
			rgb *left = new rgb;
			rgb *right = new rgb;

			*left = image[row][col];
			*right = image[row][width - 1 - col];

			image[row][width - 1 - col] = *left;
			image[row][col] = *right;
		}
	}
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
void grayScale(rgb** image, int width, int height)
{
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			int gray = (image[i][j].r + image[i][j].g + image[i][j].b) / 3;
			image[i][j].r = gray;
			image[i][j].g = gray;
			image[i][j].b = gray;
		}
	}
}

/**
* @ProgramName: Image_Manip_prog1
* @Author: Jakob Lopez
* @Description:
*     This program reads in images stored as rgb values in a space delimited file format.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 04/02/2017
*/
int main(){
	ifstream ifile;          //Input / output files
	ofstream ofile;
	ifile.open("bot.txt");
	ofile.open("bot2.txt");

	int width;               //width of image
	int height;              //height of image

	rgb **imgArray;         //Pointer var for our 2D array          


	ifile >> width >> height;   //Read in width and height from top of input file
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
			ifile >> imgArray[i][j].r >> imgArray[i][j].g >> imgArray[i][j].b;
		}
	}

	flipVert(imgArray, width, height);

	flipHorz(imgArray, width, height);

	grayScale(imgArray, width, height);


	//Write out our color data to a new file
	ofile << width << " " << height << endl;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " " << imgArray[i][j].b << " ";
		}
		ofile << endl;
	}
	ifile.close();
	ofile.close();

	return 0;
}
