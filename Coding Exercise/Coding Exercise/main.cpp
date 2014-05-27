#include <iostream>
#include <string>
#include <fstream>
#include <complex>

using namespace std;

/* Created by Gavin Whitehall (GW) - 22/05/2014. Last Modified by Gavin Whitehall (GW) - 23/05/2014 */
/// Current Functionality :: Reads the file line by line, converting the numbers and storing them in as complex, calculates the amplitude and phase and then outputs to a file.

int filesize (string dir)
{
	/* This function returns the total size of the file - GW */

	ifstream file(dir);		//Open the inputted file - GW
	streampos begin, end;			//Variables to hold the beginning and end values - GW

	begin = file.tellg();		//Set the begin value - GW
	file.seekg (0, ios::end);	//Set the get positon to the end of the file - GW
	end = file.tellg();		//Set the end value - GW
	
	file.close();				//Close the file
	return end-begin;				//Return the size of the file - GW
}

int rowcount (string dir)
{
	/* This function returns the total row count of the file - GW */

	ifstream file(dir);	//Open the inputted file - GW
	string line;				//String for the getLine function - GW
	int length = 0;				//The length variable to iterate upon - GW

	/* Iterate for the length of the file - GW */
	while (getline(file, line))
	{
		++length;				//Increase the length variable per line - GW
	}
	
	file.close();			//Close the file - GW
	
	return length;				//Return the row count of the file - GW
}

int main ()
{
	string text;								//Temp string for holding lines from the file read - GW

	string filedir = "";						//Use this for an external directory location	- GW
	string inputName = "reimadmt.dat";			//Name of the input file	- GW
	string outputname = "output.dat";			//Name of the output file	- GW

	string inputFile = filedir+inputName;		//Full Directory of the input file - GW
	string outputFile = filedir+outputname;		//Full Directory of the output file - GW
	
	ifstream input (inputFile);					//Open the file with the full directory - GW
	ofstream output;							//Variable for the output class - GW

	int num_Columns = 2;						//As there are 2 columns (real/imaginary) - GW
	int spacing = 2;							//The spacing-size between each column - GW
	string delimiter = "  ";					//As two spaces are used to separate the columns set the delimiter to this - GW
	
	int size_File = filesize(inputFile);		//Total size of the file - GW
	int num_Rows = rowcount(inputFile) + 1;		//The number of rows in the file (Extra row is hard-added due to an empty row at the bottom of which is being skipped) - GW
	int num_PopulatedRows = num_Rows - 1;		//The number of populated rows in the file - GW

	int num_Length = ((size_File/num_Rows+1) - spacing*2)/num_Columns;	//The calculated character size of the numbers (total size over total rows, remove spacing, over total columns) - GW

	complex<double>* inputNumbers = new complex<double>[num_PopulatedRows];	//Array to store complex numbers - GW

	/* Check the file is open */
	if (input.is_open())
	{
		/* Output for the user */
		cout << "Input File Found: "
			<< "'" << inputFile << "'" << endl
			<< size_File << " Characters" << endl
			<< num_Rows << " Rows" << endl;

		input.seekg(spacing);			//Set the start position past the first spacing - GW
		int i = 0;						//Counter variable - GW
		
		/* Iterate while there is a line to read - GW */
		while (getline(input, text))
		{
			/* Split text into 2 strings using the spacing and convert into a double - GW */

			int pos = input.tellg();		//Get the current position - GW
			input.seekg(pos+spacing);	//Set the positon to the current position plus the spacing - GW
						
			size_t delimPos = 0;		//The position in the string of the delimiter - GW

			/* Check if the delimiter is in the string - GW */
			if(text.find(delimiter) != string::npos)
			{
				delimPos = text.find(delimiter);	//Set the position to position of the delimiter - GW
			}

			double real = atof((text.substr(0, delimPos)).c_str());					//Variable to hold real number - GW
			double imaginary = atof((text.erase(0, delimPos + spacing)).c_str());	//Variable to hold imaginary number - GW
			complex<double> tempComplex (real,imaginary);							//Create a temporary complex double - GW

			inputNumbers[i] = tempComplex;			//Assign the temp complex double to the array - GW
	
			i++;		//iterate once per loop - GW
		}
		input.close();	//When it's finished close the file - GW
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Failed to open file. Check the directory.";
	}

	output.open(outputFile);		//Create the output file with the full directory - GW

	if (output.is_open())
	{
		/* Outputting the Array - GW */
		for(int i = 0; i < num_PopulatedRows ; ++i)
		{
			output.precision(7);			//Set the floating-point precision of the numbers to 7 - GW
			output << scientific			//Numbers will be represented in scientific form - GW
			<< delimiter					//First add the delimter - GW
			<< abs(inputNumbers[i])			//Then the Amplitude in column 1 - GW
			<< delimiter					//Then the second delimter to seperate the columns - GW
			<< arg(inputNumbers[i]) << "\n";	//Finally add the Phase to column 2 and take a new line - GW
		}
		output.close();		//When it's finished close the file - GW
		cout << "Output File Created: " << "'" << outputFile << "'" << endl;	//Output information for the user - GW
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Failed to create file" << endl;
	}

	system("pause");		//Correct Implementation to keep output open upon run - GW
	return 0;
	
}
