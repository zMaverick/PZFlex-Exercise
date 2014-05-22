#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/* Created by Gavin Whitehall (GW) - 22/05/2014 */
/// Current Functionality :: Reads the file line by line and outputs it.

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

	string* numbers = new string[num_PopulatedRows];		//Temp array for test - GW

	/* Check the file is open */
	if (file.is_open())
	{
		cout << "File Contents:" << '\n';
		file.seekg(spacing);		//Set the start position past the first spacing - GW
		int i = 0;					//Counter variable - GW
		
		/* Iterate while there is a line to read - GW */
		while (getline(file, text))
		{
			int pos = file.tellg();		//Get the current position - GW
			file.seekg(pos+spacing);	//Set the positon to the current position plus the spacing - GW

			//split text into 2 strings using the spacing
			//for both strings split them using E and convert into floats from sci-notation
			//add to array of numbers

			numbers[i] = text;		//Temporary variable for testing - GW
			i++;					//iterate once per loop - GW
		} 

		/* Test Array - GW */
		for(int x=0; x < num_PopulatedRows ; x++)
		{
			cout << numbers[x] << '\n';
		}
		
		file.close();	//When it's finished close the file - GW
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Unable to open file";
	}
	

	system("pause");		//Modified: Correct Implementation to keep output open upon run - GW
	return 0;
	
}