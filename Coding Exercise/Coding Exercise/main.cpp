#include <iostream>
#include <string>
#include <fstream>
#include <complex>

using namespace std;

/* Created by Gavin Whitehall (GW) - 22/05/2014. Last Modified by Gavin Whitehall (GW) - 28/05/2014 */
/// Current Functionality :: Extracts each number using ifstream operator (2 extracts per iteration), stores in temporary complex<double> then calculates the amplitude and phase and outputs to a file.

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
	string filedir = "";						//Use this for an external directory location	- GW
	string inputName = "reimadmt.dat";			//Name of the input file	- GW
	string outputname = "output.dat";			//Name of the output file	- GW

	string inputFile = filedir+inputName;		//Full Directory of the input file - GW
	string outputFile = filedir+outputname;		//Full Directory of the output file - GW
	
	ifstream input (inputFile);					//Open the file with the full directory - GW
	ofstream output(outputFile);				//Create and open the output file with the full directory - GW

	int num_Columns = 2;						//As there are 2 columns (real/imaginary) - GW
	string delimiter = "  ";					//As two spaces are used to separate the columns set the delimiter to this - GW
	
	int size_File = filesize(inputFile);		//(Optional) Total size of the file - GW
	int num_Rows = rowcount(inputFile) + 1;		//(Optional) The number of rows in the file (Extra row is hard-added due to an empty row at the bottom of which is being skipped) - GW

	/* Check the file is open */
	if (input.is_open())
	{
		/* Output for the user */
		cout << "Input File Found: "
			<< "'" << inputFile << "'" << endl
			<< size_File << " Characters" << endl
			<< num_Rows << " Rows" << endl;

		/* Check the file is open */
		if (output.is_open())
		{
			/* Runs indefinitely (until the break) - GW */
			while(true)
			{
				double real;			//Variable to hold real number - GW
				double imaginary;		//Variable to hold imaginary number - GW

				input >> real;			//Extract the first number into variable - GW
				input >> imaginary;		//Extract the second number into variable - GW

				if(input.eof())
				{
					break;				//Ends the statement when the file end is reached - GW
				}

				complex<double> complexNum (real, imaginary);		//Create a complex double from inputted real/imaginary numbers - GW

				output.precision(7);			//Set the floating-point precision of the numbers to 7 - GW
				output << scientific			//Numbers will be represented in scientific form - GW
				<< delimiter					//First add the delimter - GW
				<< abs(complexNum)				//Then the Amplitude in column 1 - GW
				<< delimiter					//Then the second delimter to seperate the columns - GW
				<< arg(complexNum) << "\n";		//Finally add the Phase to column 2 and take a new line - GW
			}

			output.close();		//When it's finished close the file - GW
		}
		else
		{
			/* Output error message otherwise - GW */
			cout << "Error: Failed to create file" << endl;
		}

		input.close();	//When it's finished close the file - GW

		cout << "Output File Created: " << "'" << outputFile << "'" << endl;	//Output information for the user - GW	
	}
	else
	{
		/* Output error message otherwise - GW */
		cout << "Error: Failed to open file. Check the directory.";
	}

	system("pause");		//To keep output open upon run - GW
	return 0;
}
