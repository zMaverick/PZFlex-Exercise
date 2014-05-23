#include <iostream>
#include <string>
#include <fstream>
#include <complex>

using namespace std;

/* Created by Gavin Whitehall (GW) - 22/05/2014. Last Modified by Gavin Whitehall (GW) - 23/05/2014 */
/// Current Functionality :: Reads the file line by line, converting the numbers into doubles and storing them in a 2D array and outputs it for test purposes.

int filesize (string dir)
{
	/* This function returns the total size of the file - GW */

	ifstream inputFile(dir);		//Open the inputted file - GW
	streampos begin, end;			//Variables to hold the beginning and end values - GW

	begin = inputFile.tellg();		//Set the begin value - GW
	inputFile.seekg (0, ios::end);	//Set the get positon to the end of the file - GW
	end = inputFile.tellg();		//Set the end value - GW
	
	inputFile.close();				//Close the file
	return end-begin;				//Return the size of the file - GW
}

int rowcount (string dir)
{
	/* This function returns the total row count of the file - GW */

	ifstream inputFile(dir);	//Open the inputted file - GW
	string line;				//String for the getLine function - GW
	int length = 0;				//The length variable to iterate upon - GW

	/* Iterate for the length of the file - GW */
	while (getline(inputFile, line))
	{
		++length;				//Increase the length variable per line - GW
	}
	
	inputFile.close();			//Close the file - GW
	
	return length;				//Return the row count of the file - GW
}

int main ()
{
	string text;							//Temp string for testing file read - GW

	string filedir = "";					//Use this for an external directory location	- GW
	string filename = "reimadmt.dat";		//Name of the input file	- GW

	string theFile = filedir+filename;

	ifstream file (theFile);				//Open the file with the full directory - GW
	
	int num_Columns = 2;					//As there are 2 columns (real/imaginary) - GW
	int spacing = 2;						//The spacing-size between each column - GW
	
	int size_File = filesize(theFile);			//Total size of the file - GW
	int num_Rows = rowcount(theFile) + 1;		//The number of rows in the file (Extra row is hard-added due to an empty row at the bottom of which is being skipped) - GW
	int num_PopulatedRows = num_Rows - 1;		//The number of populated rows in the file - GW

	int num_Length = ((size_File/num_Rows+1) - spacing*2)/num_Columns;	//The calculated character size of the numbers (total size over total rows, remove spacing, over total columns) - GW

	cout << "Number Length: " << num_Length << " Characters.\n";
	cout << "Total Rows: " << num_Rows << ".\n";

	double** numbers = new double*[num_PopulatedRows];		//Array of pointers to arrays, this will hold all the numbers - GW
	complex<double>* numberTest = new complex<double>[num_PopulatedRows];


	/* Populate the pointers array with doubles */
	for (int i = 0; i < num_PopulatedRows; ++i)
	{
		numbers[i] = new double[num_Columns];
	}

	/* Check the file is open */
	if (file.is_open())
	{
		cout << "File Contents:" << '\n';

		file.seekg(spacing);			//Set the start position past the first spacing - GW
		int i = 0;						//Counter variable - GW
		
		/* Iterate while there is a line to read - GW */
		while (getline(file, text))
		{
			/* Split text into 2 strings using the spacing and convert into a double - GW */

			int pos = file.tellg();		//Get the current position - GW
			file.seekg(pos+spacing);	//Set the positon to the current position plus the spacing - GW
						
			string delimiter = "  ";	//As two spaces are used to separate the numbers set the delimiter to this - GW
			size_t delimPos = 0;		//The position in the string of the delimiter - GW

			/* Check if the delimiter is in the string - GW */
			if(text.find(delimiter) != string::npos)
			{
				delimPos = text.find(delimiter);	//Set the position to position of the delimiter - GW
			}

			double real = atof((text.substr(0, delimPos)).c_str());					//Variable to hold real number - GW
			double imaginary = atof((text.erase(0, delimPos + spacing)).c_str());	//Variable to hold imaginary number - GW
			complex<double> tempComplex (real,imaginary);							//Create a temporary complex double - GW

			numberTest[i] = tempComplex;											//Assign the temp complex double to the array - GW
	
			i++;		//iterate once per loop - GW
		}
		
		file.close();	//When it's finished close the file - GW
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Unable to open file";
	}

	/* Testing the Array - GW */
	for(int i = 0; i < num_PopulatedRows ; ++i)
	{
		cout.precision(7);
		cout << scientific;
		cout << numberTest[i] << endl;
	}

	system("pause");		//Modified: Correct Implementation to keep output open upon run - GW
	return 0;
	
}